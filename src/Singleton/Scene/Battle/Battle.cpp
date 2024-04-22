//
// Created by Miles on 1/28/2024.
//

#include "../../../../utility/Functions/GeneralFunctions.h"
#include "../../Game/Game.h"
#include "../../GraphicsEngine/GraphicsEngine.h"
#include "../../TextureManager/TextureManager.h"
#include "../../Mixer/Mixer.h"
#include "../../KeyManager/KeyManager.h"
#include "../../Cache/Pokedex/Pokedex.h"
#include "Battle.h"

namespace {
    std::condition_variable cv;
    std::mutex mutex;

    constexpr int DOUBLE_TILE = Map::TILE_SIZE * 2;
    constexpr int HALF_TILE = Map::TILE_SIZE / 2;
    constexpr int TENTH_TILE = Map::TILE_SIZE / 10;
    constexpr int HALF_WINDOW_HEIGHT = Game::WINDOW_HEIGHT / 2;

    constexpr SDL_Rect RECTANGLE(
            Game::WINDOW_HEIGHT / TENTH_TILE / 2,
            Game::WINDOW_HEIGHT - DOUBLE_TILE,
            HALF_WINDOW_HEIGHT,
            DOUBLE_TILE - HALF_TILE
    );

    constexpr int BORDER_SIZE = (Game::WINDOW_WIDTH / 2 - (DOUBLE_TILE - HALF_TILE)) / (TENTH_TILE * 3) / 5;
}

void delay() {
    std::unique_lock lock(mutex);
    cv.wait_for(lock, std::chrono::seconds(1), [] -> bool { return not Game::getInstance().isRunning(); });
    GraphicsEngine::getInstance().getGraphic<TextBox>().pop();
}

void Battle::init() {
    this->setState(Scene::State::FADING_IN);
}

void Battle::init(Character *t) {
    this->participants[0].first = &Player::getPlayer();
    this->participants[1].first = t;

    this->states.push(State::MAIN);
}

void Battle::fadeIn() {
    TextureManager::getInstance().setScreenOpacity(SDL_ALPHA_TRANSPARENT);
    this->setState(Scene::State::FADED_IN);
    this->launch();
}

void Battle::update() {
    if (not this->isRunning) {
        Game::getInstance().changeScene(Id::OVERWORLD);;
        return;
    }
    GraphicsEngine::getInstance().update();

    if (KeyManager::getInstance().getKey(SDL_SCANCODE_BACKSPACE) and this->states.size() > 1) {
        this->states.pop();
        if (this->initFunctions.at(static_cast<std::size_t>(this->states.top())) != nullptr) {
            this->initFunctions.at(static_cast<std::size_t>(this->states.top()))();
        }

        if (GraphicsEngine::getInstance().hasAny<SelectionBox>()) {
            GraphicsEngine::getInstance().removeGraphic<SelectionBox>();
        }
    }

    if (this->updateFunctions.at(static_cast<std::size_t>(this->states.top())) != nullptr) {
        this->updateFunctions.at(static_cast<std::size_t>(this->states.top()))();
    }
}

void Battle::fadeOut() {
    static bool colorChanged = false;
    if (not colorChanged) {
        TextureManager::getInstance().setScreenColor(0, 0, 0);
        colorChanged = true;
    }

    if (not TextureManager::getInstance().isScreenOpaque()) {
        TextureManager::getInstance().darken();
    }
    else {
        this->terminate();
        this->setState(Scene::State::FADED_OUT);
        colorChanged = false;

        Pokedex::clear();
    }
}

