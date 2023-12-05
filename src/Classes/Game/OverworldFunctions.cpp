//
// Created by Miles Youngblood on 10/24/2023.
//

#include "Game.h"

int letterCounter = 0;

int walkCounter = 0;                                     // measures how many screen pixels the player has moved

bool keepMovingForward = false;                          // ultimately, determine when the player stops moving
bool momentum = false;                                   // denotes whether the player is still moving

Stopwatch<std::chrono::milliseconds> timer;

void Game::handleOverworldEvents() {
    switch (this->event.type) {
        case SDL_EventType::SDL_QUIT:
            this->saveData();
            this->isRunning = false;
            break;

        case SDL_EventType::SDL_KEYDOWN:
            timer.start();
            break;

        case SDL_EventType::SDL_KEYUP:
            timer.stop();
            break;

        default:
            break;
    }
}

void Game::changeMap(const std::tuple<int, int, Map::Id> &data) {
    if (Mix_FadeOutMusic(2000) == 0) {
        std::clog << "Error fading out \"" << currentMap->getMusic() << "\": " << SDL_GetError() << '\n';
        SDL_ClearError();
        this->isRunning = false;
        return;
    }

    Mix_HookMusicFinished([] -> void {
        Mix_FreeMusic(Game::getInstance().music);

        Game::getInstance().music = Mix_LoadMUS(std::string_view(
                "../assets/audio/music/" + Game::getInstance().currentMap->getMusic() + ".mp3").data());
        if (Game::getInstance().music == nullptr) {
            std::clog << "Error loading \"" << Game::getInstance().currentMap->getMusic() << "\": " << SDL_GetError()
                      << '\n';
            SDL_ClearError();
            Game::getInstance().isRunning = false;
            return;
        }

        if (Mix_PlayMusic(Game::getInstance().music, -1) == -1) {
            std::clog << "Error playing \"" << Game::getInstance().currentMap->getMusic() << "\": " << SDL_GetError()
                      << '\n';
            SDL_ClearError();
            Game::getInstance().isRunning = false;
            return;
        }
    });

    this->currentMap->reset();

    // move the new map into the current map variable
    this->currentMapIndex = std::get<2>(data);
    this->currentMap = &this->maps.at(this->currentMapIndex);

    // resets the states of these variables for each trainer
    pixelsTraveled = std::vector<int>(this->currentMap->numTrainers(), 0);
    lockTrainer = std::vector<bool>(this->currentMap->numTrainers(), false);
    keepLooping = std::vector<bool>(this->currentMap->numTrainers(), true);

    Player::getPlayer().setCoordinates(std::get<0>(data), std::get<1>(data));

    Camera::getInstance().lockOnPlayer([](Direction direct, int dist) -> void {
        Game::getInstance().currentMap->shift(direct, dist);
    });
}

void Game::checkForOpponents() {
    void (*resetVariables)() = [] -> void {
        momentum = false;
        keepMovingForward = false;
        walkCounter = 0;
    };

    // resets movement variables if you are not inputting any directions
    if (not(KeyManager::getInstance().getKey(SDL_Scancode::SDL_SCANCODE_W) or
            KeyManager::getInstance().getKey(SDL_Scancode::SDL_SCANCODE_A) or
            KeyManager::getInstance().getKey(SDL_Scancode::SDL_SCANCODE_S) or
            KeyManager::getInstance().getKey(SDL_Scancode::SDL_SCANCODE_D))) {
        resetVariables();
    }

    Trainer *trainer;               // variable to reduce the number of function calls

    static int waitCounter = 0;     // makes a trainer that spotted the player stand still for a set amount of time
    static bool freeMusic = true;
    static bool haltMusic = true;

    // checks if the player is in LoS for any trainer
    for (int i = 0; i < this->currentMap->numTrainers(); ++i) {
        trainer = &(*this->currentMap)[i];

        if (*trainer and keepLooping[i] and trainer->hasVisionOf(&Player::getPlayer())) {
            if (haltMusic) {
                Mix_HaltMusic();
                haltMusic = false;
            }

            KeyManager::getInstance().blockInput();
            resetVariables();
            lockTrainer[i] = true;

            ++waitCounter;
            if (waitCounter < 50 * (this->currentFps / 30)) {
                continue;
            }

            if (freeMusic) {
                Mix_FreeMusic(this->music);

                this->music = Mix_LoadMUS("../assets/audio/music/GymBattle.mp3");
                if (this->music == nullptr) {
                    std::clog << "Error loading \"GymBattle\": " << SDL_GetError() << '\n';
                    SDL_ClearError();
                    this->isRunning = false;
                    return;
                }

                if (Mix_PlayMusic(this->music, -1) == -1) {
                    std::clog << "Error playing \"GymBattle\": " << SDL_GetError() << '\n';
                    SDL_ClearError();
                    this->isRunning = false;
                    return;
                }

                freeMusic = false;
            }

            if (not trainer->isNextTo(&Player::getPlayer())) {
                trainer->shiftDirectionOnMap(trainer->getDirection(), this->SCROLL_SPEED);
                pixelsTraveled[i] += this->SCROLL_SPEED;

                if (pixelsTraveled[i] % (Constants::TILE_SIZE / 2) == 0) {
                    trainer->updateAnimation();
                }

                if (pixelsTraveled[i] % Constants::TILE_SIZE == 0) {
                    trainer->moveForward();
                }
            }
            else {
                Player::getPlayer().face(trainer);
                print = true;
                keepLooping[i] = false;
                letterCounter = 0;

                waitCounter = 0;
                freeMusic = true;
                haltMusic = true;
            }
            break;
        }
    }
}

