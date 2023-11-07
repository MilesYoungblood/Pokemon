//
// Created by Miles Youngblood on 10/24/2023.
//

#include <span>
#include "Game.h"

namespace {
    int letterCounter = 0;

    int walkCounter = 0;                                     // measures how many screen pixels the player has moved

    bool keepMovingForward = false;                          // ultimately, determine when the player stops moving

    Stopwatch timer;
}

void handleOverworldEvents() {
    switch (event.type) {
        case SDL_QUIT:
            timer.stop();
            Game::saveData();
            isRunning = false;
            break;

        case SDL_KEYDOWN:
            // do not accept keyboard input if your sprite is still moving
            if (keepMovingForward) {
                return;
            }
            KeyManager::getInstance().keyDown(event.key.keysym.scancode);
            timer.start();
            break;

        case SDL_KEYUP:
            switch (event.key.keysym.scancode) {
                case SDL_SCANCODE_W:
                    KeyManager::getInstance().keyUp(SDL_SCANCODE_W);
                    break;
                case SDL_SCANCODE_A:
                    KeyManager::getInstance().keyUp(SDL_SCANCODE_A);
                    break;
                case SDL_SCANCODE_S:
                    KeyManager::getInstance().keyUp(SDL_SCANCODE_S);
                    break;
                case SDL_SCANCODE_D:
                    KeyManager::getInstance().keyUp(SDL_SCANCODE_D);
                    break;
                default:
                    break;
            }
            timer.stop();
            break;

        default:
            break;
    }
}

void changeMap(const std::array<int, 3> &data) {
    const int extension_length = 4;
    const std::string_view music_path(currentMap->getMusic());

    if (Mix_FadeOutMusic(2000) != 0) {
        std::cout << "Fading out \"" << music_path.substr(0, music_path.length() - extension_length) << "\"!\n";
    }
    else {
        std::cerr << "Error fading out \"" << music_path.substr(0, music_path.length() - extension_length) << "\":"
                  << SDL_GetError() << '\n';
        SDL_ClearError();
        isRunning = false;
        return;
    }

    Mix_HookMusicFinished([] -> void {
        Mix_FreeMusic(gameMusic);

        const std::string_view music_path(currentMap->getMusic());
        const std::string_view song_name = music_path.substr(0, music_path.length() - extension_length);

        gameMusic = Mix_LoadMUS(std::string_view(PROJECT_PATH + "\\music\\" + currentMap->getMusic()).data());
        if (gameMusic != nullptr) {
            std::cout << "Loaded \"" << song_name << "\"!\n";
        }
        else {
            std::cerr << "Error loading \"" << song_name << "\": " << SDL_GetError() << '\n';
            SDL_ClearError();
            isRunning = false;
            return;
        }

        if (Mix_PlayMusic(gameMusic, -1) == 0) {
            std::cout << "Playing \"" << song_name << "\"!\n";
        }
        else {
            std::cerr << "Error playing \"" << song_name << "\": " << SDL_GetError() << '\n';
            SDL_ClearError();
            isRunning = false;
            return;
        }
    });

    currentMap->resetMap();

    // move the new map into the current map variable
    currentMapIndex = data[2];
    currentMap = &maps.at(currentMapIndex);

    // resets the states of these variables for each trainer
    walkCounters = std::vector<int>(currentMap->numTrainers(), 0);
    lockTrainer = std::vector<bool>(currentMap->numTrainers(), false);
    keepLooping = std::vector<bool>(currentMap->numTrainers(), true);

    Player::getPlayer().setCoordinates(data[0], data[1]);

    Camera::getInstance().lockOnPlayer(Player::getPlayer(), [](Direction direct, int dist) -> void {
        currentMap->shift(direct, dist);
    });
}

