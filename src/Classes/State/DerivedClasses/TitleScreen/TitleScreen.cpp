//
// Created by Miles on 1/28/2024.
//

#include "TitleScreen.h"
#include "../../../Singleton/DerivedClasses/Game/Game.h"

namespace {
    bool showPrompt = true;

    int flashSpeed = 30;
}

void TitleScreen::update() {
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

        Game::getInstance().loadData();

        Camera::getInstance().init(Game::getInstance().getWindowWidth(), Game::getInstance().getWindowHeight());
        Camera::getInstance().lockOnPlayer(Game::getInstance().getCurrentMap());

        for (auto &trainer : *Game::getInstance().getCurrentMap()) {
            pixelsTraveled[&trainer] = 0;
            keepLooping[&trainer] = true;
        }

        Mixer::getInstance().playMusic(Game::getInstance().getCurrentMap()->getMusic());

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
            Game::getInstance().getWindowWidth() / 2 - 8 * Constants::TILE_SIZE / 2, 0, 8 * Constants::TILE_SIZE, 5 * Constants::TILE_SIZE
    };
    static const SDL_Rect message_rect{
            Game::getInstance().getWindowWidth() / 2 - 24 * Game::getInstance().getFontSize() / 2,
            Game::getInstance().getWindowHeight() - Constants::TILE_SIZE * 2,
            Game::getInstance().getFontSize() * 23,
            Game::getInstance().getFontSize()
    };

    static Texture logo("PokemonLogo.png");

    static Texture text("Press enter to continue", Game::getInstance().getFont(), { 0, 0, 0, SDL_ALPHA_OPAQUE });


    TextureManager::getInstance().draw(logo.getTexture(), logo_rect);

    if (showPrompt) {
        TextureManager::getInstance().draw(text.getTexture(), message_rect);
    }
}
