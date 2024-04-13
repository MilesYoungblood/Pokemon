//
// Created by Miles Youngblood on 6/13/2022.
//

#include "../../../../../Singleton/DerivedClasses/Game/Game.h"
#include "../../../../../Singleton/DerivedClasses/GraphicsEngine/GraphicsEngine.h"
#include "../../../../../Singleton/DerivedClasses/Mixer/Mixer.h"
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
    return;
    //this->act();

    static int frameCounter = 0;    // makes this that spotted the player stand still for a set number of frames
    static bool haltMusic = true;
    static bool playMusic = true;

    static const auto not_moving = [](Character *entity) -> bool {
        return entity->getState() == Character::State::IDLE or entity->getState() == Character::State::IMMOBILE;
    };

    // checks if the player is in LoS for this
    if (not_moving(&Player::getPlayer()) and Player::getPlayer().canFight() and this->canFight() and
        not_moving(this) and this->keepLooping and this->hasVisionOf(&Player::getPlayer())) {
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

            if (this->getPixelCounter() % (Map::TILE_SIZE / 2) == 0) {
                this->updateAnimation();
            }

            if (this->getPixelCounter() % Map::TILE_SIZE == 0) {
                this->moveForward();
                this->resetPixelCounter();
            }
        }
        else {
            Player::getPlayer().face(this);

            if (not GraphicsEngine::getInstance().hasAny<TextBox>()) {
                Overworld::createTextBox(this->getDialogue());
            }

            this->keepLooping = false;

            frameCounter = 0;
            haltMusic = true;
            playMusic = true;
        }
    }
}