void checkForOpponents() {
    static void (*resetVariables)() = [] -> void {
        keepMovingForward = false;
        walkCounter = 0;
    };

    // resets movement variables if you are not inputting any directions
    if (not(KeyManager::getInstance().getKey(SDL_SCANCODE_W) or
            KeyManager::getInstance().getKey(SDL_SCANCODE_A) or
            KeyManager::getInstance().getKey(SDL_SCANCODE_S) or
            KeyManager::getInstance().getKey(SDL_SCANCODE_D))) {
        resetVariables();
    }

    Trainer *trainer;       // variable to reduce the number of function calls

    static int waitCounter = 0;

    // checks if the player is in LoS for any trainer
    for (int i = 0; i < currentMap->numTrainers(); ++i) {
        trainer = &(*currentMap)[i];

        if (*trainer and keepLooping[i] and trainer->hasVisionOf(&Player::getPlayer())) {
            KeyManager::getInstance().lockWasd();
            KeyManager::getInstance().lockKey(SDL_SCANCODE_RETURN);
            resetVariables();
            lockTrainer[i] = true;

            ++waitCounter;
            if (waitCounter < 50 * (currentFps / 30)) {
                continue;
            }

            if (not trainer->isNextTo(&Player::getPlayer())) {
                trainer->shiftDirectionOnMap(trainer->getDirection(), SCROLL_SPEED);
                walkCounters[i] += SCROLL_SPEED;

                if (walkCounters[i] % (TILE_SIZE / 2) == 0) {
                    trainer->updateAnimation();
                }

                if (walkCounters[i] % TILE_SIZE == 0) {
                    trainer->moveForward();
                }
            }
            else {
                Player::getPlayer().face(trainer);
                print = true;
                keepLooping[i] = false;
                letterCounter = 0;

                waitCounter = 0;
            }
            break;
        }
    }
}

void updateTrainers() {
    for (int i = 0; i < currentMap->numTrainers(); ++i) {
        // does not potentially make the trainer move spontaneously if true
        if (lockTrainer[i]) {
            continue;
        }

        Trainer *entity = &(*currentMap)[i];

        switch (generateInteger(1, 100 * currentFps / 30)) {
            case 1:
                entity->face(entity);
                break;

            case 2:
                if (entity->isFacingNorth() or entity->isFacingSouth()) {
                    coinFlip() ? entity->faceEast() : entity->faceWest();
                }
                else {
                    coinFlip() ? entity->faceNorth() : entity->faceSouth();
                }
                break;
        }
    }
}

void updateOverworld() {
    if (KeyManager::getInstance().getKey(SDL_SCANCODE_W)) {
        if (not Player::getPlayer().isFacingNorth()) {
            Player::getPlayer().faceNorth();
        }
        if (KeyManager::getInstance().get(SDL_SCANCODE_W) and Player::getPlayer().canMoveForward(currentMap) and
            timer.getElapsedTime() >= 10) {
            keepMovingForward = true;
            timer.reset();
        }
    }
    else if (KeyManager::getInstance().getKey(SDL_SCANCODE_A)) {
        if (not Player::getPlayer().isFacingWest()) {
            Player::getPlayer().faceWest();
        }
        if (KeyManager::getInstance().get(SDL_SCANCODE_A) and Player::getPlayer().canMoveForward(currentMap) and
            timer.getElapsedTime() >= 10) {
            keepMovingForward = true;
            timer.reset();
        }
    }
    else if (KeyManager::getInstance().getKey(SDL_SCANCODE_S)) {
        if (not Player::getPlayer().isFacingSouth()) {
            Player::getPlayer().faceSouth();
        }
        if (KeyManager::getInstance().get(SDL_SCANCODE_S) and Player::getPlayer().canMoveForward(currentMap) and
            timer.getElapsedTime() >= 10) {
            keepMovingForward = true;
            timer.reset();
        }
    }
    else if (KeyManager::getInstance().getKey(SDL_SCANCODE_D)) {
        if (not Player::getPlayer().isFacingEast()) {
            Player::getPlayer().faceEast();
        }
        if (KeyManager::getInstance().get(SDL_SCANCODE_D) and Player::getPlayer().canMoveForward(currentMap) and
            timer.getElapsedTime() >= 10) {
            keepMovingForward = true;
            timer.reset();
        }
    }
    else if (KeyManager::getInstance().getKey(SDL_SCANCODE_RETURN)) {
        for (int i = 0; i < currentMap->numTrainers(); ++i) {
            if (Player::getPlayer().hasVisionOf(&(*currentMap)[i])) {
                // FIXME does not take into account multiple pages
                (*currentMap)[i].face(&Player::getPlayer());
                print = not print;
                if (print) {
                    KeyManager::getInstance().lockKey(SDL_SCANCODE_RETURN);
                    KeyManager::getInstance().lockWasd();
                }
                else {
                    KeyManager::getInstance().unlockKey(SDL_SCANCODE_RETURN);
                    KeyManager::getInstance().unlockWasd();
                }
                lockTrainer[i] = print;
                letterCounter = 0;

                SDL_DestroyTexture(text);
                if (strlen(SDL_GetError()) == 0ULL) {
                    std::cout << "Texture destroyed!\n";
                }
                else {
                    std::cerr << "Error destroying texture (texture may have already been deleted): "
                              << SDL_GetError() << '\n';
                    SDL_ClearError();
                }

                // FIXME possibly get rid of second expression
                if ((*currentMap)[i] and not print) {
                    //TODO this is where battle would start
                }
                break;
            }
        }
        KeyManager::getInstance().keyUp(SDL_SCANCODE_RETURN);
    }

    const std::array<int, 3> map_data = currentMap->isExitPointHere(Player::getPlayer().getX(), Player::getPlayer().getY());
    if (keepMovingForward) {
        if (walkCounter % (TILE_SIZE / 2) == 0) {
            Player::getPlayer().updateAnimation();
        }
        if (walkCounter % TILE_SIZE == 0) {
            Player::getPlayer().moveForward();

            if (map_data[2] != -1) {
                changeMap(map_data);
            }
        }

        currentMap->shift(oppositeDirection(Player::getPlayer().getDirection()), SCROLL_SPEED);
        walkCounter += SCROLL_SPEED;
    }

    // if the player's sprite is on a tile...
    if (walkCounter % TILE_SIZE == 0) {
        if (not Player::getPlayer().canMoveForward(currentMap)) {
            keepMovingForward = false;
        }
        checkForOpponents();
        if (map_data[2] != -1) {
            changeMap(map_data);
        }
    }

    updateTrainers();
}