void Battle::launch() {
    Pokedex::load();

    this->participants[0].second = std::make_unique<Data>();
    this->participants[1].second = std::make_unique<Data>();

    auto loadMap = [this](const Trainer *trainer, const bool front) -> bool {
        for (const auto &pokemon : *trainer) {
            const char *side = front ? "Front" : "Back";
            this->getParticipant(trainer).sprites[pokemon->getId()] = TextureManager::getInstance().loadTexture("sprites/Pokemon/" + pokemon->getId() + '/' + pokemon->getId() + side + ".png");
            if (this->getParticipant(trainer).sprites[pokemon->getId()] == nullptr) {
                std::clog << "Unable to load pokemon battle-sprite \"" << pokemon->getId() << front << ".png\"\n";
                Game::getInstance().terminate();
                return false;
            }
        }
        return true;
    };
    if (not loadMap(&Player::getPlayer(), false)) {
        return;
    }

    // TODO change
    // if the oppoennt is a trainer iterate through its party,
    // otherwise it is a Pokemon in which case we can load it directly
    if (const Trainer *trainer = dynamic_cast<Trainer *>(this->participants[1].first); trainer != nullptr) {
        if (not loadMap(trainer, true)) {
            return;
        }
    }
    else {
        this->participants[1].second->sprites[this->participants[1].first->getId()] = TextureManager::getInstance().loadTexture("sprites/Pokemon/" + this->participants[1].first->getId() + '/' + this->participants[1].first->getId() + "Front.png");
        if (this->participants[1].second->sprites[this->participants[1].first->getId()] == nullptr) {
            std::clog << "Unable to load pokemon battle-sprite \"" << this->participants[1].first->getId() << "Front.png\"\n";
            Game::getInstance().terminate();
        }
    }

    GraphicsEngine::getInstance().addGraphic<ResourceBar>(
            SDL_Rect(Game::WINDOW_WIDTH - 250, Map::TILE_SIZE * 4, 200, 10),
            Constants::Color::GREEN,
            5,
            100
    );
    this->participants[0].second->hpBar = &GraphicsEngine::getInstance().getGraphic<ResourceBar>();

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
            "You were challenged by " + this->participants[1].first->getId() + ' ' + this->participants[1].first->getId() + '!',
            delay
    );
    GraphicsEngine::getInstance().getGraphic<TextBox>().push(
            this->participants[1].first->initMessage(),
            [this] -> void {
                delay();
                this->participants[1].second->renderSprite = true;
            }
    );
    GraphicsEngine::getInstance().getGraphic<TextBox>().push(
            "Go " + Player::getPlayer()[0].getName() + '!',
            [this] -> void {
                delay();
                this->participants[0].second->renderSprite = true;
            }
    );

    this->initMain();
}

