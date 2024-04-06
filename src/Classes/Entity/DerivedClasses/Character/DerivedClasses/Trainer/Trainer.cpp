//
// Created by Miles Youngblood on 6/13/2022.
//

#include "../../../../../Singleton/DerivedClasses/Game/Game.h"
#include "../../../../../Singleton/DerivedClasses/GraphicsEngine/GraphicsEngine.h"
#include "../../../../../Singleton/DerivedClasses/Mixer/Mixer.h"
#include "../../../../../Singleton/DerivedClasses/KeyManager/KeyManager.h"
#include "Trainer.h"

void Trainer::init() {
    this->items[typeid(RestoreItem).hash_code()];
    this->items[typeid(StatusItem).hash_code()];
    this->items[typeid(PokeBall).hash_code()];
    this->items[typeid(BattleItem).hash_code()];
}

Trainer::Trainer(const char *id, int x, int y, Direction direction) : Character(id, x, y, direction) {
    this->init();
}

Trainer::Trainer(const char *id, const char *name, int x, int y, Direction direction, int vision)
        : Character(id, name, x, y, direction, vision) {
    this->init();
}

void Trainer::addPokemon(const char *id) {
    if (this->party.size() == Trainer::MAX_POKEMON) {
        return;
    }
    this->party.push_back(std::move(Pokemon(id)));
}

void Trainer::addPokemon(Pokemon pokemon) {
    if (this->party.size() == Trainer::MAX_POKEMON) {
        return;
    }
    this->party.push_back(std::move(pokemon));
}

void Trainer::removePokemon(long long int index) {
    try {
        // decrement the faint counter if the Pokémon we're removing is fainted
        if (this->party.at(index).isFainted()) {
            //--this->numFainted;
        }

        this->party.erase(this->party.cbegin() + index);
    }
    catch (const std::out_of_range &e) {
        throw std::out_of_range(std::string("Error removing Pokemon: ") + e.what() + '\n');
    }
}

void Trainer::swapPokemon(std::size_t a, std::size_t b) {
    try {
        Pokemon copy = std::move(this->party.at(a));
        this->party.at(a) = std::move(this->party.at(b));
        this->party.at(b) = std::move(copy);
    }
    catch (const std::out_of_range &e) {
        throw std::out_of_range(std::string("Error swapping Pokemon: ") + e.what() + '\n');
    }
}

void Trainer::addItem(const std::string &id, int n) {
    this->addItem(std::move(itemMap.at(id)(n)));
}

void Trainer::addItem(std::unique_ptr<Item> item) {
    try {
        // if item already exists within our inventory
        if (this->items.at(item->getClass()).contains(item->getName())) {
            this->items.at(item->getClass()).at(item->getName())->add(item->getQuantity());
            return;
        }

        this->items.at(item->getClass())[item->getName()] = std::move(item);
    }
    catch (const std::exception &e) {
        throw std::runtime_error(std::string("Error adding item: ") + e.what() + '\n');
    }
}

Pokemon &Trainer::operator[](std::size_t index) {
    try {
        return this->party.at(index);
    }
    catch (const std::out_of_range &e) {
        throw std::out_of_range(std::string("Error accessing party: ") + e.what() + '\n');
    }
}

std::vector<Pokemon>::iterator Trainer::begin() {
    return this->party.begin();
}

std::vector<Pokemon>::const_iterator Trainer::begin() const {
    return this->party.cbegin();
}

std::vector<Pokemon>::iterator Trainer::end() {
    return this->party.end();
}

std::vector<Pokemon>::const_iterator Trainer::end() const {
    return this->party.cend();
}

std::size_t Trainer::partySize() const {
    return this->party.size();
}

void Trainer::handleFaint() {
    this->party.erase(this->party.cbegin());
}

std::vector<std::string> Trainer::winMessage() const {
    return std::vector<std::string>({ "You've run out of usable Pokemon!", "You blacked out!" });
}

bool Trainer::canFight() const {
    return not this->party.empty();
}

bool Trainer::isTrainer() const {
    return true;
}

