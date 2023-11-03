//
// Created by Miles Youngblood on 10/25/2023.
//

#include "Game.h"

bool showPrompt = true;

void handleTitleScreenEvents() {
    switch (event.type) {
        case SDL_QUIT:
            isRunning = false;
            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.scancode) {
                case SDL_SCANCODE_RETURN:
                    Mix_FreeMusic(gameMusic);

                    static Mix_Chunk *sound = Mix_LoadWAV(std::string_view(PROJECT_PATH + "\\SFX\\selection.wav").data());
                    if (sound != nullptr) {
                        std::cout << "Loaded \"selection\"!\n";
                    }
                    else {
                        std::cerr << "Unable to load \"selection\": " << SDL_GetError() << '\n';
                        isRunning = false;
                        return;
                    }

                    if (Mix_PlayChannel(-1, sound, 0) == 0) {
                        std::cout << "Playing \"selection\"!\n";
                    }
                    else {
                        std::cerr << "Unable to play \"selection\": " << SDL_GetError() << '\n';
                        isRunning = false;
                        return;
                    }

                    Mix_ChannelFinished([](int at) -> void {
                        Mix_FreeChunk(Mix_GetChunk(at));
                    });

                    Game::loadData();

                    const static int extension_length = 4;
                    const static std::string_view music_path = currentMap->getMusic();
                    const static std::string_view song_name = music_path.substr(0, music_path.length() - extension_length);

                    gameMusic = Mix_LoadMUS(std::string_view(PROJECT_PATH + "\\music\\" + currentMap->getMusic()).data());
                    if (gameMusic != nullptr) {
                        std::cout << "Loaded \"" << song_name << "\"!\n";
                    }
                    else {
                        std::cerr << "Error loading \"" << song_name << "\": " << SDL_GetError() << '\n';
                        isRunning = false;
                        return;
                    }

                    if (Mix_PlayMusic(gameMusic, -1) == 0) {
                        std::cout << "Playing \"" << song_name << "\"!\n";
                    }
                    else {
                        std::cerr << "Unable to play \"" << song_name << "\": " << SDL_GetError() << '\n';
                        isRunning = false;
                        return;
                    }

                    Camera::getInstance()->init(WINDOW_WIDTH, WINDOW_HEIGHT);
                    Camera::getInstance()->lockOnPlayer(player, [](Direction direct, int dist) -> void {
                        currentMap->update(direct, dist);
                    });

                    walkCounters = std::vector<int>(currentMap->numTrainers(), 0);
                    lockTrainer = std::vector<bool>(currentMap->numTrainers(), false);

                    SDL_DestroyTexture(logo);
                    SDL_DestroyTexture(text);
                    SDL_SetRenderDrawColor(gameRenderer, 0, 0, 0, SDL_ALPHA_OPAQUE);

                    functionState = OVERWORLD;

                    break;
                default:
                    // TODO
                    break;
            }
            break;
    }
}

void updateTitleScreen() {
    static int counter = 0;
    if (++counter == 30) {
        showPrompt = not showPrompt;
        counter = 0;
    }
}

void renderTitleScreen() {
    const static SDL_Rect logo_rect{
            WINDOW_WIDTH / 2 - 8 * TILE_SIZE / 2, 0, 8 * TILE_SIZE, 5 * TILE_SIZE
    };
    const static SDL_Rect message_rect{
            WINDOW_WIDTH / 2 - 24 * FONT_SIZE / 2,
            WINDOW_HEIGHT - TILE_SIZE * 2,
            23 * FONT_SIZE,
            FONT_SIZE
    };

    TextureManager::getInstance()->draw(logo, logo_rect);

    if (showPrompt) {
        TextureManager::getInstance()->draw(text, message_rect);
    }
}
