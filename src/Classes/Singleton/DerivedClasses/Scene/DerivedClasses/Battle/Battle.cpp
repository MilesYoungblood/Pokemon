//
// Created by Miles on 1/28/2024.
//

#include "../../../Game/Game.h"
#include "../../../GraphicsEngine/GraphicsEngine.h"
#include "../../../Mixer/Mixer.h"
#include "../../../KeyManager/KeyManager.h"
#include "Battle.h"

namespace {
    std::condition_variable cv;
    std::mutex mutex;
}

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

void delay() {
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    GraphicsEngine::getInstance().getGraphic<TextBox>().pop();
}

void Battle::initMain() {
    KeyManager::getInstance().lock(SDL_Scancode::SDL_SCANCODE_RETURN);

    GraphicsEngine::getInstance().getGraphic<TextBox>().pop();
    GraphicsEngine::getInstance().getGraphic<TextBox>().push(
            "What will " + Player::getPlayer()[0].getName() + " do?",
            [] -> void {
                std::scoped_lock<std::mutex> scopedLock(mutex);
                // unlocking the WASD keys is necessary in case the player was skipped
                KeyManager::getInstance().unlock(SDL_Scancode::SDL_SCANCODE_W);
                KeyManager::getInstance().unlock(SDL_Scancode::SDL_SCANCODE_A);
                KeyManager::getInstance().unlock(SDL_Scancode::SDL_SCANCODE_S);
                KeyManager::getInstance().unlock(SDL_Scancode::SDL_SCANCODE_D);

                KeyManager::getInstance().unlock(SDL_Scancode::SDL_SCANCODE_RETURN);
                cv.notify_one();
            }
    );

    std::thread thread([this] -> void {
        std::unique_lock<std::mutex> uniqueLock(mutex);
        cv.wait(uniqueLock);

        GraphicsEngine::getInstance().getGraphic<Panel>().clear();

        GraphicsEngine::getInstance().getGraphic<Panel>().add(
                Constants::Color::RED,
                "Fight",
                [this] -> void {
                    Mixer::getInstance().playSound("select");
                    this->changeState(Battle::State::SELECT_MOVE, false);
                }
        );
        GraphicsEngine::getInstance().getGraphic<Panel>().add(
                Constants::Color::YELLOW,
                "Bag",
                [] -> void {
                    Mixer::getInstance().playSound("select");
                }
        );
        GraphicsEngine::getInstance().getGraphic<Panel>().add(
                Constants::Color::GREEN,
                "Pokemon",
                [this] -> void {
                    Mixer::getInstance().playSound("select");
                    this->changeState(Battle::State::SELECT_POKEMON, false);
                }
        );
        GraphicsEngine::getInstance().getGraphic<Panel>().add(
                Constants::Color::BLUE,
                "Run",
                [this] -> void {
                    Mixer::getInstance().playSound("select");
                    this->handleRun();
                }
        );
    });
    thread.detach();
}

void Battle::initFight() {
    GraphicsEngine::getInstance().getGraphic<TextBox>().pop();

    KeyManager::getInstance().lock(SDL_Scancode::SDL_SCANCODE_RETURN);
    GraphicsEngine::getInstance().getGraphic<TextBox>().push(
            "Select a move",
            [] -> void { KeyManager::getInstance().unlock(SDL_Scancode::SDL_SCANCODE_RETURN); }
    );

    GraphicsEngine::getInstance().getGraphic<Panel>().clear();

    // default assignment for if the player skips
    this->playerMove = Player::getPlayer()[0].numMoves();

    for (int i = 0; i < Player::getPlayer()[0].numMoves(); ++i) {
        GraphicsEngine::getInstance().getGraphic<Panel>().add(
                typeToColor(Player::getPlayer()[0][i].getType()),
                Player::getPlayer()[0][i].getName(),
                [this, i] -> void {
                    Mixer::getInstance().playSound("select");
                    this->handleTurn(i);
                    this->changeState(Battle::State::ENGAGE, true);
                }
        );
    }
}

