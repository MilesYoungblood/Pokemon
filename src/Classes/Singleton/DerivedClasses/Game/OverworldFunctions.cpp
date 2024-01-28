//
// Created by Miles Youngblood on 10/24/2023.
//

#include "Game.h"

int walkCounter = 0;                                     // measures how many screen pixels the player has moved
int bumpCounter = 0;

bool keepMovingForward = false;                          // ultimately, determine when the player stops moving
bool colliding = false;
bool momentum = false;                                   // denotes whether the player is still moving

void Game::changeMap(const std::tuple<int, int, Map::Id> &data) {
    if (Mix_FadeOutMusic(2000) == 0) {
        std::clog << "Error fading out \"" << this->currentMap->getMusic() << "\": " << SDL_GetError() << '\n';
        SDL_ClearError();
        this->running = false;
        return;
    }

    Mix_HookMusicFinished([] -> void {
        Mixer::getInstance().playMusic(Game::getInstance().currentMap->getMusic().c_str());
    });

    this->currentMap->reset();

    // move the new map into the current map variable
    this->currentMapIndex = std::get<2>(data);
    this->currentMap = &this->maps.at(this->currentMapIndex);

    // resets the states of these variables for each trainer
    for (auto &trainer : *this->currentMap) {
        pixelsTraveled[&trainer] = 0;
        keepLooping[&trainer] = true;
    }

    Player::getPlayer().setCoordinates(std::get<0>(data), std::get<1>(data));

    Camera::getInstance().lockOnPlayer(this->currentMap);
}

void Game::createTextBox(const std::vector<std::string> &messages) const {
    GraphicsEngine::getInstance().addGraphic<TextBox>(TextBox::getInstance());
    GraphicsEngine::getInstance().getGraphic<TextBox>().setFinishedCallback([] -> void {
        KeyManager::getInstance().unlockKey(SDL_Scancode::SDL_SCANCODE_RETURN);
    });

    const int box_width = Constants::TILE_SIZE * 7;
    const int box_height = Constants::TILE_SIZE * 2;
    const SDL_Rect rect(
            this->WINDOW_WIDTH / 2 - box_width / 2,
            this->WINDOW_HEIGHT - box_height,
            box_width,
            box_height - Constants::TILE_SIZE / 2
    );
    GraphicsEngine::getInstance().getGraphic<TextBox>().init(
            rect,
            rect.h / (Constants::TILE_SIZE * 3 / 10),
            rect.x + Constants::TILE_SIZE / 10,
            rect.y + Constants::TILE_SIZE / 10
    );
    GraphicsEngine::getInstance().getGraphic<TextBox>().push(messages);
}

void Game::checkForOpponents() {
    if (GraphicsEngine::getInstance().hasAny<Rectangle>()) {
        return;
    }
    // resets movement variables if you are not inputting any directions
    if (not(KeyManager::getInstance().getKey(SDL_Scancode::SDL_SCANCODE_W) or
            KeyManager::getInstance().getKey(SDL_Scancode::SDL_SCANCODE_A) or
            KeyManager::getInstance().getKey(SDL_Scancode::SDL_SCANCODE_S) or
            KeyManager::getInstance().getKey(SDL_Scancode::SDL_SCANCODE_D))) {
        momentum = false;
    }

    static int frameCounter = 0;    // makes a trainer that spotted the player stand still for a set number of frames
    static bool haltMusic = true;
    static bool playMusic = true;

    // checks if the player is in LoS for any trainer
    for (auto &trainer : *this->currentMap) {
        if (trainer->canFight() and keepLooping[&trainer] and trainer->hasVisionOf(&Player::getPlayer())) {
            if (haltMusic) {
                Mix_HaltMusic();
                haltMusic = false;

                GraphicsEngine::getInstance().addGraphic<TimedVisual>(
                        "exclamation.png",
                        50 * (this->currentFps / 30) / 2,
                        SDL_Rect(
                                trainer->getScreenX(),
                                trainer->getScreenY() - Constants::TILE_SIZE,
                                Constants::TILE_SIZE,
                                Constants::TILE_SIZE
                        )
                );
                Mixer::getInstance().playSound("spotted");
            }
            KeyManager::getInstance().blockInput();
            momentum = false;
            trainer->lock();

            ++frameCounter;
            if (frameCounter < 50 * (this->currentFps / 30)) {
                return;
            }

            if (playMusic) {
                Mixer::getInstance().playMusic("GymBattle");
                playMusic = false;
            }

            if (not trainer->isNextTo(&Player::getPlayer())) {
                trainer->shift(trainer->getDirection(), this->SCROLL_SPEED);
                pixelsTraveled[&trainer] += this->SCROLL_SPEED;

                if (pixelsTraveled[&trainer] % (Constants::TILE_SIZE / 2) == 0) {
                    trainer->updateAnimation();
                }

                if (pixelsTraveled[&trainer] % Constants::TILE_SIZE == 0) {
                    trainer->moveForward();
                }
            }
            else {
                Player::getPlayer().face(trainer.get());

                this->createTextBox(trainer->getDialogue());

                keepLooping[&trainer] = false;

                frameCounter = 0;
                haltMusic = true;
                playMusic = true;
            }
            break;
        }
    }
}