void Game::updateTrainers() const {
    for (int i = 0; i < this->currentMap->numTrainers(); ++i) {
        // does not potentially make the trainer move spontaneously if true
        if (lockTrainer[i]) {
            continue;
        }

        Trainer *entity = &(*this->currentMap)[i];

        switch (generateInteger(1, 100 * this->currentFps / 30)) {
            case 1:
                entity->face(entity);
                break;

            case 2:
                if (entity->isFacingNorth() or entity->isFacingSouth()) {
                    binomial() ? entity->setDirection(Direction::LEFT) : entity->setDirection(Direction::RIGHT);
                }
                else {
                    binomial() ? entity->setDirection(Direction::UP) : entity->setDirection(Direction::DOWN);
                }
                break;
        }
    }
}

void Game::updateOverworld() {
    static void (*startWalking)() = [] -> void {
        KeyManager::getInstance().lockWasd();
        keepMovingForward = true;

        momentum = true;
        timer.stop();
        timer.reset();
    };

    if (KeyManager::getInstance().getKey(SDL_Scancode::SDL_SCANCODE_W)) {
        if (not Player::getPlayer().isFacingNorth()) {
            Player::getPlayer().setDirection(Direction::UP);
        }
        if (KeyManager::getInstance().getKey(SDL_Scancode::SDL_SCANCODE_W) and
            Player::getPlayer().canMoveForward(this->currentMap) and (momentum or timer >= 10)) {
            startWalking();
        }
    }
    else if (KeyManager::getInstance().getKey(SDL_Scancode::SDL_SCANCODE_A)) {
        if (not Player::getPlayer().isFacingWest()) {
            Player::getPlayer().setDirection(Direction::LEFT);
        }
        if (KeyManager::getInstance().getKey(SDL_Scancode::SDL_SCANCODE_A) and
            Player::getPlayer().canMoveForward(this->currentMap) and (momentum or timer >= 10)) {
            startWalking();
        }
    }
    else if (KeyManager::getInstance().getKey(SDL_Scancode::SDL_SCANCODE_S)) {
        if (not Player::getPlayer().isFacingSouth()) {
            Player::getPlayer().setDirection(Direction::DOWN);
        }
        if (KeyManager::getInstance().getKey(SDL_Scancode::SDL_SCANCODE_S) and
            Player::getPlayer().canMoveForward(this->currentMap) and (momentum or timer >= 10)) {
            startWalking();
        }
    }
    else if (KeyManager::getInstance().getKey(SDL_Scancode::SDL_SCANCODE_D)) {
        if (not Player::getPlayer().isFacingEast()) {
            Player::getPlayer().setDirection(Direction::RIGHT);
        }
        if (KeyManager::getInstance().getKey(SDL_Scancode::SDL_SCANCODE_D) and
            Player::getPlayer().canMoveForward(this->currentMap) and (momentum or timer >= 10)) {
            startWalking();
        }
    }
    else if (KeyManager::getInstance().getKey(SDL_Scancode::SDL_SCANCODE_RETURN) and not keepMovingForward) {
        for (int i = 0; i < this->currentMap->numTrainers(); ++i) {
            if (Player::getPlayer().hasVisionOf(&(*this->currentMap)[i])) {
                // FIXME does not take into account multiple pages
                (*this->currentMap)[i].face(&Player::getPlayer());
                print = currentPage <= numPages;
                if (print) {
                    KeyManager::getInstance().blockInput();
                    ++currentPage;
                }
                else {
                    currentPage = 0;
                    // re-lock the Enter key
                    KeyManager::getInstance().lockKey(SDL_Scancode::SDL_SCANCODE_RETURN);

                    // sets a cool-down period before the Enter key can be registered again
                    AutoThread::run([] -> void {
                        std::this_thread::sleep_for(std::chrono::milliseconds(500));
                        KeyManager::getInstance().unlockKey(SDL_Scancode::SDL_SCANCODE_RETURN);
                    });
                    KeyManager::getInstance().unlockWasd();

                    if ((*this->currentMap)[i]) {
                        Mix_FreeMusic(this->music);

                        this->music = Mix_LoadMUS("../assets/audio/music/TrainerBattle.mp3");
                        if (this->music == nullptr) {
                            std::clog << "Error loading \"TrainerBattle\": " << SDL_GetError() << '\n';
                            SDL_ClearError();
                            this->isRunning = false;
                            return;
                        }

                        if (Mix_PlayMusic(this->music, -1) == -1) {
                            std::clog << "Error playing \"TrainerBattle\": " << SDL_GetError() << '\n';
                            SDL_ClearError();
                            this->isRunning = false;
                            return;
                        }

                        this->currentState = Game::State::BATTLE;
                        SDL_SetRenderDrawColor(this->renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
                    }
                }
                lockTrainer[i] = print;
                letterCounter = 0;

                SDL_DestroyTexture(this->text);
                if (strlen(SDL_GetError()) > 0ULL) {
                    std::clog << "Error destroying texture (texture may have already been deleted): "
                              << SDL_GetError() << '\n';
                    SDL_ClearError();
                }

                timer.reset();
                break;
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

    // if the player's sprite is on a tile...
    if (walkCounter % Constants::TILE_SIZE == 0) {
        if (not print) {
            KeyManager::getInstance().unlockWasd();
        }

        keepMovingForward = false;

        checkForOpponents();
        const auto map_data = this->currentMap->isExitPointHere(Player::getPlayer().getX(), Player::getPlayer().getY());
        if (map_data) {
            this->changeMap(map_data.value());
        }
    }

    updateTrainers();
}

void Game::renderTextBox(const std::string &message = "Pokemon White is the best Pokemon game of all time!") {
    const static int box_width = Constants::TILE_SIZE * 7;
    const static int box_height = Constants::TILE_SIZE * 2;
    const static SDL_Rect text_box{
            this->WINDOW_WIDTH / 2 - box_width / 2,
            this->WINDOW_HEIGHT - box_height,
            box_width,
            box_height - Constants::TILE_SIZE / 2
    };

    const static int border_size{ text_box.h / (Constants::TILE_SIZE * 3 / 10) };

    TextureManager::getInstance().drawRect(text_box, { 255, 255, 255 }, { 0, 0, 0 }, border_size);

    static int width;
    static int height;

    // if the string has not yet completed concatenation
    if (message.length() >= letterCounter) {
        //safe delete the current texture
        SDL_DestroyTexture(this->text);
        if (strlen(SDL_GetError()) > 0ULL) {
            std::clog << "Error destroying texture: " << SDL_GetError() << '\n';
            SDL_ClearError();
        }

        // buffer is required to store the substring
        const std::string buffer = letterCounter > 0 ? message.substr(0, letterCounter) : " ";

        // recreate the texture
        SDL_Surface *temp = TTF_RenderUTF8_Blended_Wrapped(this->font, buffer.c_str(), { 0, 0, 0 }, text_box.w);
        text = SDL_CreateTextureFromSurface(this->renderer, temp);

        // save the width and height of the text just in case next iteration, this branch isn't executed
        width = temp->w;
        height = temp->h;

        SDL_FreeSurface(temp);

        // increment the word counter
        ++letterCounter;
    }
    else {
        // unlocks Enter once the message has finished printing
        KeyManager::getInstance().unlockKey(SDL_Scancode::SDL_SCANCODE_RETURN);
    }

    // render the current message to the renderer
    TextureManager::getInstance().draw(this->text,
                                       { text_box.x + Constants::TILE_SIZE / 10, text_box.y + Constants::TILE_SIZE / 10, width, height });
}

void Game::renderOverworld() {
    this->currentMap->render();
    Player::getPlayer().render();

    if (print) {
        this->renderTextBox();
    }
}