void Battle::initPokemon() {
    GraphicsEngine::getInstance().getGraphic<Panel>().clear();

    GraphicsEngine::getInstance().getGraphic<TextBox>().pop();

    KeyManager::getInstance().lock(SDL_Scancode::SDL_SCANCODE_RETURN);
    GraphicsEngine::getInstance().getGraphic<TextBox>().push(
            "Select a Pokemon",
            [] -> void { KeyManager::getInstance().unlock(SDL_Scancode::SDL_SCANCODE_RETURN); }
    );

    std::vector<std::pair<std::string, std::function<void()>>> pairs;

    pairs.emplace_back(Player::getPlayer()[0].getName(), [this] -> void {
            KeyManager::getInstance().lock(SDL_Scancode::SDL_SCANCODE_RETURN);

            GraphicsEngine::getInstance().removeGraphic<SelectionBox>();

            GraphicsEngine::getInstance().getGraphic<TextBox>().pop();
            GraphicsEngine::getInstance().getGraphic<TextBox>().push(
                    Player::getPlayer()[0].getName() + " is already in battle!",
                    [this] -> void {
                        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                        this->initMain();
                    }
            );
    });
    for (int i = 1; i < Player::getPlayer().partySize(); ++i) {
        pairs.emplace_back(Player::getPlayer()[i].getName(), [this, i] -> void {
            Player::getPlayer().swapPokemon(0, i);
            GraphicsEngine::getInstance().getGraphic<TextBox>().pop();
            GraphicsEngine::getInstance().getGraphic<TextBox>().push(
                    "You swapped out " + Player::getPlayer()[i].getName() + " for " + Player::getPlayer()[0].getName() + '!',
                    [this] -> void {
                        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                        this->handleTurn(Player::getPlayer()[0].numMoves());
                        this->changeState(Battle::State::ENGAGE, true);
                    }
            );
        });
    }

    GraphicsEngine::getInstance().addGraphic<SelectionBox>(
            SDL_Rect(50, 50, 250, 300),
            5,
            pairs
    );
}

void Battle::initEngage() {
    // pops the message that does not belong
    GraphicsEngine::getInstance().getGraphic<TextBox>().pop();
    GraphicsEngine::getInstance().getGraphic<Panel>().clear();

    KeyManager::getInstance().lock(SDL_Scancode::SDL_SCANCODE_RETURN);
    KeyManager::getInstance().lock(SDL_Scancode::SDL_SCANCODE_BACKSPACE);
}

std::string statusMessage(const Pokemon &pokemon) {
    auto damageMessage = [&pokemon](const char *status) -> std::string {
        return pokemon.getName() + " took " + std::to_string(static_cast<int>(std::round(pokemon.getMaxHp() * 0.0625))) + " damage from it's " + status + '!';
    };

    switch (pokemon.getStatus()) {
        case StatusCondition::BURN:
            return damageMessage("burn");

        case StatusCondition::PARALYSIS:
            return pokemon.getName() + " is paralyzed! It can't move!";

        case StatusCondition::FREEZE:
            return pokemon.getName() + " is frozen solid!";

        case StatusCondition::POISON:
            return damageMessage("poisoning");

        case StatusCondition::SLEEP:
            return pokemon.getName() + " is fast asleep!";

        default:
            throw std::runtime_error("Unexpected error: function statusMessage");
    }
}

