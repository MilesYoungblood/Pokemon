//
// Created by Miles Youngblood on 10/24/2023.
//

#include "Game.h"

const static std::string string = "Pokemon White is the best Pokemon game of all time!";
int wordCounter = 0;

constexpr static int BOX_WIDTH = TILE_SIZE * 7;
constexpr static int BOX_HEIGHT = TILE_SIZE * 2;

constexpr SDL_Rect textBox(
        WINDOW_WIDTH / 2 - BOX_WIDTH / 2,
        WINDOW_HEIGHT - BOX_HEIGHT,
        BOX_WIDTH,
        BOX_HEIGHT - TILE_SIZE / 2
);

constexpr static int BORDER_SIZE = textBox.h / (TILE_SIZE * 3 / 10);
constexpr SDL_Rect border(
        textBox.x - BORDER_SIZE,
        textBox.y - BORDER_SIZE,
        textBox.w + BORDER_SIZE * 2,
        textBox.h + BORDER_SIZE * 2
);

int width;
int height;

void handleOverworldKeyDown() {
    switch (event.key.keysym.scancode) {
        case SDL_SCANCODE_RETURN:
            pressedEnter = true;
            break;
        default:
            if (not canMove) {
                return;
            }
            switch (event.key.keysym.scancode) {
                case SDL_SCANCODE_W:
                    if (not player->isFacingNorth()) {
                        player->faceNorth();
                    }
                    else {
                        moveDirection[Direction::UP] = true;
                        keepMovingDirection[Direction::UP] = true;
                    }
                    break;
                case SDL_SCANCODE_A:
                    if (not player->isFacingWest()) {
                        player->faceWest();
                    }
                    else {
                        moveDirection[Direction::LEFT] = true;
                        keepMovingDirection[Direction::LEFT] = true;
                    }
                    break;
                case SDL_SCANCODE_S:
                    if (not player->isFacingSouth()) {
                        player->faceSouth();
                    }
                    else {
                        moveDirection[Direction::DOWN] = true;
                        keepMovingDirection[Direction::DOWN] = true;
                    }
                    break;
                case SDL_SCANCODE_D:
                    if (not player->isFacingEast()) {
                        player->faceEast();
                    }
                    else {
                        moveDirection[Direction::RIGHT] = true;
                        keepMovingDirection[Direction::RIGHT] = true;
                    }
                    break;
                default:
                    return;
            }
    }
}

