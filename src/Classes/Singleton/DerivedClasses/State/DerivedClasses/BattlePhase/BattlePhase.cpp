//
// Created by Miles on 1/28/2024.
//

#include "../../../Game/Game.h"
#include "BattlePhase.h"

void BattlePhase::initMain() {
    const int double_tile = Map::TILE_SIZE * 2;
    const int half_tile = Map::TILE_SIZE / 2;
    const int tenth_tile = Map::TILE_SIZE / 10;
    const int half_window_height = Game::WINDOW_HEIGHT / 2;

    const SDL_Rect text_box(
            Game::WINDOW_HEIGHT / tenth_tile / 2,
            Game::WINDOW_HEIGHT - double_tile,
            half_window_height,
            double_tile - half_tile
    );

    GraphicsEngine::getInstance().addGraphic<TextBox>(
            text_box,
            text_box.h / (tenth_tile * 3),
            text_box.x + tenth_tile,
            text_box.y + tenth_tile
    );
    GraphicsEngine::getInstance().getGraphic<TextBox>().push("What will " + Player::getPlayer()[0].getName() + " do?");

    GraphicsEngine::getInstance().addGraphic<ResourceBar>(
            SDL_Rect(Game::WINDOW_WIDTH - 250, Map::TILE_SIZE * 4, 200, 10),
            Constants::Color::GREEN,
            5,
            100
    );

    const int border_size = (Game::WINDOW_WIDTH / 2 - (double_tile - half_tile)) / (tenth_tile * 3) / 5;

    GraphicsEngine::getInstance().addGraphic<Panel>(
            SDL_Rect(
                    Game::WINDOW_WIDTH - (half_window_height + Game::WINDOW_HEIGHT / 10) - (half_tile),
                    Game::WINDOW_HEIGHT - double_tile,
                    half_window_height + Game::WINDOW_HEIGHT / 10,
                    double_tile - half_tile
            ),
            Constants::Color::GRAY,
            text_box.h / (tenth_tile * 3),
            2,
            2,
            Game::WINDOW_WIDTH / 4 - half_tile,
            half_tile,
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
}

void BattlePhase::init(Trainer *trainer, bool isTrainer) {
    this->opponent = trainer;
    this->canRunAway = isTrainer;
    this->INIT_FUNCTIONS[static_cast<std::size_t>(BattlePhase::BattleState::MAIN)]();
}

void BattlePhase::update() {
    if (not this->isRunning) {
        this->opponent = nullptr;
        this->turn = 0;

        this->skipPlayer = false;
        this->skipOpponent = false;

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