void Battle::engage(Trainer *attacker, Trainer *defender, int move, bool *skip) {
    (*attacker)[0][move].action((*attacker)[0], (*defender)[0], *skip);

    std::vector<std::pair<std::string, std::function<void()>>> pairs;
    for (const auto &message : (*attacker)[0][move].actionMessage((*attacker)[0], (*defender)[0], *skip)) {
        pairs.emplace_back(message, delay);
    }
    GraphicsEngine::getInstance().getGraphic<TextBox>().push(pairs);

    if ((*defender)[0].isFainted()) {
        *skip = true;
        GraphicsEngine::getInstance().getGraphic<TextBox>().push(
                (*defender)[0].getName() + " fained!",
                [this, attacker, defender] -> void {
                    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                    defender->handleFaint();
                    if (not defender->canFight()) {
                        for (auto &pokemon : Player::getPlayer()) {
                            pokemon.initStatMods();
                        }

                        std::vector<std::pair<std::string, std::function<void()>>> pairs;
                        {
                            std::vector<std::string> message = attacker->winMessage();

                            pairs.emplace_back(message[0], delay);
                            pairs.emplace_back(message[1],[this] -> void {
                                    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
                                    this->isRunning = false;
                            });
                        }

                        GraphicsEngine::getInstance().getGraphic<TextBox>().pop();
                        GraphicsEngine::getInstance().getGraphic<TextBox>().push(pairs);
                    }
                    else {
                        // TODO implement switchOut for trainer and player inside the classes
                    }
                }
        );
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
                GraphicsEngine::getInstance().getGraphic<TextBox>().push(statusMessage((*attacker)[0]), delay);
            }
        }
    };

    Trainer *first = isPlayerFaster ? &Player::getPlayer() : this->opponent;
    Trainer *second = isPlayerFaster ? this->opponent : &Player::getPlayer();

    const int first_move = isPlayerFaster ? this->playerMove : this->opponentMove;
    const int second_move = isPlayerFaster ? this->opponentMove : this->playerMove;

    action(first, second, first_move);
    if (not *toSkip and second->canFight()) {
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

    auto postStatus = [this](Trainer *observer, Trainer *receiver, ResourceBar *resourceBar) -> void {
        int damage = static_cast<int>((*receiver)[0].getMaxHp() * 0.0625);
        (*receiver)[0].takeDamage(damage);
        GraphicsEngine::getInstance().getGraphic<TextBox>().push(
                statusMessage((*receiver)[0]),
                [resourceBar, damage] -> void {
                    if (resourceBar != nullptr) {
                        resourceBar->lower(damage);
                    }
                }
        );

        if ((*receiver)[0].isFainted()) {
            GraphicsEngine::getInstance().getGraphic<TextBox>().push((*receiver)[0].getName() + " fainted!");
            receiver->handleFaint();

            if (not receiver->canFight()) {
                for (auto &pokemon : Player::getPlayer()) {
                    pokemon.initStatMods();
                }

                std::vector<std::pair<std::string, std::function<void()>>> pairs;
                {
                    std::vector<std::string> message = observer->winMessage();

                    pairs.emplace_back(message[0], delay);
                    pairs.emplace_back(message[1], [this] -> void {
                        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
                        this->isRunning = false;
                    });
                }

                GraphicsEngine::getInstance().getGraphic<TextBox>().push(pairs);
            }
            else {
                // TODO implement switchOut for receiver and player inside the classes
            }
        }
    };

    Trainer *first = isPlayerFaster ? &Player::getPlayer() : this->opponent;
    Trainer *second = isPlayerFaster ? this->opponent : &Player::getPlayer();

    ResourceBar *firstBar = isPlayerFaster ? this->playerBar : this->opponentBar;
    ResourceBar *secondBar = isPlayerFaster ? this->opponentBar : this->playerBar;

    if (hasStatusCondition((*first)[0].getStatus())) {
        postStatus(second, first, firstBar);
    }
    if (hasStatusCondition((*second)[0].getStatus())) {
        postStatus(first, second, secondBar);
    }
}

