//
// Created by Miles on 1/28/2024.
//

#include "../../../Game/Game.h"
#include "BattlePhase.h"

void BattlePhase::handleInput() {
    static bool consecutive = false;

    if (KeyManager::getInstance().getKey(SDL_Scancode::SDL_SCANCODE_W)) {
        if (not consecutive) {
            GraphicsEngine::getInstance().removeGraphic<Texture>();
            GraphicsEngine::getInstance().addGraphic<Texture>(
                    "RightArrow.png",
                    SDL_Rect(

                    )
            );
            this->row = std::max(0, this->row - 1);
            consecutive = true;
        }
    }
    else if (KeyManager::getInstance().getKey(SDL_Scancode::SDL_SCANCODE_A)) {
        if (not consecutive) {
            this->col = std::max(0, this->col - 1);
            consecutive = true;
        }
    }
    else if (KeyManager::getInstance().getKey(SDL_Scancode::SDL_SCANCODE_S)) {
        if (not consecutive) {
            this->row = std::min(this->row + 1, static_cast<int>(this->options.size()) - 1);
            consecutive = true;
        }
    }
    else if (KeyManager::getInstance().getKey(SDL_Scancode::SDL_SCANCODE_D)) {
        if (not consecutive) {
            this->col = std::min(this->col + 1, static_cast<int>(this->options.size()) - 1);
            consecutive = true;
        }
    }
    else if (KeyManager::getInstance().getKey(SDL_Scancode::SDL_SCANCODE_RETURN)) {
        if (not consecutive) {
            this->options[this->col][this->row]->click();
            consecutive = true;
        }
    }
    else {
        consecutive = false;
    }
}

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
            SDL_Rect(Game::WINDOW_WIDTH - 200 - 50, Map::TILE_SIZE * 4, 200, 10),
            Constants::Color::GREEN,
            Constants::Color::BLACK,
            5,
            100
    );

    this->options = std::vector<std::vector<Button *>>(2, std::vector<Button *>(2, nullptr));

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

    this->options[1][1] = &GraphicsEngine::getInstance().getGraphic<Button>(0);

    button.y = button.y - button.h - static_cast<int>(button.y * 0.025);
    GraphicsEngine::getInstance().addGraphic<Button>(
            button,
            Constants::Color::YELLOW,
            border_size,
            "Bag",
            nullptr
    );

    this->options[1][0] = &GraphicsEngine::getInstance().getGraphic<Button>(1);

    button.x = button.x - button.w - static_cast<int>(button.x * 0.025);
    GraphicsEngine::getInstance().addGraphic<Button>(
            button,
            Constants::Color::RED,
            border_size,
            "Fight",
            nullptr
    );

    this->options[0][0] = &GraphicsEngine::getInstance().getGraphic<Button>(2);

    button.y = Game::WINDOW_HEIGHT - Map::TILE_SIZE / 2 - Map::TILE_SIZE / 2;
    GraphicsEngine::getInstance().addGraphic<Button>(
            button,
            Constants::Color::GREEN,
            border_size,
            "Pokemon",
            nullptr
    );

    this->options[0][1] = &GraphicsEngine::getInstance().getGraphic<Button>(3);
}

void BattlePhase::init() {
    this->INIT_FUNCTIONS[static_cast<std::size_t>(BattlePhase::BattleState::MAIN)]();
}

void BattlePhase::update() {
    if (not this->isRunning) {
        Game::getInstance().setState(State::Id::OVERWORLD);
        return;
    }

    this->handleInput();
    GraphicsEngine::getInstance().update();
}

void BattlePhase::render() {
    GraphicsEngine::getInstance().render();
    this->RENDER_FUNCTIONS.at(static_cast<std::size_t>(this->currentState))();

    Game::getInstance().setRenderColor(Constants::Color::WHITE);
}
