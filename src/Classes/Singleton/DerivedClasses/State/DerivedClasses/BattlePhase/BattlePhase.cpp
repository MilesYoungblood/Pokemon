//
// Created by Miles on 1/28/2024.
//

#include "../../../Game/Game.h"
#include "BattlePhase.h"

void BattlePhase::initMain() {
    GraphicsEngine::getInstance().clear();

    const int double_tile = Map::TILE_SIZE * 2;
    const int half_tile = Map::TILE_SIZE / 2;
    const int tenth_tile = Map::TILE_SIZE / 10;
    const int half_window_height = Game::WINDOW_HEIGHT / 2;

    const SDL_Rect rectangle(
            Game::WINDOW_HEIGHT / tenth_tile / 2,
            Game::WINDOW_HEIGHT - double_tile,
            half_window_height,
            double_tile - half_tile
    );

    GraphicsEngine::getInstance().addGraphic<TextBox>(
            rectangle,
            rectangle.h / (tenth_tile * 3),
            rectangle.x + tenth_tile,
            rectangle.y + tenth_tile
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
            rectangle.h / (tenth_tile * 3),
            2,
            2,
            Game::WINDOW_WIDTH / 4 - half_tile,
            half_tile,
            border_size
    );

    GraphicsEngine::getInstance().getGraphic<Panel>().add<0, 0>(
            Constants::Color::RED,
            "Fight",
            [this] -> void {
                this->states.push(BattlePhase::BattleState::FIGHT);
                this->initFight();
            }
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
                // TODO not is only here for testing purposes
                if (not this->opponent->isTrainer()) {
                    GraphicsEngine::getInstance().getGraphic<TextBox>().push("You can't run away from a trainer battle!");
                }
                else {
                    const int opponent_speed = static_cast<int>((*this->opponent)[0].getBaseStat(Pokemon::Stat::SPEED) / 4) % 256;
                    const int odds = static_cast<int>((Player::getPlayer()[0].getBaseStat(Pokemon::Stat::SPEED) * 32) / opponent_speed) + 30;

                    if (opponent_speed == 0 or odds > 255 or generateInteger(0, 255) < odds) {
                        GraphicsEngine::getInstance().getGraphic<TextBox>().push("Got away safely!");
                        this->states.push(BattlePhase::BattleState::T_OUT);
                    }
                    else {
                        GraphicsEngine::getInstance().getGraphic<TextBox>().push("Couldn't get away");
                    }
                }
            }
    );
}

void BattlePhase::initFight() {
    GraphicsEngine::getInstance().getGraphic<TextBox>().pop();
    GraphicsEngine::getInstance().getGraphic<TextBox>().push("Select a move");

    GraphicsEngine::getInstance().removeGraphic<Panel>();

    const int double_tile = Map::TILE_SIZE * 2;
    const int half_tile = Map::TILE_SIZE / 2;
    const int tenth_tile = Map::TILE_SIZE / 10;
    const int half_window_height = Game::WINDOW_HEIGHT / 2;

    const SDL_Rect rectangle(
            Game::WINDOW_HEIGHT / tenth_tile / 2,
            Game::WINDOW_HEIGHT - double_tile,
            half_window_height,
            double_tile - half_tile
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
            rectangle.h / (tenth_tile * 3),
            2,
            2,
            Game::WINDOW_WIDTH / 4 - half_tile,
            half_tile,
            border_size
    );

    // default assignment for if the player skips
    this->playerMove = Player::getPlayer()[0].numMoves();

    if (Player::getPlayer()[0].numMoves() > 0) {
        GraphicsEngine::getInstance().getGraphic<Panel>().add<0, 0>(
                typeToColor(Player::getPlayer()[0][0].getType()),
                Player::getPlayer()[0][0].getName(),
                [this] -> void {
                    this->playerMove = 0;
                    this->handleTurn();
                }
        );

        if (Player::getPlayer()[0].numMoves() > 1) {
            GraphicsEngine::getInstance().getGraphic<Panel>().add<0, 1>(
                    typeToColor(Player::getPlayer()[0][1].getType()),
                    Player::getPlayer()[0][1].getName(),
                    [this] -> void {
                        this->playerMove = 1;
                        this->handleTurn();
                    }
            );

            if (Player::getPlayer()[0].numMoves() > 2) {
                GraphicsEngine::getInstance().getGraphic<Panel>().add<1, 0>(
                        typeToColor(Player::getPlayer()[0][2].getType()),
                        Player::getPlayer()[0][2].getName(),
                        [this] -> void {
                            this->playerMove = 2;
                            this->handleTurn();
                        }
                );

                if (Player::getPlayer()[0].numMoves() > 3) {
                    GraphicsEngine::getInstance().getGraphic<Panel>().add<1, 1>(
                            typeToColor(Player::getPlayer()[0][3].getType()),
                            Player::getPlayer()[0][3].getName(),
                            [this] -> void {
                                this->playerMove = 3;
                                this->handleTurn();
                            }
                    );
                }
            }
        }
    }
}

