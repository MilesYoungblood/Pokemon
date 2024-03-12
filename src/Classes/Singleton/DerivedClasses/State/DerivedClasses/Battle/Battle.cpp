//
// Created by Miles on 1/28/2024.
//

#include "../../../Game/Game.h"
#include "../../../GraphicsEngine/GraphicsEngine.h"
#include "../../../Mixer/Mixer.h"
#include "../../../KeyManager/KeyManager.h"
#include "Battle.h"

const int DOUBLE_TILE = Map::TILE_SIZE * 2;
const int HALF_TILE = Map::TILE_SIZE / 2;
const int TENTH_TILE = Map::TILE_SIZE / 10;
const int HALF_WINDOW_HEIGHT = Game::WINDOW_HEIGHT / 2;

const SDL_Rect RECTANGLE(
        Game::WINDOW_HEIGHT / TENTH_TILE / 2,
        Game::WINDOW_HEIGHT - DOUBLE_TILE,
        HALF_WINDOW_HEIGHT,
        DOUBLE_TILE - HALF_TILE
);

const int BORDER_SIZE = (Game::WINDOW_WIDTH / 2 - (DOUBLE_TILE - HALF_TILE)) / (TENTH_TILE * 3) / 5;

void Battle::initMain() {
    GraphicsEngine::getInstance().clear();

    GraphicsEngine::getInstance().addGraphic<TextBox>(
            RECTANGLE,
            RECTANGLE.h / (TENTH_TILE * 3),
            RECTANGLE.x + TENTH_TILE,
            RECTANGLE.y + TENTH_TILE
    );
    KeyManager::getInstance().lockKey(SDL_Scancode::SDL_SCANCODE_RETURN);
    GraphicsEngine::getInstance().getGraphic<TextBox>().push(
            "What will " + Player::getPlayer()[0].getName() + " do?",
            [] -> void { KeyManager::getInstance().unlockKey(SDL_Scancode::SDL_SCANCODE_RETURN); }
    );

    GraphicsEngine::getInstance().addGraphic<ResourceBar>(
            SDL_Rect(Game::WINDOW_WIDTH - 250, Map::TILE_SIZE * 4, 200, 10),
            Constants::Color::GREEN,
            5,
            100
    );

    GraphicsEngine::getInstance().addGraphic<Panel>(
            SDL_Rect(
                    Game::WINDOW_WIDTH - (HALF_WINDOW_HEIGHT + Game::WINDOW_HEIGHT / 10) - HALF_TILE,
                    Game::WINDOW_HEIGHT - DOUBLE_TILE,
                    HALF_WINDOW_HEIGHT + Game::WINDOW_HEIGHT / 10,
                    DOUBLE_TILE - HALF_TILE
            ),
            Constants::Color::GRAY,
            RECTANGLE.h / (TENTH_TILE * 3),
            2,
            2,
            Game::WINDOW_WIDTH / 4 - HALF_TILE,
            HALF_TILE,
            BORDER_SIZE
    );

    GraphicsEngine::getInstance().getGraphic<Panel>().add(
            Constants::Color::RED,
            "Fight",
            [this] -> void {
                this->states.push_front(Battle::BattleState::SELECT_MOVE);
                this->initFight();
            }
    );
    GraphicsEngine::getInstance().getGraphic<Panel>().add(
            Constants::Color::YELLOW,
            "Bag",
            nullptr
    );
    GraphicsEngine::getInstance().getGraphic<Panel>().add(
            Constants::Color::GREEN,
            "Pokemon",
            nullptr
    );
    GraphicsEngine::getInstance().getGraphic<Panel>().add(
            Constants::Color::BLUE,
            "Run",
            [this] -> void {
                this->handleRun();
            }
    );
}

