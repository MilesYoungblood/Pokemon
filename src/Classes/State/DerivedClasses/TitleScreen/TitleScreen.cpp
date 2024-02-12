//
// Created by Miles on 1/28/2024.
//

#include "../../../Singleton/DerivedClasses/Game/Game.h"

namespace {
    bool showPrompt = true;
}

void TitleScreen::update() {
    static int flashSpeed = 30;

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

        Overworld::getInstance().load();

        Camera::getInstance().init(Game::WINDOW_WIDTH, Game::WINDOW_HEIGHT);
        Camera::getInstance().lockOnPlayer(Overworld::getInstance().getCurrentMap());

        for (auto &trainer : *Overworld::getInstance().getCurrentMap()) {
            keepLooping[&trainer] = true;
        }

        Mixer::getInstance().playMusic(Overworld::getInstance().getCurrentMap()->getMusic());

        Game::getInstance().setState(State::Id::OVERWORLD);
        Game::getInstance().setRenderColor(Constants::Color::BLACK);
    }

    static int counter = 0;
    if (++counter == flashSpeed) {
        showPrompt = not showPrompt;
        counter = 0;
    }
}

void TitleScreen::render() {
    static const SDL_Rect logo_rect{
            Game::WINDOW_WIDTH / 2 - 8 * Map::TILE_SIZE / 2,
            0,
            8 * Map::TILE_SIZE,
            5 * Map::TILE_SIZE
    };
    static const SDL_Rect message_rect{
            Game::WINDOW_WIDTH / 2 - 24 * Game::FONT_SIZE / 2,
            Game::WINDOW_HEIGHT - Map::TILE_SIZE * 2,
            Game::FONT_SIZE * 23,
            Game::FONT_SIZE
    };

    static Texture logo("PokemonLogo.png");
    static Texture text("Press enter to continue", Constants::Color::BLACK);

    TextureManager::getInstance().draw(logo.getTexture(), logo_rect);

    if (showPrompt) {
        TextureManager::getInstance().draw(text.getTexture(), message_rect);
    }
}