void renderTextBox(const std::string &message = "Pokemon White is the best Pokemon game of all time!") {
    const static int box_width = TILE_SIZE * 7;
    const static int box_height = TILE_SIZE * 2;
    const static SDL_Rect text_box{
            WINDOW_WIDTH / 2 - box_width / 2,
            WINDOW_HEIGHT - box_height,
            box_width,
            box_height - TILE_SIZE / 2
    };

    const static int border_size = text_box.h / (TILE_SIZE * 3 / 10);
    const static SDL_Rect border{
            text_box.x - border_size,
            text_box.y - border_size,
            text_box.w + border_size * 2,
            text_box.h + border_size * 2
    };

    // first draw the border of the dialogue box
    SDL_RenderFillRect(gameRenderer, &border);
    SDL_SetRenderDrawColor(gameRenderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

    // then draw the inner dialogue box in front of the border
    SDL_RenderFillRect(gameRenderer, &text_box);
    SDL_SetRenderDrawColor(gameRenderer, 0, 0, 0, SDL_ALPHA_OPAQUE);

    static int width;
    static int height;

    // if the string has not yet completed concatenation
    if (message.length() >= letterCounter) {
        //safe delete the current texture
        SDL_DestroyTexture(text);
        if (strlen(SDL_GetError()) == 0) {
            std::cout << "Texture destroyed!\n";
        }
        else {
            std::cerr << "Error destroying texture: " << SDL_GetError() << '\n';
            SDL_ClearError();
        }

        // buffer is required to store the substring
        const std::string buffer = letterCounter > 0 ? message.substr(0, letterCounter) : " ";

        // recreate the texture
        SDL_Surface *temp = TTF_RenderUTF8_Blended_Wrapped(textFont, buffer.c_str(), { 0, 0, 0 }, text_box.w);
        text = SDL_CreateTextureFromSurface(gameRenderer, temp);

        // save the width and height of the text just in case next iteration, this branch isn't executed
        width = temp->w;
        height = temp->h;

        SDL_FreeSurface(temp);

        // increment the word counter
        ++letterCounter;
    }
    else {
        // unlocks Enter once the message has finished printing
        KeyManager::getInstance().unlockKey(SDL_SCANCODE_RETURN);
    }

    // draw the current message to the renderer
    TextureManager::getInstance().draw(text,
                                        { text_box.x + TILE_SIZE / 10, text_box.y + TILE_SIZE / 10, width, height });
}

void renderOverworld() {
    currentMap->render();
    Player::getPlayer().render();

    if (print) {
        renderTextBox();
    }
}