void Trainer::idle() {
    this->act();

    static int frameCounter = 0;    // makes this that spotted the player stand still for a set number of frames
    static bool haltMusic = true;
    static bool playMusic = true;

    static const auto not_moving = [](Character *entity) -> bool {
        return entity->getState() == Character::State::IDLE or entity->getState() == Character::State::IMMOBILE;
    };

    // checks if the player is in LoS for this
    if (not_moving(&Player::getPlayer()) and this->canFight() and not_moving(this) and this->keepLooping and
        this->hasVisionOf(&Player::getPlayer())) {
        if (haltMusic) {
            Player::getPlayer().setState(Character::State::IMMOBILE);
            this->setState(Character::State::IMMOBILE);
            momentum = false;

            Mix_HaltMusic();
            haltMusic = false;

            GraphicsEngine::getInstance().addGraphic<TimedVisual>(
                    "exclamation.png",
                    50 * (Game::getInstance().getFps() / 30) / 2,
                    SDL_Rect(
                            this->getScreenX(),
                            this->getScreenY() - Map::TILE_SIZE,
                            Map::TILE_SIZE,
                            Map::TILE_SIZE
                    )
            );
            Mixer::getInstance().playSound("spotted");
        }

        ++frameCounter;
        if (frameCounter < 50 * (Game::getInstance().getFps() / 30)) {
            return;
        }

        if (playMusic) {
            Mixer::getInstance().playMusic("GymBattle");
            playMusic = false;
        }

        if (not this->isNextTo(&Player::getPlayer())) {
            this->shift(this->getDirection(), Character::WALK_SPEED);
            this->incPixelCounter(Character::WALK_SPEED);

            if (this->getWalkCounter() % (Map::TILE_SIZE / 2) == 0) {
                this->updateAnimation();
            }

            if (this->getWalkCounter() % Map::TILE_SIZE == 0) {
                this->moveForward();
                this->resetPixelCounter();
            }
        }
        else {
            Player::getPlayer().face(this);

            Overworld::createTextBox(this->getDialogue());

            this->keepLooping = false;

            frameCounter = 0;
            haltMusic = true;
            playMusic = true;
        }
    }
}

void Trainer::interact() {
    // if the player manually clicked Enter
    // (the trainer will have opened the TextBox if it has contacted the player already)
    if (not GraphicsEngine::getInstance().hasAny<TextBox>()) {
        KeyManager::getInstance().lockKey(SDL_Scancode::SDL_SCANCODE_RETURN);

        Player::getPlayer().setState(Character::State::IMMOBILE);
        this->face(&Player::getPlayer());

        // only create the textbox here if the trainer cannot fight;
        // the program will loop back to checkForOpponents() in the next cycle
        // and create it there if the trainer can fight
        if (not this->canFight()) {
            this->setState(Character::State::IMMOBILE);
            Overworld::createTextBox(this->getDialogue());
        }
    }
    else if (not GraphicsEngine::getInstance().getGraphic<TextBox>().isPrinting()) {
        // if the textbox still has messages to print
        if (not GraphicsEngine::getInstance().getGraphic<TextBox>().empty()) {
            GraphicsEngine::getInstance().getGraphic<TextBox>().pop();

            // the 'accept' sound effect will play for every pop except the last
            if (not GraphicsEngine::getInstance().getGraphic<TextBox>().empty()) {
                Mixer::getInstance().playSound("accept");
            }
            else {
                GraphicsEngine::getInstance().removeGraphic<TextBox>();

                if (this->canFight()) {
                    Game::getInstance().changeScene(Scene::Id::BATTLE);
                    Game::getInstance().setRenderColor(Constants::Color::WHITE);

                    Scene::getInstance<Battle>().init(this);

                    Mixer::getInstance().playMusic("TrainerBattle");
                }
                else {
                    Player::getPlayer().setState(Character::State::IDLE);
                    this->setState(Character::State::IDLE);
                }
            }
        }
        // re-lock the Enter key
        KeyManager::getInstance().lockKey(SDL_Scancode::SDL_SCANCODE_RETURN);

        // sets a cool-down period before the Enter key can be registered again;
        // this is needed because the program will register a button as
        // being pressed faster than the user can lift their finger
        std::thread coolDown([] -> void {
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            KeyManager::getInstance().unlockKey(SDL_Scancode::SDL_SCANCODE_RETURN);
        });
        coolDown.detach();

        keyDelay.reset();
    }
}