void Battle::render() const {
    if (this->participants[0].second == nullptr or this->participants[1].second == nullptr) {
        return;
    }
    // FIXME works but not correctly implemented
    if (this->participants[0].second->renderSprite and Player::getPlayer().canFight()) {
        TextureManager::getInstance().draw(
                this->participants[0].second->sprites.at(Player::getPlayer()[0].getName()),
                SDL_Rect(
                        HALF_TILE,
                        Game::WINDOW_HEIGHT - Map::TILE_SIZE * 5 - HALF_TILE,
                        Map::TILE_SIZE * 4,
                        Map::TILE_SIZE * 4
                )
        );
    }
    // FIXME works but not correctly implemented
    if (this->participants[1].second->renderSprite and this->participants[1].first->canFight()) {
        TextureManager::getInstance().draw(
                this->participants[1].second->sprites.at(this->participants[1].first->getAttacker()->getName()),
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

void Battle::openSelectionBox(const std::function<void()> &callback) {
    KeyManager::getInstance().lock(SDL_SCANCODE_RETURN);

    GraphicsEngine::getInstance().getGraphic<TextBox>().pop();
    GraphicsEngine::getInstance().getGraphic<TextBox>().push(
        "Select a Pokemon",
        [] -> void { KeyManager::getInstance().unlock(SDL_SCANCODE_RETURN); }
    );
    std::vector<std::pair<std::string, std::function<void()>>> pairs;

    for (int i = 1; i < Player::getPlayer().partySize(); ++i) {
        pairs.emplace_back(Player::getPlayer()[i].getName(), [this, callback, i] -> void {
            KeyManager::getInstance().lock(SDL_SCANCODE_RETURN);

            this->participants[0].second->renderSprite = false;
            // FIXME does not account for fainted Pokemon as of now
            Player::getPlayer().swapPokemon(0, i);

            GraphicsEngine::getInstance().getGraphic<TextBox>().pop();
            GraphicsEngine::getInstance().getGraphic<TextBox>().push(
                    "You swapped out " + Player::getPlayer()[i].getName() + " for " + Player::getPlayer()[0].getName() + '!',
                    [this, callback] -> void {
                        std::this_thread::sleep_for(std::chrono::seconds(1));
                        this->participants[0].second->renderSprite = true;

                        if (callback != nullptr) {
                            callback();
                        }
                    }
            );

            GraphicsEngine::getInstance().removeGraphic<SelectionBox>();
        });
    }

    GraphicsEngine::getInstance().addGraphic<SelectionBox>(SDL_Rect(50, 50, 250, 300), 5, pairs);
}

Battle::Data &Battle::getParticipant(const Character *character) {
    for (auto &[participant, data] : this->participants) {
        if (character == participant) {
            return *data;
        }
    }
    throw std::runtime_error("Invalid argument character in function Battle::getParticipant\n");
}

void Battle::initMain() {
    KeyManager::getInstance().lock(SDL_SCANCODE_RETURN);

    GraphicsEngine::getInstance().getGraphic<TextBox>().pop();
    GraphicsEngine::getInstance().getGraphic<TextBox>().push(
            "What will " + Player::getPlayer()[0].getName() + " do?",
            [] -> void {
                std::scoped_lock scopedLock(mutex);
                // unlocking the WASD keys is necessary in case the player was skipped
                KeyManager::getInstance().unlock(SDL_SCANCODE_W);
                KeyManager::getInstance().unlock(SDL_SCANCODE_A);
                KeyManager::getInstance().unlock(SDL_SCANCODE_S);
                KeyManager::getInstance().unlock(SDL_SCANCODE_D);

                KeyManager::getInstance().unlock(SDL_SCANCODE_RETURN);
                cv.notify_one();
            }
    );

    std::thread thread([this] -> void {
        std::unique_lock uniqueLock(mutex);
        cv.wait(uniqueLock);

        GraphicsEngine::getInstance().getGraphic<Panel>().clear();

        GraphicsEngine::getInstance().getGraphic<Panel>().add(
                "Fight",
                Constants::Color::RED,
                [this] -> void {
                    Mixer::getInstance().playSound("select");
                    this->changeState(State::SELECT_MOVE, false);
                }
        );
        GraphicsEngine::getInstance().getGraphic<Panel>().add(
                "Bag",
                Constants::Color::YELLOW,
                [] -> void {
                    Mixer::getInstance().playSound("select");
                }
        );
        GraphicsEngine::getInstance().getGraphic<Panel>().add(
                "Pokemon",
                Constants::Color::GREEN,
                [this] -> void {
                    Mixer::getInstance().playSound("select");
                    this->changeState(State::SELECT_POKEMON, false);
                }
        );
        GraphicsEngine::getInstance().getGraphic<Panel>().add(
                "Run",
                Constants::Color::BLUE,
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

    KeyManager::getInstance().lock(SDL_SCANCODE_RETURN);
    GraphicsEngine::getInstance().getGraphic<TextBox>().push(
            "Select a move",
            [] -> void { KeyManager::getInstance().unlock(SDL_SCANCODE_RETURN); }
    );

    GraphicsEngine::getInstance().getGraphic<Panel>().clear();

    // default assignment for if the player skips
    this->participants[0].second->move = Player::getPlayer()[0].numMoves();

    for (int i = 0; i < Player::getPlayer()[0].numMoves(); ++i) {
        GraphicsEngine::getInstance().getGraphic<Panel>().add(
                Player::getPlayer()[0][i].getName(),
                typeToColor(Player::getPlayer()[0][i].getType()),
                [this, i] -> void {
                    Mixer::getInstance().playSound("select");
                    this->handleTurn(i);
                    this->changeState(State::ENGAGE, true);
                }
        );
    }
}

void Battle::initPokemon() {
    GraphicsEngine::getInstance().getGraphic<Panel>().clear();

    GraphicsEngine::getInstance().getGraphic<TextBox>().pop();

    KeyManager::getInstance().lock(SDL_SCANCODE_RETURN);
    GraphicsEngine::getInstance().getGraphic<TextBox>().push(
            "Select a Pokemon",
            [] -> void { KeyManager::getInstance().unlock(SDL_SCANCODE_RETURN); }
    );

    std::vector<std::pair<std::string, std::function<void()>>> pairs;

    pairs.emplace_back(Player::getPlayer()[0].getName(), [this] -> void {
            KeyManager::getInstance().lock(SDL_SCANCODE_RETURN);

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
            this->participants[0].second->renderSprite = false;

            GraphicsEngine::getInstance().removeGraphic<SelectionBox>();
            Player::getPlayer().swapPokemon(0, i);
            GraphicsEngine::getInstance().getGraphic<TextBox>().pop();
            GraphicsEngine::getInstance().getGraphic<TextBox>().push(
                    "You swapped out " + Player::getPlayer()[i].getName() + " for " + Player::getPlayer()[0].getName() + '!',
                    [this] -> void {
                        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                        this->participants[0].second->renderSprite = true;
                        this->handleTurn(Player::getPlayer()[0].numMoves());
                        this->changeState(State::ENGAGE, true);
                    }
            );
        });
    }

    GraphicsEngine::getInstance().addGraphic<SelectionBox>(SDL_Rect(50, 50, 250, 300), 5, pairs);
}

void Battle::initEngage() {
    // pops the message that does not belong
    GraphicsEngine::getInstance().getGraphic<TextBox>().pop();
    GraphicsEngine::getInstance().getGraphic<Panel>().clear();

    KeyManager::getInstance().lock(SDL_SCANCODE_RETURN);
    KeyManager::getInstance().lock(SDL_SCANCODE_BACKSPACE);
}

std::string statusMessage(const Pokemon &pokemon) {
    auto damageMessage = [&pokemon](const char *status) -> std::string {
        return pokemon.getName() + " took " + std::to_string(static_cast<int>(std::round(pokemon.getHp().getMax() * 0.0625))) + " damage from it's " + status + '!';
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

void Battle::engage(Character *attacker, Character *defender) {
    const int move = this->getParticipant(attacker).move;
    bool &skip = this->getParticipant(defender).skip;
    bool &target = this->getParticipant(defender).renderSprite;

    (*attacker->getAttacker())[move].action(*attacker->getAttacker(), *defender->getAttacker(), skip);

    {
        std::vector<std::pair<std::string, std::function<void()>>> pairs;
        for (const auto &message : (*attacker->getAttacker())[move].actionMessage(*attacker->getAttacker(), *defender->getAttacker(), skip)) {
            pairs.emplace_back(message, delay);
        }
        GraphicsEngine::getInstance().getGraphic<TextBox>().push(pairs);
    }

    if (defender->getAttacker()->getHp().empty()) {
        skip = true;
        GraphicsEngine::getInstance().getGraphic<TextBox>().push(
                defender->getAttacker()->getName() + " fained!",
                [this, attacker, defender, &target] -> void {
                    std::this_thread::sleep_for(std::chrono::seconds(1));

                    target = false;
                    defender->handleFaint();
                    if (defender->canFight()) {
                        defender->handleSwitchOut(target);
                    }
                    else {
                        attacker->handleVictory();

                        std::vector<std::pair<std::string, std::function<void()>>> pairs;
                        {
                            std::vector<std::string> message = defender->getDefeatMessage();
                            if (message.size() == 2) {
                                pairs.emplace_back(message[0], delay);
                            }
                            pairs.emplace_back(message.back(),[this] -> void {
                                    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
                                    this->isRunning = false;
                            });
                        }

                        GraphicsEngine::getInstance().getGraphic<TextBox>().pop();
                        GraphicsEngine::getInstance().getGraphic<TextBox>().push(pairs);
                    }
                }
        );
    }
}

void Battle::preStatus(Character *first, Character *second) {
    auto hasStatusCondition = [](const StatusCondition status) -> bool {
        if (status == StatusCondition::PARALYSIS) {
            return binomial(25.0);
        }
        return status == StatusCondition::FREEZE or status == StatusCondition::SLEEP;
    };

    const auto action = [this, &hasStatusCondition](Character *attacker, Character *defender, const int move) -> void {
        if (move < attacker->getAttacker()->numMoves()) {
            if (not hasStatusCondition(attacker->getAttacker()->getStatus())) {
                this->engage(attacker, defender);
            }
            else {
                GraphicsEngine::getInstance().getGraphic<TextBox>().push(statusMessage(*attacker->getAttacker()), delay);
            }
        }
    };

    const int firstMove = this->getParticipant(first).move;
    const int secondMove = this->getParticipant(second).move;

    action(first, second, firstMove);
    if (not this->getParticipant(second).skip and first->canFight() and second->canFight()) {
        action(second, first, secondMove);
    }
}

void Battle::postStatus(Character *first, Character *second) {
    // if one of the trainers here can no longer fight, exit
    if (not Player::getPlayer().canFight() or not this->participants[1].first->canFight()) {
        return;
    }

    bool (*hasStatusCondition)(StatusCondition) = [](const StatusCondition status) -> bool {
        return status == StatusCondition::BURN or status == StatusCondition::POISON;
    };

    auto postStatus = [this](Character *receiver, ResourceBar *resourceBar) -> void {
        int damage = static_cast<int>(receiver->getAttacker()->getHp().getMax() * 0.0625);
        receiver->getAttacker()->getHp().lower(damage);
        GraphicsEngine::getInstance().getGraphic<TextBox>().push(
                statusMessage(*receiver->getAttacker()),
                [resourceBar, damage] -> void {
                    if (resourceBar != nullptr) {
                        resourceBar->getProgress().lower(damage);
                    }
                }
        );

        if (receiver->getAttacker()->getHp().empty()) {
            GraphicsEngine::getInstance().getGraphic<TextBox>().push(receiver->getAttacker()->getName() + " fainted!");
            receiver->handleFaint();

            if (not receiver->canFight()) {
                std::vector<std::pair<std::string, std::function<void()>>> pairs;
                {
                    std::vector<std::string> message = receiver->getDefeatMessage();

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

    if (hasStatusCondition(first->getAttacker()->getStatus())) {
        postStatus(first, this->getParticipant(first).hpBar);
    }
    if (hasStatusCondition(second->getAttacker()->getStatus())) {
        postStatus(second, this->getParticipant(second).hpBar);
    }
}

void Battle::handleTurn(const int move) {
    this->participants[0].second->move = move;
    this->participants[1].second->move = this->participants[1].first->getAttacker()->numMoves();

    if (this->participants[1].first->getAttacker()->canAttack()) {
        while (true) {
            this->participants[1].second->move = generateInteger(0, this->participants[1].first->getAttacker()->numMoves() - 1);
            if ((*this->participants[1].first->getAttacker())[this->participants[1].second->move].canUse()) {
                break;
            }
        }
    }

    // if neither the player nor the opponent is attempting to attack
    if (this->participants[0].second->move == Player::getPlayer()[0].numMoves() and this->participants[1].second->move == this->participants[1].first->getAttacker()->numMoves()) {
        std::clog << "Not yet implemented where neither choose to attack\n";
        Game::getInstance().terminate();
    }
    else {
        const bool playerFirst = [this] -> bool {
            // if the opponent is not intending to attack, the player will attack first
            if (this->participants[1].second->move == this->participants[1].first->getAttacker()->numMoves()) {
                return true;
            }
            // if the player is not intending to attack, the opponent will attack first
            if (this->participants[0].second->move == Player::getPlayer()[0].numMoves()) {
                return false;
            }

            const bool samePrio = Player::getPlayer()[0][this->participants[0].second->move].isPriority() == (*this->participants[1].first->getAttacker())[this->participants[1].second->move].isPriority();
            const bool sameSpeed = Player::getPlayer()[0].rivalsInSpeed(*this->participants[1].first->getAttacker());

            // if the player and the opponent's moves have matching priority,
            if (samePrio) {
                // if the player and the opponent have matching speeds, decide randomly
                if (sameSpeed) {
                    return binomial();
                }
                // otherwise, the faster entity goes first
                return Player::getPlayer()[0].isFasterThan(*this->participants[1].first->getAttacker());
            }
            // if the player and the opponent have matching speeds, decide randomly
            if (sameSpeed) {
                return binomial();
            }
            // otherwise, if the player either is using a priority move or is faster, then it goes first;
            // and vice versa
            return Player::getPlayer()[0][this->participants[0].second->move].isPriority() or Player::getPlayer()[0].isFasterThan(*this->participants[1].first->getAttacker());
        }();
        Character *first = playerFirst ? &Player::getPlayer() : this->participants[1].first;
        Character *second = playerFirst ? this->participants[1].first : &Player::getPlayer();

        this->preStatus(first, second);
        this->postStatus(first, second);
    }

    ++this->turn;

    // reset flags
    for (const auto &dataset: this->participants | std::views::values) {
        dataset->skipCounter = std::max(dataset->skipCounter - 1, 0);
        if (dataset->skipCounter == 0) {
            dataset->skip = false;
        }
    }
}

void Battle::updateEngage() {
    if (GraphicsEngine::getInstance().getGraphic<TextBox>().empty()) {
        this->changeState(State::MAIN, true);
        KeyManager::getInstance().unlock(SDL_SCANCODE_RETURN);
        KeyManager::getInstance().unlock(SDL_SCANCODE_BACKSPACE);
    }
}

void Battle::handleRun() {
    GraphicsEngine::getInstance().getGraphic<TextBox>().pop();
    GraphicsEngine::getInstance().getGraphic<Panel>().clear();

    KeyManager::getInstance().lock(SDL_SCANCODE_W);
    KeyManager::getInstance().lock(SDL_SCANCODE_A);
    KeyManager::getInstance().lock(SDL_SCANCODE_S);
    KeyManager::getInstance().lock(SDL_SCANCODE_D);

    if (const auto *trainer = dynamic_cast<Trainer *>(this->participants[1].first); trainer == nullptr) {
        KeyManager::getInstance().lock(SDL_SCANCODE_RETURN);
        GraphicsEngine::getInstance().getGraphic<TextBox>().push(
                "You can't run away from a trainer battle!",
                [this] -> void {
                    delay();
                    this->initMain();
                }
        );
    }
    else {
        const int opponentSpeed = static_cast<int>(this->participants[1].first->getAttacker()->getBaseStat("Speed") / 4) % 256;

        if (const int odds = static_cast<int>(Player::getPlayer()[0].getBaseStat("Speed") * 32 / opponentSpeed) + 30;
            opponentSpeed == 0 or odds > 255 or generateInteger(0, 255) < odds) {
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
                            this->changeState(State::ENGAGE, true);
                    }
            );
        }
    }
}

void Battle::terminate() {
    this->turn = 0;

    while (not this->states.empty()) {
        this->states.pop();
    }

    auto cleanMap = [](std::unordered_map<std::string, SDL_Texture *> &map) -> void {
        for (auto &[id, sprite] : map) {
            if (sprite != nullptr) {
                SDL_DestroyTexture(sprite);
                if (strlen(SDL_GetError()) > 0){
                    std::clog << "Unable to destroy pokemon battle-sprite \"" << id << ": " << SDL_GetError() << '\n';
                    SDL_ClearError();
                }
            }
        }
        map.clear();
    };

    cleanMap(this->participants[0].second->sprites);
    cleanMap(this->participants[1].second->sprites);

    this->participants[0].second.reset(nullptr);
    this->participants[1].second.reset(nullptr);

    KeyManager::getInstance().unlock(SDL_SCANCODE_W);
    KeyManager::getInstance().unlock(SDL_SCANCODE_A);
    KeyManager::getInstance().unlock(SDL_SCANCODE_S);
    KeyManager::getInstance().unlock(SDL_SCANCODE_D);

    KeyManager::getInstance().unlock(SDL_SCANCODE_RETURN);

    Player::getPlayer().setState(Character::State::IDLE);
    GraphicsEngine::getInstance().clear();

    if (Mix_FadeOutMusic(2000) == 0) {
        std::clog << "Error fading out \"" << getInstance<Overworld>().getCurrentMap().getId()
                  << "\": " << SDL_GetError() << '\n';
        SDL_ClearError();
        Game::getInstance().terminate();
        return;
    }

    Mix_HookMusicFinished([] -> void {
        Mixer::getInstance().playMusic(getInstance<Overworld>().getCurrentMap().getId());
    });

    this->isRunning = true;
}

void Battle::changeState(const State x, const bool clear) {
    if (clear) {
        while (not this->states.empty()) {
            this->states.pop();
        }
    }
    this->states.push(x);
    if (this->initFunctions.at(static_cast<std::size_t>(this->states.top())) != nullptr) {
        this->initFunctions.at(static_cast<std::size_t>(this->states.top()))();
    }
}