void handleOverworldEvents() {
    switch (event.type) {
        case SDL_QUIT:
            Game::saveData();
            isRunning = false;
            break;

        case SDL_KEYDOWN:
            // do not accept keyboard input if your sprite is still moving
            if (keepMovingDirection[0] or keepMovingDirection[1] or keepMovingDirection[2] or keepMovingDirection[3]) {
                return;
            }
            handleOverworldKeyDown();
            break;

        case SDL_KEYUP:
            switch (event.key.keysym.scancode) {
                case SDL_SCANCODE_W:
                    moveDirection[Direction::UP] = false;
                    break;
                case SDL_SCANCODE_A:
                    moveDirection[Direction::LEFT] = false;
                    break;
                case SDL_SCANCODE_S:
                    moveDirection[Direction::DOWN] = false;
                    break;
                case SDL_SCANCODE_D:
                    moveDirection[Direction::RIGHT] = false;
                    break;
                default:
                    break;
            }
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

    Mix_HookMusicFinished([] -> void {
        Mix_FreeMusic(gameMusic);

        gameMusic = Mix_LoadMUS(std::string_view(PROJECT_PATH + "\\music\\" + currentMap->getMusic()).data());
        if (gameMusic != nullptr) {
            const std::string_view music_path(currentMap->getMusic());
            const std::string_view song_name = music_path.substr(0, music_path.length() - extension_length);
            std::cout << "Loaded \"" << song_name << "\"!\n";

            Mix_PlayMusic(gameMusic, -1);
            std::cout << "Playing \"" << song_name << "\"!\n";
        }
    });

    currentMap->resetMap();

    // move the old map back into the array
    maps.at(currentMapIndex) = std::move(currentMap);

    // move the new map into the current map variable
    currentMapIndex = data[2];
    currentMap = std::move(maps.at(currentMapIndex));

    // resets the states of these variables for each trainer
    walkCounters = std::vector<int>(currentMap->numTrainers(), 0);
    lockTrainer = std::vector<bool>(currentMap->numTrainers(), false);

    player->setCoordinates(data[0], data[1]);

    Camera::lockOnPlayer(player, [](Direction direct, int dist) -> void { currentMap->updateMap(direct, dist); });
}

void checkForOpponents() {
    void (*resetVariables)() = [] -> void {
        keepMovingDirection[0] = false;
        keepMovingDirection[1] = false;
        keepMovingDirection[2] = false;
        keepMovingDirection[3] = false;
        walkCounter = 0;
    };

    // resets movement variables if you are not inputting any directions
    if (not (moveDirection[0] or moveDirection[1] or moveDirection[2] or moveDirection[3])) {
        resetVariables();
    }

    Trainer *trainer;

    // checks if the player is in LoS for any trainer
    for (int i = 0; i < currentMap->numTrainers(); ++i) {
        trainer = &(*currentMap)[i];

        if (not lockTrainer[i] and trainer->hasVisionOf(player) and *trainer) {
            resetVariables();
            canMove = false;
            lockTrainer[i] = true;

            if (trainer->isNextTo(player)) {
                // TODO open dialogue, start battle
                // functionState = 1;
                player->face(trainer);
                print = true;
                trainer->clearParty();
                walkCounters[i] = 0;
            }

            trainer->shiftDirectionOnMap(trainer->getDirection(), SCROLL_SPEED);
            walkCounters[i] += SCROLL_SPEED;

            if (walkCounters[i] % TILE_SIZE == 0) {
                trainer->moveForward();
            }

            break;
        }
    }
}

void updateTrainers() {
    Trainer *trainer;

    // FIXME possibly make trainers turn slower
    for (int i = 0; i < currentMap->numTrainers(); ++i) {
        // does not potentially make the trainer move spontaneously if true
        if (lockTrainer[i]) {
            continue;
        }

        trainer = &(*currentMap)[i];
        switch (generateInteger(1, 100)) {
            case 1:
                trainer->face(trainer);

                if (trainer->hasVisionOf(player) and *trainer) {
                    canMove = false;
                    return;
                }
                break;

            case 2:
                if (trainer->isFacingNorth() or trainer->isFacingSouth()) {
                    coinFlip() ? trainer->faceEast() : trainer->faceWest();
                }
                else if (trainer->isFacingEast() or trainer->isFacingWest()) {
                    coinFlip() ? trainer->faceNorth() : trainer->faceSouth();
                }

                if (trainer->hasVisionOf(player) and *trainer) {
                    canMove = false;
                    return;
                }
                break;
        }
    }
}

void updateOverworld() {
    const Direction pDirection = player->getDirection();

    const std::array<int, 3> mapData = currentMap->isExitPointHere(player->getX(), player->getY());
    if (mapData[2] != -1) {
        changeMap(mapData);
    }
    else if (pressedEnter) {
        Trainer *trainer;       // variable used to reduce the number of function calls

        for (int i = 0; i < currentMap->numTrainers(); ++i) {
            if (not canInteract) {
                break;
            }
            trainer = &(*currentMap)[i];

            if (player->hasVisionOf(trainer)) {
                // FIXME does not take into account multiple pages
                trainer->face(player);
                print = not print;
                canInteract = not print;
                lockTrainer[i] = not lockTrainer[i];
                canMove = not canMove;
                wordCounter = 0;

                SDL_DestroyTexture(text);
                break;
            }
        }
        pressedEnter = false;
    }
    else if (player->canMoveForward(currentMap.get()) and (moveDirection.at(pDirection) or keepMovingDirection.at(pDirection))) {
        const Direction qDirection = oppositeDirection(pDirection);

        currentMap->updateMap(qDirection, SCROLL_SPEED);
        walkCounter += SCROLL_SPEED;

        if (walkCounter % TILE_SIZE == 0) {
            player->moveForward();
        }
    }

    // if the player's sprite is on a tile...
    if (walkCounter % TILE_SIZE == 0) {
        checkForOpponents();
    }

    updateTrainers();
}

void renderTextBox() {
    // first draw the border of the dialogue box
    SDL_RenderFillRect(gameRenderer, &border);
    SDL_SetRenderDrawColor(gameRenderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

    // then draw the inner dialogue box in front of the border
    SDL_RenderFillRect(gameRenderer, &textBox);
    SDL_SetRenderDrawColor(gameRenderer, 0, 0, 0, SDL_ALPHA_OPAQUE);

    // if the string has not yet completed concatenation
    if (string.length() >= wordCounter) {
        //safe delete the current texture
        SDL_DestroyTexture(text);

        // buffer is required to store the substring
        const std::string buffer = wordCounter > 0 ? string.substr(0, wordCounter) : " ";

        // recreate the texture
        SDL_Surface *temp = TTF_RenderUTF8_Blended_Wrapped(textFont, buffer.c_str(), {0, 0, 0 }, textBox.w);
        text = SDL_CreateTextureFromSurface(gameRenderer, temp);

        width = temp->w;
        height = temp->h;

        SDL_FreeSurface(temp);

        // increment the word counter
        ++wordCounter;
    }
    else {
        canInteract = true;
    }

    // draw the current message to the renderer
    TextureManager::Draw(text, { textBox.x + TILE_SIZE / 10, textBox.y + TILE_SIZE / 10, width, height });
}

void renderOverworld() {
    currentMap->renderMap();
    player->render();

    if (print) {
        renderTextBox();
    }
}