void Battle::handleTurn(int move) {
    this->playerMove = move;
    this->opponentMove = (*this->opponent)[0].numMoves();

    if ((*this->opponent)[0].canAttack()) {
        while (true) {
            this->opponentMove = generateInteger(0, (*this->opponent)[0].numMoves() - 1);
            if ((*this->opponent)[0][this->opponentMove].canUse()) {
                break;
            }
        }
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
    if (GraphicsEngine::getInstance().getGraphic<TextBox>().empty()) {
        this->changeState(Battle::State::MAIN, true);
        KeyManager::getInstance().unlock(SDL_Scancode::SDL_SCANCODE_RETURN);
        KeyManager::getInstance().unlock(SDL_Scancode::SDL_SCANCODE_BACKSPACE);
    }
}

void Battle::handleRun() {
    GraphicsEngine::getInstance().getGraphic<TextBox>().pop();
    GraphicsEngine::getInstance().getGraphic<Panel>().clear();

    KeyManager::getInstance().lock(SDL_Scancode::SDL_SCANCODE_W);
    KeyManager::getInstance().lock(SDL_Scancode::SDL_SCANCODE_A);
    KeyManager::getInstance().lock(SDL_Scancode::SDL_SCANCODE_S);
    KeyManager::getInstance().lock(SDL_Scancode::SDL_SCANCODE_D);

    if (this->opponent->isTrainer()) {
        KeyManager::getInstance().lock(SDL_Scancode::SDL_SCANCODE_RETURN);
        GraphicsEngine::getInstance().getGraphic<TextBox>().push(
                "You can't run away from a trainer battle!",
                [this] -> void {
                    delay();
                    this->initMain();
                }
        );
    }
    else {
        const int opponent_speed = static_cast<int>((*this->opponent)[0].getBaseStat(Pokemon::Stat::SPEED) / 4) % 256;
        const int odds = static_cast<int>((Player::getPlayer()[0].getBaseStat(Pokemon::Stat::SPEED) * 32) / opponent_speed) + 30;

        if (opponent_speed == 0 or odds > 255 or generateInteger(0, 255) < odds) {
            GraphicsEngine::getInstance().getGraphic<TextBox>().push(
                    "Got away safely!",
                    [this] -> void {
                        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
                        this->terminate();
                    }
            );
        }
        else {
            GraphicsEngine::getInstance().getGraphic<TextBox>().push(
                    "Couldn't get away",
                    [this] -> void {
                            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                            this->handleTurn(Player::getPlayer()[0].numMoves());
                            this->changeState(Battle::State::ENGAGE, true);
                    }
            );
        }
    }
}

void Battle::terminate() {
    this->opponent = nullptr;
    this->turn = 0;

    this->skipPlayer = false;
    this->skipOpponent = false;

    this->renderPlayer = false;
    this->renderOpponent = false;

    Game::getInstance().changeScene(Scene::Id::OVERWORLD);
    while (not this->states.empty()) {
        this->states.pop();
    }

    auto cleanMap = [](std::unordered_map<std::string, SDL_Texture *> &map) -> void{
        for (auto &texture : map) {
            if (texture.second != nullptr) {
                SDL_DestroyTexture(texture.second);
                if (strlen(SDL_GetError()) > 0){
                    std::clog << "Unable to destroy pokemon battle-sprite \"" << texture.first << ": " << SDL_GetError() << '\n';
                    SDL_ClearError();
                }
            }
        }
        map.clear();
    };

    cleanMap(this->playerSprites);
    cleanMap(this->opponentSprites);

    KeyManager::getInstance().unlock(SDL_Scancode::SDL_SCANCODE_W);
    KeyManager::getInstance().unlock(SDL_Scancode::SDL_SCANCODE_A);
    KeyManager::getInstance().unlock(SDL_Scancode::SDL_SCANCODE_S);
    KeyManager::getInstance().unlock(SDL_Scancode::SDL_SCANCODE_D);

    KeyManager::getInstance().unlock(SDL_Scancode::SDL_SCANCODE_RETURN);

    Player::getPlayer().setState(Character::State::IDLE);
    GraphicsEngine::getInstance().clear();

    if (Mix_FadeOutMusic(2000) == 0) {
        std::clog << "Error fading out \"" << Scene::getInstance<Overworld>().getCurrentMap().getMusic()
                  << "\": " << SDL_GetError() << '\n';
        SDL_ClearError();
        Game::getInstance().terminate();
        return;
    }

    Mix_HookMusicFinished([] -> void {
        Mixer::getInstance().playMusic(Scene::getInstance<Overworld>().getCurrentMap().getMusic());
    });

    this->isRunning = true;
}

void Battle::changeState(Battle::State state, bool clear) {
    if (clear) {
        while (not this->states.empty()) {
            this->states.pop();
        }
    }
    this->states.push(state);
    if (this->INIT_FUNCTIONS.at(static_cast<std::size_t>(this->states.top())) != nullptr) {
        this->INIT_FUNCTIONS.at(static_cast<std::size_t>(this->states.top()))();
    }
}

void Battle::init(Trainer *trainer) {
    this->opponent = trainer;
    this->states.push(Battle::State::MAIN);

    auto loadMap = [](std::unordered_map<std::string, SDL_Texture *> &map, const Trainer &trainer, bool front) -> bool {
        for (const auto &pokemon : trainer) {
            const char *side = front ? "Front" : "Back";
            map[pokemon.getName()] = TextureManager::getInstance().loadTexture("sprites/Pokemon/" + pokemon.getName() + '/' + pokemon.getName() + side + ".png");
            if (map[pokemon.getName()] == nullptr) {
                std::clog << "Unable to load pokemon battle-sprite \"" << pokemon.getName() << front << ".png\"\n";
                Game::getInstance().terminate();
                return false;
            }
        }
        return true;
    };
    if (not loadMap(this->playerSprites, Player::getPlayer(), false)) {
        return;
    }
    if (not loadMap(this->opponentSprites, *this->opponent, true)) {
        return;
    }

    GraphicsEngine::getInstance().addGraphic<ResourceBar>(
            SDL_Rect(Game::WINDOW_WIDTH - 250, Map::TILE_SIZE * 4, 200, 10),
            Constants::Color::GREEN,
            5,
            100
    );
    this->playerBar = &GraphicsEngine::getInstance().getGraphic<ResourceBar>();

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

    GraphicsEngine::getInstance().addGraphic<TextBox>(
            RECTANGLE,
            RECTANGLE.h / (TENTH_TILE * 3),
            RECTANGLE.x + TENTH_TILE,
            RECTANGLE.y + TENTH_TILE
    );
    GraphicsEngine::getInstance().getGraphic<TextBox>().push(
            "You were challenged by " + this->opponent->getId() + ' ' + this->opponent->getName() + '!',
            delay
    );
    GraphicsEngine::getInstance().getGraphic<TextBox>().push(
            this->opponent->getId() + ' ' + this->opponent->getName() + " sent out " + (*this->opponent)[0].getName() + '!',
            [this] -> void {
                delay();
                this->renderOpponent = true;
            }
    );
    GraphicsEngine::getInstance().getGraphic<TextBox>().push(
            "Go " + Player::getPlayer()[0].getName() + '!',
            [this] -> void {
                delay();
                this->renderPlayer = true;
            }
    );

    this->initMain();
}

void Battle::update() {
    if (not this->isRunning) {
        this->terminate();
        return;
    }
    GraphicsEngine::getInstance().update();

    if (KeyManager::getInstance().getKey(SDL_Scancode::SDL_SCANCODE_BACKSPACE) and this->states.size() > 1) {
        this->states.pop();
        if (this->INIT_FUNCTIONS.at(static_cast<std::size_t>(this->states.top())) != nullptr) {
            this->INIT_FUNCTIONS.at(static_cast<std::size_t>(this->states.top()))();
        }

        if (GraphicsEngine::getInstance().hasAny<SelectionBox>()) {
            GraphicsEngine::getInstance().removeGraphic<SelectionBox>();
        }
    }

    if (this->UPDATE_FUNCTIONS.at(static_cast<std::size_t>(this->states.top())) != nullptr) {
        this->UPDATE_FUNCTIONS.at(static_cast<std::size_t>(this->states.top()))();
    }
}

void Battle::render() {
    // FIXME works but not correctly implemented
    if (this->renderPlayer and Player::getPlayer().canFight()) {
        TextureManager::getInstance().draw(
                this->playerSprites.at(Player::getPlayer()[0].getName()),
                SDL_Rect(
                        HALF_TILE,
                        Game::WINDOW_HEIGHT - Map::TILE_SIZE * 5 - HALF_TILE,
                        Map::TILE_SIZE * 4,
                        Map::TILE_SIZE * 4
                )
        );
    }
    // FIXME works but not correctly implemented
    if (this->renderOpponent and this->opponent->canFight()) {
        TextureManager::getInstance().draw(
                this->opponentSprites.at((*this->opponent)[0].getName()),
                SDL_Rect(
                        Game::WINDOW_WIDTH - Map::TILE_SIZE * 4 + HALF_TILE,
                        0,
                        Map::TILE_SIZE * 3 - HALF_TILE,
                        Map::TILE_SIZE * 3 - HALF_TILE
                )
        );
    }
    GraphicsEngine::getInstance().render();
    Game::getInstance().setRenderColor(Constants::Color::WHITE);
}