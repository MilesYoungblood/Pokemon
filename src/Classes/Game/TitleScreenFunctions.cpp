//
// Created by Miles Youngblood on 10/25/2023.
//

#include "Game.h"
#include <future>

namespace {
    bool showPrompt = true;

    int flashSpeed = 30;
}

void Game::handleTitleScreenEvents() {
    if (Game::event.type == SDL_EventType::SDL_QUIT) {
        Game::isRunning = false;
    }
}

void Game::updateTitleScreen() {
    if (KeyManager::getInstance().getKey(SDL_Scancode::SDL_SCANCODE_RETURN)) {
        Mix_FreeMusic(Game::music);

        // re-lock the Enter key
        KeyManager::getInstance().lockKey(SDL_Scancode::SDL_SCANCODE_RETURN);

        // sets a cool-down period before the Enter key can be registered again
        std::thread coolDown([] -> void {
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            KeyManager::getInstance().unlockKey(SDL_Scancode::SDL_SCANCODE_RETURN);
        });
        coolDown.detach();

        flashSpeed = 10;
        showPrompt = false;

        SoundPlayer::getInstance().playSound(SoundPlayer::SoundId::SELECTION);

        Game::loadData();

        Game::music = Mix_LoadMUS(
                std::string_view(PROJECT_PATH + R"(\assets\audio\music\)" + currentMap->getMusic() + ".mp3").data());
        if (Game::music == nullptr) {
            std::clog << "Error loading \"" << currentMap->getMusic() << "\": " << SDL_GetError() << '\n';
            SDL_ClearError();
            Game::isRunning = false;
            return;
        }

        if (Mix_PlayMusic(Game::music, -1) == -1) {
            std::clog << "Error playing \"" << currentMap->getMusic() << "\": " << SDL_GetError() << '\n';
            SDL_ClearError();
            Game::isRunning = false;
            return;
        }

        Camera::getInstance().init(Game::WINDOW_WIDTH, Game::WINDOW_HEIGHT);
        Camera::getInstance().lockOnPlayer(Player::getPlayer(), [](Direction direct, int dist) -> void {
            currentMap->shift(direct, dist);
        });

        pixelsTraveled = std::vector<int>(currentMap->numTrainers(), 0);
        lockTrainer = std::vector<bool>(currentMap->numTrainers(), false);
        keepLooping = std::vector<bool>(currentMap->numTrainers(), true);

        SDL_DestroyTexture(Game::logo);
        if (strlen(SDL_GetError()) > 0ULL) {
            std::clog << "Error destroying texture: " << SDL_GetError() << '\n';
            SDL_ClearError();
            Game::isRunning = false;
        }
        SDL_DestroyTexture(Game::text);
        if (strlen(SDL_GetError()) > 0ULL) {
            std::clog << "Error destroying texture: " << SDL_GetError() << '\n';
            SDL_ClearError();
            Game::isRunning = false;
        }
        SDL_SetRenderDrawColor(Game::renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);

        Game::currentState = Game::State::OVERWORLD;
    }

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
        //TextureManager::getInstance().drawBorderedText("Press Enter to start!", message_rect.x, message_rect.y,
        //                                               { 255, 255, 255 }, { 0, 0, 0 }, Game::font);
    }
}
