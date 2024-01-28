//
// Created by Miles on 1/28/2024.
//

#include "../../../Singleton/DerivedClasses/Game/Game.h"
#include "Overworld.h"

namespace {
    int walkCounter = 0;                                     // measures how many screen pixels the player has moved
    int bumpCounter = 0;

    bool keepMovingForward = false;                          // ultimately, determine when the player stops moving
    bool colliding = false;
    bool momentum = false;                                   // denotes whether the player is still moving
}

void createTextBox(const std::vector<std::string> &messages) {
    GraphicsEngine::getInstance().addGraphic<TextBox>(TextBox::getInstance());
    GraphicsEngine::getInstance().getGraphic<TextBox>().setFinishedCallback([] -> void {
        KeyManager::getInstance().unlockKey(SDL_Scancode::SDL_SCANCODE_RETURN);
    });

    const int box_width = Constants::TILE_SIZE * 7;
    const int box_height = Constants::TILE_SIZE * 2;
    const SDL_Rect rect(
            Game::getInstance().getWindowWidth() / 2 - box_width / 2,
            Game::getInstance().getWindowHeight() - box_height,
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

void checkForOpponents() {
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
    for (auto &trainer : *Game::getInstance().getCurrentMap()) {
        if (trainer->canFight() and keepLooping[trainer.get()] and trainer->hasVisionOf(&Player::getPlayer())) {
            if (haltMusic) {
                Mix_HaltMusic();
                haltMusic = false;

                GraphicsEngine::getInstance().addGraphic<TimedVisual>(
                        "exclamation.png",
                        50 * (Game::getInstance().getFps() / 30) / 2,
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
            if (frameCounter < 50 * (Game::getInstance().getFps() / 30)) {
                return;
            }

            if (playMusic) {
                Mixer::getInstance().playMusic("GymBattle");
                playMusic = false;
            }

            if (not trainer->isNextTo(&Player::getPlayer())) {
                trainer->shift(trainer->getDirection(), Game::getInstance().getScrollSpeed());
                pixelsTraveled[trainer.get()] += Game::getInstance().getScrollSpeed();

                if (pixelsTraveled[trainer.get()] % (Constants::TILE_SIZE / 2) == 0) {
                    trainer->updateAnimation();
                }

                if (pixelsTraveled[trainer.get()] % Constants::TILE_SIZE == 0) {
                    trainer->moveForward();
                }
            }
            else {
                Player::getPlayer().face(trainer.get());

                createTextBox(trainer->getDialogue());

                keepLooping[trainer.get()] = false;

                frameCounter = 0;
                haltMusic = true;
                playMusic = true;
            }
            break;
        }
    }
}

void changeMap(const std::tuple<int, int, Map::Id> &data) {
    if (Mix_FadeOutMusic(2000) == 0) {
        std::clog << "Error fading out \"" << Game::getInstance().getCurrentMap()->getMusic() << "\": " << SDL_GetError() << '\n';
        SDL_ClearError();
        Game::getInstance().terminate();
        return;
    }

    Mix_HookMusicFinished([] -> void {
        Mixer::getInstance().playMusic(Game::getInstance().getCurrentMap()->getMusic().c_str());
    });

    Game::getInstance().getCurrentMap()->reset();

    // move the new map into the current map variable
    Game::getInstance().changeMap(std::get<2>(data));

    // resets the states of these variables for each trainer
    for (auto &trainer : *Game::getInstance().getCurrentMap()) {
        pixelsTraveled[trainer.get()] = 0;
        keepLooping[trainer.get()] = true;
    }

    Player::getPlayer().setCoordinates(std::get<0>(data), std::get<1>(data));

    Camera::getInstance().lockOnPlayer(Game::getInstance().getCurrentMap());
}

void Overworld::update() {
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

                if (Player::getPlayer().canMoveForward(Game::getInstance().getCurrentMap())) {
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
        for (auto &trainer : *Game::getInstance().getCurrentMap()) {
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
                        createTextBox(trainer->getDialogue());
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
                            Game::getInstance().setState(State::Id::BATTLE);
                            Game::getInstance().setRenderColor(Constants::Color::WHITE);
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

        Game::getInstance().getCurrentMap()->shift(oppositeDirection(Player::getPlayer().getDirection()),
                                                   Game::getInstance().getScrollSpeed());
        walkCounter += Game::getInstance().getScrollSpeed();
    }

    if (colliding) {
        if (bumpCounter == 10 * (Game::getInstance().getFps() / 30)) {
            Player::getPlayer().updateAnimation();
        }
        else if (bumpCounter == 20 * (Game::getInstance().getFps() / 30)) {
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
        const auto map_data = Game::getInstance().getCurrentMap()->isExitPointHere(Player::getPlayer().getX(), Player::getPlayer().getY());
        if (map_data.has_value()) {
            changeMap(map_data.value());
        }
    }

    for (auto &trainer : *Game::getInstance().getCurrentMap()) {
        trainer->act();
    }

    GraphicsEngine::getInstance().update();
}

void Overworld::render() {
    Game::getInstance().getCurrentMap()->render();
    GraphicsEngine::getInstance().render();
}
