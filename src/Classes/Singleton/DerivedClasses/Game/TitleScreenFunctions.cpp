//
// Created by Miles Youngblood on 10/25/2023.
//

#include "Game.h"

namespace {
    bool showPrompt = true;

    int flashSpeed = 30;
}

void Game::updateTitleScreen() {
    if (KeyManager::getInstance().getKey(SDL_Scancode::SDL_SCANCODE_RETURN)) {
        Mix_HaltMusic();

        // re-lock the Enter key
        KeyManager::getInstance().lockKey(SDL_Scancode::SDL_SCANCODE_RETURN);

        // sets a cool-down period before the Enter key can be registered again;
        // this is needed because the program will register a button
        // being pressed faster than the user can lift their finger
        std::thread coolDown([] -> void {
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            KeyManager::getInstance().unlockKey(SDL_Scancode::SDL_SCANCODE_RETURN);
        });
        coolDown.detach();

        flashSpeed = 10;
        showPrompt = false;

        // FIXME make code following this execute based on MixChannelFinished callback
        Mixer::getInstance().playSound("select");

        this->loadData();

        Camera::getInstance().init(this->WINDOW_WIDTH, this->WINDOW_HEIGHT);
        Camera::getInstance().lockOnPlayer(this->currentMap);

        for (auto &trainer : *this->currentMap) {
            pixelsTraveled[&trainer] = 0;
            keepLooping[&trainer] = true;
        }

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

        Mixer::getInstance().playMusic(this->currentMap->getMusic().c_str());

        this->currentState = Game::State::OVERWORLD;
    }

    static int counter = 0;
    if (++counter == flashSpeed) {
        showPrompt = not showPrompt;
        counter = 0;
    }
}

void Game::renderTitleScreen() {
    static const SDL_Rect logo_rect{
            this->WINDOW_WIDTH / 2 - 8 * Constants::TILE_SIZE / 2, 0, 8 * Constants::TILE_SIZE, 5 * Constants::TILE_SIZE
    };
    static const SDL_Rect message_rect{
            this->WINDOW_WIDTH / 2 - 24 * this->FONT_SIZE / 2,
            this->WINDOW_HEIGHT - Constants::TILE_SIZE * 2,
            this->FONT_SIZE * 23,
            this->FONT_SIZE
    };

    TextureManager::getInstance().draw(this->logo, logo_rect);

    if (showPrompt) {
        TextureManager::getInstance().draw(this->text, message_rect);
    }
}
