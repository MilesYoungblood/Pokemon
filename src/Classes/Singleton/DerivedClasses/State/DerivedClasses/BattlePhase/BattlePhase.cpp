//
// Created by Miles on 1/28/2024.
//

#include "../../../Game/Game.h"
#include "BattlePhase.h"

void BattlePhase::handleInput() {
    static bool consecutive = false;

    if (KeyManager::getInstance().getKey(SDL_Scancode::SDL_SCANCODE_W)) {
        if (not consecutive) {
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
            SDL_Rect(Game::WINDOW_WIDTH - 250, Map::TILE_SIZE * 4, 200, 10),
            Constants::Color::GREEN,
            5,
            100
    );

    this->options = std::vector<std::vector<Button *>>(2, std::vector<Button *>(2, nullptr));

    SDL_Rect button(
            Game::WINDOW_WIDTH - Map::TILE_SIZE / 10 - Game::WINDOW_WIDTH / 4 + Map::TILE_SIZE / 5,
            Game::WINDOW_HEIGHT - static_cast<Uint16>(Map::TILE_SIZE),
            Game::WINDOW_WIDTH / 4 - Map::TILE_SIZE / 2,
            Map::TILE_SIZE / 2
    );
    const int border_size = (Game::WINDOW_WIDTH / 2 - (Map::TILE_SIZE * 2 - Map::TILE_SIZE / 2)) /
                            (Map::TILE_SIZE * 3 / 10) / 5;

    GraphicsEngine::getInstance().addGraphic<Panel>(
            SDL_Rect(
                    10,
                    10,
                    box_width / 2 + box_width / 10,
                    box_height - Map::TILE_SIZE / 2
            ),
            Constants::Color::GRAY,
            text_box.h / (Map::TILE_SIZE * 3 / 10),
            2,
            2,
            Game::WINDOW_WIDTH / 4 - Map::TILE_SIZE / 2,
            Map::TILE_SIZE / 2,
            border_size
    );

    GraphicsEngine::getInstance().getGraphic<Panel>().add<0, 0>(
            Constants::Color::RED,
            "Fight",
            nullptr
    );
    GraphicsEngine::getInstance().getGraphic<Panel>().add<0, 1>(
            Constants::Color::YELLOW,
            "Bag",
            nullptr
    );
    GraphicsEngine::getInstance().getGraphic<Panel>().add<1, 0>(
            Constants::Color::GREEN,
            "Pokemon",
            nullptr
    );
    GraphicsEngine::getInstance().getGraphic<Panel>().add<1, 1>(
            Constants::Color::BLUE,
            "Run",
            nullptr
    );

    GraphicsEngine::getInstance().addGraphic<Button>(
            button,
            Constants::Color::BLUE,
            border_size,
            "Run",
            [this] -> void {
                GraphicsEngine::getInstance().getGraphic<TextBox>().pop();
                if (not this->canRunAway) {
                    GraphicsEngine::getInstance().getGraphic<TextBox>().push("You can't run away from a trainer battle!");
                }
                else {
                    const int opponent_speed = static_cast<int>((*this->opponent)[0].getBaseStat(Pokemon::Stat::SPEED) / 4) % 256;
                    const int odds = static_cast<int>((Player::getPlayer()[0].getBaseStat(Pokemon::Stat::SPEED) * 32) / opponent_speed) + 30;

                    if (opponent_speed == 0 or odds > 255 or generateInteger(0, 255) < odds) {
                        GraphicsEngine::getInstance().getGraphic<TextBox>().push("Got away safely!");
                        std::thread thread([this] -> void {
                            while (GraphicsEngine::getInstance().getGraphic<TextBox>().isPrinting()) {
                                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                            }
                            this->isRunning = false;
                            GraphicsEngine::getInstance().clear();

                            if (Mix_FadeOutMusic(2000) == 0) {
                                std::clog << "Error fading out \"" << State::getInstance<Overworld>().getCurrentMap()->getMusic() << "\": "
                                          << SDL_GetError() << '\n';
                                SDL_ClearError();
                                Game::getInstance().terminate();
                                return;
                            }

                            Mix_HookMusicFinished([] -> void {
                                Mixer::getInstance().playMusic(State::getInstance<Overworld>().getCurrentMap()->getMusic());
                            });
                        });
                        thread.detach();
                    }
                    else {
                        GraphicsEngine::getInstance().getGraphic<TextBox>().push("Couldn't get away");
                    }
                }
            }
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

    button.y = Game::WINDOW_HEIGHT - static_cast<Uint16>(Map::TILE_SIZE);
    GraphicsEngine::getInstance().addGraphic<Button>(
            button,
            Constants::Color::GREEN,
            border_size,
            "Pokemon",
            nullptr
    );

    this->options[0][1] = &GraphicsEngine::getInstance().getGraphic<Button>(3);
}

void BattlePhase::init(Trainer *trainer, bool isTrainer) {
    this->opponent = trainer;
    this->canRunAway = isTrainer;
    this->INIT_FUNCTIONS[static_cast<std::size_t>(BattlePhase::BattleState::MAIN)]();
}

void BattlePhase::update() {
    if (not this->isRunning) {
        this->options.clear();
        this->col = 0;
        this->row = 0;

        this->opponent = nullptr;
        this->turn = 0;

        this->skipPlayer = false;
        this->skipOpponent = false;

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
