//
// Created by Miles Youngblood on 10/25/2023.
//

#include "Game.h"

namespace {
    bool showPrompt = true;

    int flashSpeed = 30;
}

void Game::handleTitleScreenEvents() {
    if (this->event.type == SDL_EventType::SDL_QUIT) {
        this->isRunning = false;
    }
}

void Game::updateTitleScreen() {
    if (KeyManager::getInstance().getKey(SDL_Scancode::SDL_SCANCODE_RETURN)) {
        Mix_FreeMusic(this->music);

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

        // FIXME make code following this execute based on MixChannelFinished callback
        SoundPlayer::getInstance().playSound(SoundPlayer::SoundId::SELECTION);

        this->loadData();

        Camera::getInstance().init(this->WINDOW_WIDTH, this->WINDOW_HEIGHT);
        Camera::getInstance().lockOnPlayer([](Direction direct, int dist) -> void {
            Game::getInstance().currentMap->shift(direct, dist);
        });

        pixelsTraveled = std::vector<int>(currentMap->numTrainers(), 0);
        lockTrainer = std::vector<bool>(currentMap->numTrainers(), false);
        keepLooping = std::vector<bool>(currentMap->numTrainers(), true);

        SDL_DestroyTexture(this->logo);
        if (strlen(SDL_GetError()) > 0ULL) {
            std::clog << "Error destroying texture: " << SDL_GetError() << '\n';
            SDL_ClearError();
        }
        SDL_DestroyTexture(this->text);
        if (strlen(SDL_GetError()) > 0ULL) {
            std::clog << "Error destroying texture: " << SDL_GetError() << '\n';
            SDL_ClearError();
        }

        SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);

        this->music = Mix_LoadMUS(std::string_view("../assets/audio/music/" + currentMap->getMusic() + ".mp3").data());
        if (this->music == nullptr) {
            std::clog << "Error loading \"" << currentMap->getMusic() << "\": " << SDL_GetError() << '\n';
            SDL_ClearError();
            this->isRunning = false;
            return;
        }

        if (Mix_PlayMusic(this->music, -1) == -1) {
            std::clog << "Error playing \"" << currentMap->getMusic() << "\": " << SDL_GetError() << '\n';
            SDL_ClearError();
            this->isRunning = false;
            return;
        }

        this->currentState = Game::State::OVERWORLD;
    }

    static int counter = 0;
    if (++counter == flashSpeed) {
        showPrompt = not showPrompt;
        counter = 0;
    }
}

void Game::renderTitleScreen() {
    const SDL_Rect logo_rect{
            this->WINDOW_WIDTH / 2 - 8 * TILE_SIZE / 2, 0, 8 * TILE_SIZE, 5 * TILE_SIZE
    };
    const SDL_Rect message_rect{
            this->WINDOW_WIDTH / 2 - 24 * this->FONT_SIZE / 2,
            this->WINDOW_HEIGHT - TILE_SIZE * 2,
            23 * this->FONT_SIZE,
            this->FONT_SIZE
    };

    TextureManager::getInstance().draw(this->logo, logo_rect);

    if (showPrompt) {
        TextureManager::getInstance().draw(this->text, message_rect);
    }
}
