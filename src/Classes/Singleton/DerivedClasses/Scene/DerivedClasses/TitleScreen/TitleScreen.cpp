//
// Created by Miles on 1/28/2024.
//

#include "../../../Game/Game.h"
#include "../../../Camera/Camera.h"
#include "../../../Mixer/Mixer.h"
#include "../../../KeyManager/KeyManager.h"
#include "../../../../../Graphic/DerivedClasses/Texture/Texture.h"

namespace {
    bool showPrompt = true;
}

void TitleScreen::update() {
    static int flashSpeed = 30;

    if (KeyManager::getInstance().getKey(SDL_SCANCODE_RETURN)) {
        Mix_HaltMusic();

        // re-lock the Enter key
        KeyManager::getInstance().lock(SDL_SCANCODE_RETURN);

        // sets a cool-down period before the Enter key can be registered again;
        // this is needed because the program will register a button
        // being pressed faster than the user can lift their finger
        std::thread coolDown([] -> void {
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            KeyManager::getInstance().unlock(SDL_SCANCODE_RETURN);
        });
        coolDown.detach();

        flashSpeed = 10;
        showPrompt = false;

        // FIXME make code following this execute based on MixChannelFinished callback
        Mixer::getInstance().playSound("select");

        getInstance<Overworld>().init();

        Camera::getInstance().lockOnPlayer(getInstance<Overworld>().getCurrentMap());

        Mixer::getInstance().playMusic(getInstance<Overworld>().getCurrentMap().getMusic());

        Game::getInstance().changeScene(Id::OVERWORLD);
        Game::getInstance().setRenderColor(Constants::Color::BLACK);
    }

    static int counter = 0;
    if (++counter == flashSpeed) {
        showPrompt = not showPrompt;
        counter = 0;
    }
}

void TitleScreen::render() const {
    static constexpr SDL_Rect logo_rect(
            Game::WINDOW_WIDTH / 2 - 8 * Map::TILE_SIZE / 2,
            0,
            8 * Map::TILE_SIZE,
            5 * Map::TILE_SIZE
    );
    static constexpr SDL_Rect message_rect(
            Game::WINDOW_WIDTH / 2 - 24 * Game::FONT_SIZE / 2,
            Game::WINDOW_HEIGHT - Map::TILE_SIZE * 2,
            Game::FONT_SIZE * 23,
            Game::FONT_SIZE
    );

    static const Texture logo("PokemonLogo.png", logo_rect);
    static const Texture text("Press enter to continue", Constants::Color::BLACK, message_rect);

    logo.render();

    if (showPrompt) {
        text.render();
    }
}