std::string statusMessage(const Pokemon &pokemon) {
    switch (pokemon.getStatus()) {
        case StatusCondition::BURN:
            return pokemon.getName() + " took " +
                         std::to_string(static_cast<int>(std::round(pokemon.getMaxHp() * 0.0625))) +
                         " damage from it's burn!";

        case StatusCondition::PARALYSIS:
            return pokemon.getName() + " is paralyzed! It can't move!";

        case StatusCondition::FREEZE:
            return pokemon.getName() + " is frozen solid!";

        case StatusCondition::POISON:
            return pokemon.getName() + " took " +
                         std::to_string(static_cast<int>(std::round(pokemon.getMaxHp() * 0.0625))) +
                         " damage from it's poisoning!";

        case StatusCondition::SLEEP:
            return pokemon.getName() + " is fast asleep!";

        default:
            throw std::runtime_error("Unexpected error: function inflictedMessage");
    }
}

void BattlePhase::engage(Trainer *attacker, Trainer *defender, int move, bool *skip) {
    (*attacker)[0][move].action((*attacker)[0], (*defender)[0], *skip);

    auto queue = (*attacker)[0][move].actionMessage((*attacker)[0], (*defender)[0], *skip);
    while (not queue.empty()) {
        GraphicsEngine::getInstance().getGraphic<TextBox>().push(queue.front());
        queue.pop();
    }

    if ((*defender)[0].isFainted()) {
        defender->incFaintCount();

        GraphicsEngine::getInstance().getGraphic<TextBox>().push((*defender)[0].getName() + " fained!");
        if (not defender->canFight()) {
            for (int i = 0; i < Player::getPlayer().partySize(); ++i) {
                Player::getPlayer()[i].initStatMods();
            }
            GraphicsEngine::getInstance().getGraphic<TextBox>().push(attacker->winMessage());
            this->states.push(BattlePhase::BattleState::T_OUT);
        }
        else {
            // TODO implement switchOut for trainer and player inside the classes
        }
    }
}

void BattlePhase::preStatus(bool isPlayerFaster) {
    bool (*hasStatusCondition)(const StatusCondition) = [](const StatusCondition status) -> bool {
        return status == StatusCondition::PARALYSIS ? binomial(25.0) : status == StatusCondition::FREEZE or status == StatusCondition::SLEEP;
    };

    Trainer *first = isPlayerFaster ? &Player::getPlayer() : this->opponent;
    Trainer *second = isPlayerFaster ? this->opponent : &Player::getPlayer();
    bool *toSkip = isPlayerFaster ? &this->skipOpponent : &this->skipPlayer;

    const auto action = [this, &isPlayerFaster, &toSkip, &hasStatusCondition](Trainer *attacker, Trainer *defender) -> void {
        const int move = isPlayerFaster ? this->playerMove : this->opponentMove;
        if (move < (*attacker)[0].numMoves()) {
            if (not hasStatusCondition((*attacker)[0].getStatus())) {
                this->engage(attacker, defender, move, toSkip);
            }
            else {
                GraphicsEngine::getInstance().getGraphic<TextBox>().push(statusMessage((*attacker)[0]));
            }
        }
    };

    action(first, second);
    if (not *toSkip and this->states.top() != BattlePhase::BattleState::T_OUT) {
        action(second, first);
    }
    *toSkip = false;
}

void BattlePhase::postStatus(bool isPlayerFaster) {
    if (this->states.top() == BattlePhase::BattleState::T_OUT) {
        return;
    }

    bool (*hasStatusCondition)(StatusCondition) = [](StatusCondition status) -> bool {
        return status == StatusCondition::BURN or status == StatusCondition::POISON;
    };

    auto postStatus = [this](Trainer *trainer) -> void {
        (*trainer)[0].takeDamage(static_cast<int>(std::round((*trainer)[0].getMaxHp() * 0.0625)));
        GraphicsEngine::getInstance().getGraphic<TextBox>().push(statusMessage((*trainer)[0]));

        if ((*trainer)[0].isFainted()) {
            trainer->incFaintCount();
            GraphicsEngine::getInstance().getGraphic<TextBox>().push((*trainer)[0].getName() + " fainted!");

            if (not trainer->canFight()) {
                for (int i = 0; i < Player::getPlayer().partySize(); ++i) {
                    Player::getPlayer()[i].initStatMods();
                }
                GraphicsEngine::getInstance().getGraphic<TextBox>().push(trainer->winMessage());
                this->states.push(BattlePhase::BattleState::T_OUT);
            }
            else {
                // TODO implement switchOut for trainer and player inside the classes
            }
        }
    };

    Trainer *first = isPlayerFaster ? &Player::getPlayer() : this->opponent;
    Trainer *second = isPlayerFaster ? this->opponent : &Player::getPlayer();

    if (hasStatusCondition((*first)[0].getStatus())) {
        postStatus(first);
    }
    if (hasStatusCondition((*second)[0].getStatus())) {
        postStatus(second);
    }
}

