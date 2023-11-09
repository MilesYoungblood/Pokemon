//
// Created by Miles Youngblood on 10/25/2023.
//

#include "Game.h"

namespace {
    bool showPrompt = true;

    int flashSpeed = 30;
}

void Game::handleTitleScreenEvents() {
    switch (Game::event.type) {
        case SDL_QUIT:
            Game::isRunning = false;
            break;
        case SDL_KEYDOWN:
            switch (Game::event.key.keysym.scancode) {
                case SDL_SCANCODE_RETURN:
                    flashSpeed = 10;
                    showPrompt = false;

                    Mix_FreeMusic(Game::music);
                    SoundPlayer::getInstance().playSound(SoundPlayer::SoundId::SELECTION);

                    Game::loadData();

                    const static int extension_length = 4;
                    const static std::string_view music_path(currentMap->getMusic());
                    const static std::string_view song_name(music_path.substr(0, music_path.length() - extension_length));

                    Game::music = Mix_LoadMUS(std::string_view(PROJECT_PATH + "\\music\\" + currentMap->getMusic()).data());
                    if (Game::music != nullptr) {
                        std::cout << "Loaded \"" << song_name << "\"!\n";
                    }
                    else {
                        std::cerr << "Error loading \"" << song_name << "\": " << SDL_GetError() << '\n';
                        SDL_ClearError();
                        Game::isRunning = false;
                        return;
                    }

                    if (Mix_PlayMusic(Game::music, -1) == 0) {
                        std::cout << "Playing \"" << song_name << "\"!\n";
                    }
                    else {
                        std::cerr << "Unable to play \"" << song_name << "\": " << SDL_GetError() << '\n';
                        SDL_ClearError();
                        Game::isRunning = false;
                        return;
                    }

                    Camera::getInstance().init(Game::WINDOW_WIDTH, Game::WINDOW_HEIGHT);
                    Camera::getInstance().lockOnPlayer(Player::getPlayer(), [](Direction direct, int dist) -> void {
                        currentMap->shift(direct, dist);
                    });

                    distanceTraveled = std::vector<int>(currentMap->numTrainers(), 0);
                    lockTrainer = std::vector<bool>(currentMap->numTrainers(), false);
                    keepLooping = std::vector<bool>(currentMap->numTrainers(), true);

                    SDL_DestroyTexture(Game::logo);
                    if (strlen(SDL_GetError()) == 0) {
                        std::cout << "Texture destroyed!\n";
                    }
                    else {
                        std::cerr << "Error destroying texture: " << SDL_GetError() << '\n';
                        SDL_ClearError();
                        Game::isRunning = false;
                    }
                    SDL_DestroyTexture(Game::text);
                    if (strlen(SDL_GetError()) == 0) {
                        std::cout << "Texture destroyed!\n";
                    }
                    else {
                        std::cerr << "Error destroying texture: " << SDL_GetError() << '\n';
                        SDL_ClearError();
                        Game::isRunning = false;
                    }
                    SDL_SetRenderDrawColor(Game::renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);

                    Game::currentState = State::OVERWORLD;

                    break;
                default:
                    // TODO
                    break;
            }
            break;
    }
}

void Game::updateTitleScreen() {
    static int counter = 0;
    if (++counter == flashSpeed) {
        showPrompt = not showPrompt;
        counter = 0;
    }
}

void Game::renderTitleScreen() {
    const SDL_Rect logo_rect{
            Game::WINDOW_WIDTH / 2 - 8 * TILE_SIZE / 2, 0, 8 * TILE_SIZE, 5 * TILE_SIZE
    };
    const SDL_Rect message_rect{
            Game::WINDOW_WIDTH / 2 - 24 * Game::FONT_SIZE / 2,
            Game::WINDOW_HEIGHT - TILE_SIZE * 2,
            23 * Game::FONT_SIZE,
            Game::FONT_SIZE
    };

    TextureManager::getInstance().draw(Game::logo, logo_rect);

    if (showPrompt) {
        TextureManager::getInstance().draw(Game::text, message_rect);
    }
}
