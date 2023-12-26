//
// Created by Miles Youngblood on 6/13/2022.
//

#include "Trainer.h"

Trainer::Trainer() {
    this->items[typeid(RestoreItem).hash_code()];
    this->items[typeid(StatusItem).hash_code()];
    this->items[typeid(PokeBall).hash_code()];
    this->items[typeid(BattleItem).hash_code()];
}

Trainer::Trainer(const char *name, int x, int y) : Entity(name, x, y) {
    this->items[typeid(RestoreItem).hash_code()];
    this->items[typeid(StatusItem).hash_code()];
    this->items[typeid(PokeBall).hash_code()];
    this->items[typeid(BattleItem).hash_code()];

    //FIXME change these to not be Hilbert
    this->setAnimation(Direction::UP, "sprites/Hilbert/HilbertSpriteSheetUp.png");
    this->setAnimation(Direction::DOWN, "sprites/Hilbert/HilbertSpriteSheetDown.png");
    this->setAnimation(Direction::LEFT, "sprites/Hilbert/HilbertSpriteSheetLeft.png");
    this->setAnimation(Direction::RIGHT, "sprites/Hilbert/HilbertSpriteSheetRight.png");
}

Trainer::Trainer(const char *name, int x, int y, Direction direction) : Trainer(name, x, y) {
    this->setDirection(direction);
}

Trainer::Trainer(const char *name, int x, int y, Direction direction, int vision) : Trainer(name, x, y, direction) {
    this->setVision(vision);
}

std::size_t Trainer::partySize() const {
    return this->party.size();
}

void Trainer::addPokemon(std::unique_ptr<Pokemon> toAdd) {
    if (this->party.size() == Trainer::MAX_POKEMON) {
        return;
    }

    this->party.push_back(std::move(toAdd));
}

void Trainer::removePokemon(long long int index) {
    try {
        // decrement the faint counter if the Pokémon we're removing is fainted
        if (this->party.at(index)->isFainted()) {
            --this->numFainted;
        }

        this->party.erase(this->party.begin() + index);
    }
    catch (const std::out_of_range &e) {
        throw std::out_of_range(std::string("Error removing Pokemon: ") + e.what() + '\n');
    }
}

void Trainer::swapPokemon(std::size_t a, std::size_t b) {
    try {
        std::unique_ptr<Pokemon> copy = std::move(this->party.at(a));
        this->party.at(a) = std::move(this->party.at(b));
        this->party.at(b) = std::move(copy);
    }
    catch (const std::out_of_range &e) {
        throw std::out_of_range(std::string("Error swapping Pokemon: ") + e.what() + '\n');
    }
}

void Trainer::clearParty() {
    this->party.clear();
}

void Trainer::incFaintCount() {
    ++this->numFainted;
}

void Trainer::decFaintCount() {
    --this->numFainted;
}

int Trainer::getFaintCount() const {
    return this->numFainted;
}

Pokemon &Trainer::operator[](std::size_t index) {
    try {
        return *this->party.at(index);
    }
    catch (const std::out_of_range &e) {
        throw std::out_of_range(std::string("Error accessing party: ") + e.what() + '\n');
    }
}

const Pokemon &Trainer::operator[](std::size_t index) const {
    try {
        return *this->party.at(index);
    }
    catch (const std::out_of_range &e) {
        throw std::out_of_range(std::string("Error accessing party: ") + e.what() + '\n');
    }
}

std::vector<std::unique_ptr<Pokemon>>::iterator Trainer::begin() {
    return this->party.begin();
}

std::vector<std::unique_ptr<Pokemon>>::iterator Trainer::end() {
    return this->party.end();
}

bool Trainer::canFight() const {
    return not this->party.empty();
}