void BattlePhase::handleTurn() {
    // re-selects opponent move if it's out of PP
    this->opponentMove = generateInteger(0, (*this->opponent)[0].numMoves() - 1);
    while (not(*this->opponent)[0][this->opponentMove]) {
        opponentMove = generateInteger(0, (*this->opponent)[0].numMoves() - 1);
    }

    // if the player is faster than the opponent or,
    // assuming the opponent isn't using a priority move,
    // the player is using a priority move...
    if (Player::getPlayer()[0].isFasterThan((*this->opponent)[0]) or Player::getPlayer()[0][this->playerMove].isPriority() and not (*this->opponent)[0][this->opponentMove].isPriority()) {
        this->preStatus(true);
        this->postStatus(true);
    }
        // if the opponent is faster than the player or,
        // assuming the player isn't using a priority move,
        // the opponent is using a priority move...
    else if ((*this->opponent)[0].isFasterThan(Player::getPlayer()[0]) or (*this->opponent)[0][this->opponentMove].isPriority() and not Player::getPlayer()[0][this->playerMove].isPriority()) {
        this->preStatus(false);
        this->postStatus(false);
    }
        // if trainer and opponent rival in speed or both or neither are using a priority move, choose randomly
    else {
        const bool player_first = binomial();
        this->preStatus(player_first);
        this->postStatus(player_first);
    }

    ++this->turn;

    // reset flags
    // TODO account for self skipping moves such as Solar Beam
    this->skipPlayer = false;
    this->skipOpponent = false;

    // FIXME this is assuming that there are only 2 states pushed at this point; this could break
    this->states.pop();
}

void BattlePhase::updateTOut() {
    static int counter = 0;

    if (not GraphicsEngine::getInstance().getGraphic<TextBox>().isPrinting()) {
        ++counter;
        if (counter == 100) {
            this->isRunning = false;
            this->opponent->clearParty();

            Player::getPlayer().setState(Entity::State::IDLE);
            GraphicsEngine::getInstance().clear();

            if (Mix_FadeOutMusic(2000) == 0) {
                std::clog << "Error fading out \"" << State::getInstance<Overworld>().getCurrentMap()->getMusic()
                          << "\": " << SDL_GetError() << '\n';
                SDL_ClearError();
                Game::getInstance().terminate();
                return;
            }

            Mix_HookMusicFinished([] -> void {
                Mixer::getInstance().playMusic(State::getInstance<Overworld>().getCurrentMap()->getMusic());
            });

            counter = 0;
        }
    }
}

void BattlePhase::init(Trainer *trainer) {
    this->opponent = trainer;
    this->INIT_FUNCTIONS[static_cast<std::size_t>(BattlePhase::BattleState::MAIN)]();
}

void BattlePhase::update() {
    if (not this->isRunning) {
        this->opponent = nullptr;
        this->turn = 0;

        this->skipPlayer = false;
        this->skipOpponent = false;

        Game::getInstance().setState(State::Id::OVERWORLD);
        while (not this->states.empty()) {
            this->states.pop();
        }
        return;
    }

    GraphicsEngine::getInstance().update();

    if (KeyManager::getInstance().getKey(SDL_Scancode::SDL_SCANCODE_BACKSPACE) and this->states.size() != 1) {
        this->states.pop();
        if (this->INIT_FUNCTIONS.at(static_cast<std::size_t>(this->states.top())) != nullptr) {
            this->INIT_FUNCTIONS.at(static_cast<std::size_t>(this->states.top()))();
        }
    }

    if (this->UPDATE_FUNCTIONS.at(static_cast<std::size_t>(this->states.top())) != nullptr) {
        this->UPDATE_FUNCTIONS.at(static_cast<std::size_t>(this->states.top()))();
    }
}

void BattlePhase::render() {
    GraphicsEngine::getInstance().render();
    Game::getInstance().setRenderColor(Constants::Color::WHITE);
}
