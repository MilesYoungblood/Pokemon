//
// Created by Miles on 1/28/2024.
//

#include "../../../Game/Game.h"
#include "BattlePhase.h"

void renderMain() {
    int width;      // stores the text width
    int height;     // stores the text height

    static const int box_width = Map::TILE_SIZE * 7;
    static const int box_height = Map::TILE_SIZE * 2;
    static const SDL_Rect text_box(
            box_width / (Map::TILE_SIZE / 10) / 2,
            Game::WINDOW_HEIGHT - box_height,
            box_width / 2,
            box_height - Map::TILE_SIZE / 2
    );

    TextureManager::getInstance().drawRect(text_box, Constants::Color::BLACK,
                                           text_box.h / (Map::TILE_SIZE * 3 / 10));

    SDL_Rect button(
            Game::WINDOW_WIDTH - Map::TILE_SIZE / 10 - Game::WINDOW_WIDTH / 4 + Map::TILE_SIZE / 5,
            Game::WINDOW_HEIGHT - Map::TILE_SIZE / 2 - Map::TILE_SIZE / 2,
            Game::WINDOW_WIDTH / 4 - Map::TILE_SIZE / 2,
            Map::TILE_SIZE / 2
    );

    const int border_size = (Game::WINDOW_WIDTH / 2 - (Map::TILE_SIZE * 2 - Map::TILE_SIZE / 2)) /
                            (Map::TILE_SIZE * 3 / 10) / 5;

    // RUN
    TextureManager::getInstance().drawRect(button, { 0, 0, 255 }, Constants::Color::BLACK, border_size);

    // draw text
    TTF_SizeUTF8(TextureManager::getInstance().getFont(), "Run", &width, &height);
    TextureManager::getInstance().drawBorderedText("Run", button.x + button.w / 2 - width / 2,
                                                   button.y + button.h / 2 - height / 2, 2, Constants::Color::WHITE,
                                                   Constants::Color::BLACK);

    // BAG
    // update button position
    button.y = button.y - button.h - static_cast<int>(button.y * 0.025);

    TextureManager::getInstance().drawRect(button, { 255, 255, 0 }, Constants::Color::BLACK, border_size);

    // draw text
    TTF_SizeUTF8(TextureManager::getInstance().getFont(), "Bag", &width, &height);
    TextureManager::getInstance().drawBorderedText("Bag", button.x + button.w / 2 - width / 2,
                                                   button.y + button.h / 2 - height / 2, 2, Constants::Color::WHITE,
                                                   Constants::Color::BLACK);

    // FIGHT
    // update button position
    button.x = button.x - button.w - static_cast<int>(button.x * 0.025);

    TextureManager::getInstance().drawRect(button, { 255, 0, 0 }, Constants::Color::BLACK, border_size);

    TTF_SizeUTF8(TextureManager::getInstance().getFont(), "Fight", &width, &height);
    TextureManager::getInstance().drawBorderedText("Fight", button.x + button.w / 2 - width / 2,
                                                   button.y + button.h / 2 - height / 2, 2, { Constants::Color::WHITE },
                                                   Constants::Color::BLACK);

    // POKEMON
    // update button position
    button.y = Game::WINDOW_HEIGHT - Map::TILE_SIZE / 2 - Map::TILE_SIZE / 2;

    TextureManager::getInstance().drawRect(button, { 0, 255, 0 }, Constants::Color::BLACK, border_size);

    TTF_SizeUTF8(TextureManager::getInstance().getFont(), "Pokemon", &width, &height);
    TextureManager::getInstance().drawBorderedText("Pokemon", button.x + button.w / 2 - width / 2,
                                                   button.y + button.h / 2 - height / 2, 2, Constants::Color::WHITE,
                                                   Constants::Color::BLACK);

    Game::getInstance().setRenderColor(Constants::Color::WHITE);
}

enum class BattleState : Uint8 {
    MAIN
};

namespace {
    BattleState battleState = BattleState::MAIN;
    std::unordered_map<BattleState, void (*)()> battleFunctions(
            {
                    std::make_pair(BattleState::MAIN, renderMain)
            }
    );
}

void BattlePhase::update() {
    GraphicsEngine::getInstance().update();
}

void BattlePhase::render() {
    battleFunctions.at(battleState)();
    GraphicsEngine::getInstance().render();

    Game::getInstance().setRenderColor(Constants::Color::WHITE);
}
