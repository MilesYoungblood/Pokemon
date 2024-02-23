//
// Created by Miles on 1/28/2024.
//

#include "../../../Game/Game.h"
#include "BattlePhase.h"

void BattlePhase::initMain() {
    const int box_width = Map::TILE_SIZE * 7;
    const int box_height = Map::TILE_SIZE * 2;
    const SDL_Rect text_box(
            box_width / (Map::TILE_SIZE / 10) / 2,
            Game::WINDOW_HEIGHT - box_height,
            box_width / 2,
            box_height - Map::TILE_SIZE / 2
    );

    GraphicsEngine::getInstance().addGraphic<TextBox>(
            text_box,
            text_box.h / (Map::TILE_SIZE * 3 / 10),
            text_box.x + Map::TILE_SIZE / 10,
            text_box.y + Map::TILE_SIZE / 10
    );
    GraphicsEngine::getInstance().getGraphic<TextBox>().push("What will " + Player::getPlayer()[0].getName() + " do?");

    GraphicsEngine::getInstance().addGraphic<ResourceBar>(
            SDL_Rect(Game::WINDOW_WIDTH - 200 - 50, 50, 200, 10),
            Constants::Color::GREEN,
            Constants::Color::BLACK,
            5,
            100
    );

    SDL_Rect button(
            Game::WINDOW_WIDTH - Map::TILE_SIZE / 10 - Game::WINDOW_WIDTH / 4 + Map::TILE_SIZE / 5,
            Game::WINDOW_HEIGHT - Map::TILE_SIZE / 2 - Map::TILE_SIZE / 2,
            Game::WINDOW_WIDTH / 4 - Map::TILE_SIZE / 2,
            Map::TILE_SIZE / 2
    );
    const int border_size = (Game::WINDOW_WIDTH / 2 - (Map::TILE_SIZE * 2 - Map::TILE_SIZE / 2)) /
                            (Map::TILE_SIZE * 3 / 10) / 5;

    GraphicsEngine::getInstance().addGraphic<Button>(
            button,
            Constants::Color::BLUE,
            border_size,
            "Run",
            nullptr
    );

    button.y = button.y - button.h - static_cast<int>(button.y * 0.025);
    GraphicsEngine::getInstance().addGraphic<Button>(
            button,
            Constants::Color::YELLOW,
            border_size,
            "Bag",
            nullptr
    );

    button.x = button.x - button.w - static_cast<int>(button.x * 0.025);
    GraphicsEngine::getInstance().addGraphic<Button>(
            button,
            Constants::Color::RED,
            border_size,
            "Fight",
            nullptr
    );

    button.y = Game::WINDOW_HEIGHT - Map::TILE_SIZE / 2 - Map::TILE_SIZE / 2;
    GraphicsEngine::getInstance().addGraphic<Button>(
            button,
            Constants::Color::GREEN,
            border_size,
            "Pokemon",
            nullptr
    );
}

void BattlePhase::init() {
    this->INIT_FUNCTIONS[static_cast<std::size_t>(BattlePhase::BattleState::MAIN)]();
}

void BattlePhase::update() {
    if (not this->isRunning) {
        Game::getInstance().setState(State::Id::OVERWORLD);
        return;
    }

    GraphicsEngine::getInstance().update();
}

void BattlePhase::render() {
    GraphicsEngine::getInstance().render();
    this->RENDER_FUNCTIONS.at(static_cast<std::size_t>(this->currentState))();

    Game::getInstance().setRenderColor(Constants::Color::WHITE);
}