void Game::updateOverworld() {
    static const auto check = [this](SDL_Scancode scancode) -> void {
        static const std::unordered_map<SDL_Scancode, Direction> direction_to_key{
                std::make_pair(SDL_Scancode::SDL_SCANCODE_W, Direction::UP),
                std::make_pair(SDL_Scancode::SDL_SCANCODE_A, Direction::LEFT),
                std::make_pair(SDL_Scancode::SDL_SCANCODE_S, Direction::DOWN),
                std::make_pair(SDL_Scancode::SDL_SCANCODE_D, Direction::RIGHT)
        };

        if (not GraphicsEngine::getInstance().hasAny<Rectangle>()) {
            if (not Player::getPlayer().isFacing(direction_to_key.at(scancode))) {
                Player::getPlayer().setDirection(direction_to_key.at(scancode));
            }
            if (KeyManager::getInstance().getKey(scancode) and (momentum or keyDelay >= 10)) {
                KeyManager::getInstance().lockWasd();

                momentum = true;
                keyDelay.stop();
                keyDelay.reset();

                if (Player::getPlayer().canMoveForward(this->currentMap)) {
                    keepMovingForward = true;
                }
                else {
                    colliding = true;

                    Player::getPlayer().updateAnimation();
                    Mixer::getInstance().playSound("bump");
                }
            }
        }
    };

    if (KeyManager::getInstance().getKey(SDL_Scancode::SDL_SCANCODE_ESCAPE)) {
        if (GraphicsEngine::getInstance().hasAny<Rectangle>()) {
            GraphicsEngine::getInstance().removeGraphic<Rectangle>();
        }
        else {
            GraphicsEngine::getInstance().addGraphic<Rectangle>(SDL_Rect(50, 50, 250, 400), Constants::Color::BLACK, 5);
        }
        // re-lock the Enter key
        KeyManager::getInstance().lockKey(SDL_Scancode::SDL_SCANCODE_ESCAPE);

        // sets a cool-down period before the Enter key can be registered again;
        // this is needed because the program will register a button as
        // being pressed faster than the user can lift their finger
        std::thread coolDown([] -> void {
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            KeyManager::getInstance().unlockKey(SDL_Scancode::SDL_SCANCODE_ESCAPE);
        });
        coolDown.detach();
    }
    else if (KeyManager::getInstance().getKey(SDL_Scancode::SDL_SCANCODE_W)) {
        check(SDL_Scancode::SDL_SCANCODE_W);
    }
    else if (KeyManager::getInstance().getKey(SDL_Scancode::SDL_SCANCODE_A)) {
        check(SDL_Scancode::SDL_SCANCODE_A);
    }
    else if (KeyManager::getInstance().getKey(SDL_Scancode::SDL_SCANCODE_S)) {
        check(SDL_Scancode::SDL_SCANCODE_S);
    }
    else if (KeyManager::getInstance().getKey(SDL_Scancode::SDL_SCANCODE_D)) {
        check(SDL_Scancode::SDL_SCANCODE_D);
    }
    else if (KeyManager::getInstance().getKey(SDL_Scancode::SDL_SCANCODE_RETURN) and not keepMovingForward) {
        for (auto &trainer : *this->currentMap) {
            if (Player::getPlayer().hasVisionOf(trainer.get())) {
                // if the player manually clicked Enter
                if (not GraphicsEngine::getInstance().hasAny<TextBox>()) {
                    trainer->face(&Player::getPlayer());
                    trainer->lock();
                    KeyManager::getInstance().blockInput();

                    // only create the textbox here if the trainer cannot fight;
                    // the program will loop back to checkForOpponents()
                    // and create it there if the trainer can fight
                    if (not trainer->canFight()) {
                        this->createTextBox(trainer->getDialogue());
                    }
                }
                else {
                    // if the textbox still has messages to print
                    if (not GraphicsEngine::getInstance().getGraphic<TextBox>().empty()) {
                        KeyManager::getInstance().blockInput();
                        GraphicsEngine::getInstance().getGraphic<TextBox>().pop();

                        if (not GraphicsEngine::getInstance().getGraphic<TextBox>().empty()) {
                            Mixer::getInstance().playSound("accept");
                        }
                    }
                    // if the textbox is done printing
                    if (GraphicsEngine::getInstance().getGraphic<TextBox>().empty()) {
                        GraphicsEngine::getInstance().removeGraphic<TextBox>();
                        // re-lock the Enter key
                        KeyManager::getInstance().lockKey(SDL_Scancode::SDL_SCANCODE_RETURN);

                        // sets a cool-down period before the Enter key can be registered again;
                        // this is needed because the program will register a button as
                        // being pressed faster than the user can lift their finger
                        std::thread coolDown([] -> void {
                            std::this_thread::sleep_for(std::chrono::milliseconds(500));
                            KeyManager::getInstance().unlockKey(SDL_Scancode::SDL_SCANCODE_RETURN);
                        });
                        coolDown.detach();
                        KeyManager::getInstance().unlockWasd();

                        if (trainer->canFight()) {
                            Mix_HaltMusic();
                            Mixer::getInstance().playMusic("TrainerBattle");

                            trainer->clearParty();
                            this->currentState = Game::State::BATTLE;
                            SDL_SetRenderDrawColor(this->renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
                        }
                        else {
                            trainer->unlock();
                        }
                    }

                    keyDelay.reset();
                    break;
                }
            }
        }
    }

    if (keepMovingForward) {
        if (walkCounter % (Constants::TILE_SIZE / 2) == 0) {
            Player::getPlayer().updateAnimation();
        }
        if (walkCounter % Constants::TILE_SIZE == 0) {
            Player::getPlayer().moveForward();
        }

        this->currentMap->shift(oppositeDirection(Player::getPlayer().getDirection()), this->SCROLL_SPEED);
        walkCounter += this->SCROLL_SPEED;
    }

    if (colliding) {
        if (bumpCounter == 10 * (this->currentFps / 30)) {
            Player::getPlayer().updateAnimation();
        }
        else if (bumpCounter == 20 * (this->currentFps / 30)) {
            KeyManager::getInstance().unlockWasd();

            colliding = false;
            bumpCounter = 0;

            checkForOpponents();
        }

        ++bumpCounter;
    }

    // if the player's sprite is on a tile...
    else if (walkCounter % Constants::TILE_SIZE == 0) {
        if (not GraphicsEngine::getInstance().hasAny<TextBox>()) {
            KeyManager::getInstance().unlockWasd();
        }

        keepMovingForward = false;
        walkCounter = 0;

        checkForOpponents();
        const auto map_data = this->currentMap->isExitPointHere(Player::getPlayer().getX(), Player::getPlayer().getY());
        if (map_data.has_value()) {
            this->changeMap(map_data.value());
        }
    }

    for (auto &trainer : *this->currentMap) {
        trainer->act();
    }

    GraphicsEngine::getInstance().update();
}

void Game::renderOverworld() {
    this->currentMap->render();

    GraphicsEngine::getInstance().render();
}
