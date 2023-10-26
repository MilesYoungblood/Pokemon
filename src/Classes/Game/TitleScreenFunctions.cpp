//
// Created by Miles Youngblood on 10/25/2023.
//

#include "Game.h"

const int extension_length = 4;
std::string_view music_path;
std::string_view song_name;

int counter = 0;
bool showPrompt = true;

void handleTitleScreenEvents() {
    switch (event.type) {
        case SDL_QUIT:
            isRunning = false;
            SDL_DestroyTexture(logo);
            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.scancode) {
                case SDL_SCANCODE_RETURN:
                    functionState = 1;

                    Mix_HaltMusic();
                    Mix_FreeMusic(gameMusic);

                    maps[0] = std::move(std::make_unique<Map>("Route 1", "TrainerBattle.mp3", 13, 10));
                    maps[0]->addTrainer(std::make_unique<Trainer>(7, 6, 1, 3));
                    maps[0]->addTrainer(std::make_unique<Trainer>(2, 4, 1, 3));
                    maps[0]->addExitPoint({ 6, 0, MapID::ROUTE_2, 10, 18 });

                    maps[1] = std::move(std::make_unique<Map>("Route 2", "RivalBattle.mp3", 21, 20));
                    maps[1]->addExitPoint({ 10, 19, MapID::ROUTE_1, 6, 1 });
                    maps[1]->addExitPoint({ 0, 10, MapID::ROUTE_3, 19, 5 });

                    maps[2] = std::move(std::make_unique<Map>("Route 3", "GymBattle.mp3", 21, 11));
                    maps[2]->addExitPoint({ 20, 5, MapID::ROUTE_2, 1, 10 });

                    Game::loadData();

                    music_path = currentMap->getMusic();
                    song_name = music_path.substr(0, music_path.length() - extension_length);

                    gameMusic = Mix_LoadMUS(std::string_view(PROJECT_PATH + "\\music\\" + currentMap->getMusic()).data());
                    if (gameMusic != nullptr) {
                        std::cout << "Loaded \"" << song_name << "\"!\n";
                    }
                    else {
                        std::cerr << "Could not play music: " << SDL_GetError() << '\n';
                        Player::destroyPlayer();
                        Mix_CloseAudio();
                        SDL_DestroyRenderer(gameRenderer);
                        SDL_DestroyWindow(gameWindow);
                        SDL_Quit();
                        abort();
                    }

                    Mix_PlayMusic(gameMusic, -1);
                    std::cout << "Playing \"" << song_name << "\"!\n";

                    Camera::lockOnPlayer(player, [](Direction direct, int dist) -> void { currentMap->updateMap(direct, dist); });

                    walkCounters = std::vector<int>(currentMap->numTrainers(), 0);
                    lockTrainer = std::vector<bool>(currentMap->numTrainers(), false);

                    SDL_DestroyTexture(logo);
                    SDL_DestroyTexture(text);
                    SDL_SetRenderDrawColor(gameRenderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
                    break;
                default:
                    return;
                    // TODO
            }
            break;
    }
}

void updateTitleScreen() {
    ++counter;
    if (counter == 30) {
        showPrompt = not showPrompt;
        counter = 0;
    }
}

void renderTitleScreen() {
    SDL_RenderClear(gameRenderer);
    TextureManager::Draw(logo, { WINDOW_WIDTH / 2 - 8 * TILE_SIZE / 2, 0, 8 * TILE_SIZE, 5 * TILE_SIZE });

    if (showPrompt) {
        TextureManager::Draw(text, { WINDOW_WIDTH / 2 - 24 * FONT_SIZE / 2, WINDOW_HEIGHT - TILE_SIZE * 2, 23 * FONT_SIZE, FONT_SIZE });
    }
    SDL_RenderPresent(gameRenderer);
}