void Battle::initFight() {
    GraphicsEngine::getInstance().getGraphic<TextBox>().pop();

    KeyManager::getInstance().lockKey(SDL_Scancode::SDL_SCANCODE_RETURN);
    GraphicsEngine::getInstance().getGraphic<TextBox>().push(
            "Select a move",
            [] -> void { KeyManager::getInstance().unlockKey(SDL_Scancode::SDL_SCANCODE_RETURN); }
    );

    GraphicsEngine::getInstance().getGraphic<Panel>().clear();

    // default assignment for if the player skips
    this->playerMove = Player::getPlayer()[0].numMoves();

    for (int i = 0; i < Player::getPlayer()[0].numMoves(); ++i) {
        GraphicsEngine::getInstance().getGraphic<Panel>().add(
                typeToColor(Player::getPlayer()[0][0].getType()),
                Player::getPlayer()[0][0].getName(),
                [this, &i] -> void {
                    GraphicsEngine::getInstance().getGraphic<TextBox>().pop();
                    this->playerMove = i;
                    this->handleTurn();
                    this->states.clear();
                    this->states.push_front(Battle::BattleState::ENGAGE);
                    Battle::initEngage();
                }
        );
    }
}

void Battle::initEngage() {
    GraphicsEngine::getInstance().getGraphic<Panel>().clear();
    KeyManager::getInstance().lockKey(SDL_Scancode::SDL_SCANCODE_RETURN);
    KeyManager::getInstance().lockKey(SDL_Scancode::SDL_SCANCODE_BACKSPACE);
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

void Battle::engage(Trainer *attacker, Trainer *defender, int move, bool *skip) {
    void (*openReturn)() = [] -> void { KeyManager::getInstance().unlockKey(SDL_Scancode::SDL_SCANCODE_RETURN); };

    (*attacker)[0][move].action((*attacker)[0], (*defender)[0], *skip);

    const std::vector<std::string> messages = (*attacker)[0][move].actionMessage((*attacker)[0], (*defender)[0], *skip);
    GraphicsEngine::getInstance().getGraphic<TextBox>().push(messages,std::vector<std::function<void()>>(messages.size(), openReturn));

    if ((*defender)[0].isFainted()) {
        GraphicsEngine::getInstance().getGraphic<TextBox>().push(
                (*defender)[0].getName() + " fained!",
                openReturn
        );
        defender->handleFaint();

        if (not defender->canFight()) {
            for (auto &pokemon : Player::getPlayer()) {
                pokemon->initStatMods();
            }
            GraphicsEngine::getInstance().getGraphic<TextBox>().push(
                    attacker->winMessage(),
                    std::vector<std::function<void()>>({
                           openReturn,
                           [this, &openReturn] -> void {
                                openReturn();
                                this->states.clear();
                                this->states.push_front(Battle::BattleState::T_OUT);
                           }
                    })
            );
        }
        else {
            // TODO implement switchOut for trainer and player inside the classes
        }
    }
}

void Battle::preStatus(bool isPlayerFaster) {
    bool (*hasStatusCondition)(const StatusCondition) = [](const StatusCondition status) -> bool {
        return status == StatusCondition::PARALYSIS ? binomial(25.0) : status == StatusCondition::FREEZE or status == StatusCondition::SLEEP;
    };

    bool *toSkip = isPlayerFaster ? &this->skipOpponent : &this->skipPlayer;

    const auto action = [this, &toSkip, &hasStatusCondition](Trainer *attacker, Trainer *defender, int move) -> void {
        if (move < (*attacker)[0].numMoves()) {
            if (not hasStatusCondition((*attacker)[0].getStatus())) {
                this->engage(attacker, defender, move, toSkip);
            }
            else {
                GraphicsEngine::getInstance().getGraphic<TextBox>().push(statusMessage((*attacker)[0]));
            }
        }
    };

    Trainer *first = isPlayerFaster ? &Player::getPlayer() : this->opponent;
    Trainer *second = isPlayerFaster ? this->opponent : &Player::getPlayer();

    const int first_move = isPlayerFaster ? this->playerMove : this->opponentMove;
    const int second_move = isPlayerFaster ? this->opponentMove : this->playerMove;

    action(first, second, first_move);
    if (not *toSkip and this->states.front() != Battle::BattleState::T_OUT) {
        action(second, first, second_move);
    }
}

void Battle::postStatus(bool isPlayerFaster) {
    // if one of the trainers here can no longer fight, exit
    if (not Player::getPlayer().canFight() or not this->opponent->canFight()) {
        return;
    }

    bool (*hasStatusCondition)(StatusCondition) = [](StatusCondition status) -> bool {
        return status == StatusCondition::BURN or status == StatusCondition::POISON;
    };

    auto postStatus = [this](Trainer *trainer) -> void {
        (*trainer)[0].takeDamage(static_cast<int>(std::round((*trainer)[0].getMaxHp() * 0.0625)));
        GraphicsEngine::getInstance().getGraphic<TextBox>().push(statusMessage((*trainer)[0]));

        if ((*trainer)[0].isFainted()) {
            GraphicsEngine::getInstance().getGraphic<TextBox>().push((*trainer)[0].getName() + " fainted!");
            trainer->handleFaint();

            if (not trainer->canFight()) {
                for (auto &pokemon : Player::getPlayer()) {
                    pokemon->initStatMods();
                }
                GraphicsEngine::getInstance().getGraphic<TextBox>().push(trainer->winMessage());
                this->states.pop_back();
                this->states.push_front(Battle::BattleState::T_OUT);
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

void Battle::handleTurn() {
    // re-selects opponent move if it's out of PP
    this->opponentMove = generateInteger(0, (*this->opponent)[0].numMoves() - 1);
    while (not(*this->opponent)[0][this->opponentMove]) {
        opponentMove = generateInteger(0, (*this->opponent)[0].numMoves() - 1);
    }

    // if neither the player nor the opponent is attempting to attack
    if (this->playerMove == Player::getPlayer()[0].numMoves() and this->opponentMove == (*this->opponent)[0].numMoves()) {
        std::clog << "Not yet implemented where neither choose to attack\n";
        Game::getInstance().terminate();
    }
    else {
        bool playerFirst = [this] -> bool {
            // if the opponent is not intending to attack, the player will attack first
            if (this->opponentMove == (*this->opponent)[0].numMoves()) {
                return true;
            }
            // if the player is not intending to attack, the opponent will attack first
            if (this->playerMove == Player::getPlayer()[0].numMoves()) {
                return false;
            }

            const bool same_prio = Player::getPlayer()[0][this->playerMove].isPriority() == (*this->opponent)[0][this->opponentMove].isPriority();
            const bool same_speed = Player::getPlayer()[0].rivalsInSpeed((*this->opponent)[0]);

            // if the player and the opponent's moves have matching priority,
            if (same_prio) {
                // if the player and the opponent have matching speeds, decide randomly
                if (same_speed) {
                    return binomial();
                }
                // otherwise, the faster entity goes first
                return Player::getPlayer()[0].isFasterThan((*this->opponent)[0]);
            }
            // if the player and the opponent have matching speeds, decide randomly
            if (same_speed) {
                return binomial();
            }
            // otherwise, if the player either is using a priority move or is faster, then it goes first;
            // and vice versa
            return Player::getPlayer()[0][this->playerMove].isPriority() or Player::getPlayer()[0].isFasterThan((*this->opponent)[0]);
        }();
        this->preStatus(playerFirst);
        this->postStatus(playerFirst);
    }

    ++this->turn;

    // reset flags
    // TODO account for self skipping moves such as Solar Beam
    this->skipPlayer = false;
    this->skipOpponent = false;
}

void Battle::updateEngage() {
    if (KeyManager::getInstance().getKey(SDL_Scancode::SDL_SCANCODE_RETURN)) {
        if (not GraphicsEngine::getInstance().getGraphic<TextBox>().empty()) {
            GraphicsEngine::getInstance().getGraphic<TextBox>().pop();
            KeyManager::getInstance().lockKey(SDL_Scancode::SDL_SCANCODE_RETURN);
        }
        if (GraphicsEngine::getInstance().getGraphic<TextBox>().empty()) {
            this->states.clear();
            this->states.push_front(Battle::BattleState::MAIN);
            this->initMain();

            KeyManager::getInstance().unlockKey(SDL_Scancode::SDL_SCANCODE_BACKSPACE);

            // sets a cool-down period before the Enter key can be registered again;
            // this is needed because the program will register a button as
            // being pressed faster than the user can lift their finger
            std::thread coolDown([] -> void {
                std::this_thread::sleep_for(std::chrono::milliseconds(500));
                KeyManager::getInstance().unlockKey(SDL_Scancode::SDL_SCANCODE_RETURN);
            });
            coolDown.detach();
        }
    }
}

void Battle::handleRun() {
    GraphicsEngine::getInstance().getGraphic<TextBox>().pop();
    // TODO not is only here for testing purposes
    if (not this->opponent->isTrainer()) {
        KeyManager::getInstance().lockKey(SDL_Scancode::SDL_SCANCODE_RETURN);
        GraphicsEngine::getInstance().getGraphic<TextBox>().push(
                "You can't run away from a trainer battle!",
                [this] -> void {
                    [] -> void {
                        SDL_Event event;
                        while (true) {
                            SDL_WaitEvent(&event);
                            if (event.key.keysym.scancode == SDL_Scancode::SDL_SCANCODE_RETURN) {
                                return;
                            }
                        }
                    }();
                    GraphicsEngine::getInstance().getGraphic<TextBox>().pop();
                    KeyManager::getInstance().unlockKey(SDL_Scancode::SDL_SCANCODE_RETURN);
                    this->initMain();
                }
        );
    }
    else {
        const int opponent_speed = static_cast<int>((*this->opponent)[0].getBaseStat(Pokemon::Stat::SPEED) / 4) % 256;
        const int odds = static_cast<int>((Player::getPlayer()[0].getBaseStat(Pokemon::Stat::SPEED) * 32) / opponent_speed) + 30;

        if (opponent_speed == 0 or odds > 255 or generateInteger(0, 255) < odds) {
            GraphicsEngine::getInstance().getGraphic<TextBox>().push("Got away safely!");
            this->states.pop_back();
            this->states.push_front(Battle::BattleState::T_OUT);
        }
        else {
            GraphicsEngine::getInstance().getGraphic<TextBox>().push(
                    "Couldn't get away",
                    [this] -> void {
                            [] -> void {
                                SDL_Event event;
                                while (true) {
                                    SDL_WaitEvent(&event);
                                    if (event.key.keysym.scancode == SDL_Scancode::SDL_SCANCODE_RETURN) {
                                        return;
                                    }
                                }
                            }();
                            this->playerMove = Player::getPlayer()[0].numMoves();
                            this->handleTurn();
                            this->states.clear();
                            this->states.push_front(Battle::BattleState::ENGAGE);
                            Battle::initEngage();
                            KeyManager::getInstance().unlockKey(SDL_Scancode::SDL_SCANCODE_RETURN);
                    }
            );
        }
    }
}

void Battle::updateTOut() {
    static int counter = 0;

    if (not GraphicsEngine::getInstance().getGraphic<TextBox>().isPrinting()) {
        ++counter;
        if (counter == 100) {
            this->isRunning = false;
            this->opponent->clearParty();

            Player::getPlayer().setState(Character::State::IDLE);
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

void Battle::init(Trainer *trainer) {
    this->opponent = trainer;
    this->INIT_FUNCTIONS[static_cast<std::size_t>(Battle::BattleState::MAIN)]();
}

void Battle::update() {
    if (not this->isRunning) {
        this->opponent = nullptr;
        this->turn = 0;

        this->skipPlayer = false;
        this->skipOpponent = false;

        Game::getInstance().setState(State::Id::OVERWORLD);
        this->states.clear();
        return;
    }

    GraphicsEngine::getInstance().update();

    if (KeyManager::getInstance().getKey(SDL_Scancode::SDL_SCANCODE_BACKSPACE) and this->states.size() != 1) {
        this->states.pop_front();
        if (this->INIT_FUNCTIONS.at(static_cast<std::size_t>(this->states.front())) != nullptr) {
            this->INIT_FUNCTIONS.at(static_cast<std::size_t>(this->states.front()))();
        }
    }

    if (this->UPDATE_FUNCTIONS.at(static_cast<std::size_t>(this->states.front())) != nullptr) {
        this->UPDATE_FUNCTIONS.at(static_cast<std::size_t>(this->states.front()))();
    }
}

void Battle::render() {
    GraphicsEngine::getInstance().render();
    Game::getInstance().setRenderColor(Constants::Color::WHITE);
}
