//
// Created by Miles Youngblood on 6/13/2022.
//

#include "Trainer.h"

Trainer::Trainer(const char *name, const int x, const int y) : Entity(name, x, y), items() {
    //FIXME change these to not be Hilbert
    this->setAnimation(Direction::UP, "sprites\\Hilbert\\HilbertSpriteSheetUp.png", 4, 1);
    this->setAnimation(Direction::DOWN, "sprites\\Hilbert\\HilbertSpriteSheetDown.png", 4, 1);
    this->setAnimation(Direction::LEFT, "sprites\\Hilbert\\HilbertSpriteSheetLeft.png", 4, 1);
    this->setAnimation(Direction::RIGHT, "sprites\\Hilbert\\HilbertSpriteSheetRight.png", 4, 1);
}

Trainer::Trainer(const char *name, const int x, const int y, const Direction direction) : Trainer(name, x, y) {
    this->setDirection(direction);
}

Trainer::Trainer(const char *name, const int x, const int y, const Direction direction, const int vision)
        : Trainer(name, x, y, direction) {
    this->setVision(vision);
}

void Trainer::init() {
    Trainer::getItemTypeId<RestoreItem>();
    Trainer::getItemTypeId<StatusItem>();
    Trainer::getItemTypeId<PokeBall>();
    Trainer::getItemTypeId<BattleItem>();
}

int Trainer::partySize() const {
    return static_cast<int>(this->party.size());
}

void Trainer::removePokemon(const int index) {
    try {
        // decrement the faint counter if the Pokémon we're removing is fainted
        if (this->party.at(index).isFainted()) {
            --this->numFainted;
        }

        this->party.erase(this->party.begin() + index);
    }
    catch (const std::out_of_range &e) {
        throw std::out_of_range(std::string("Error removing Pokemon: ") + e.what() + '\n');
    }
}

void Trainer::swapPokemon(const int a, const int b) {
    try {
        Pokemon copy = std::move(this->party.at(a));
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

void Trainer::addItem(std::unique_ptr<Item> toAdd) {
    const int type = static_cast<int>(toAdd->getClass());
    if (this->items.at(type).size() == Trainer::MAX_ITEMS) {
        return;
    }

    for (const auto &i : this->items.at(type)) {
        // if item already exists within our inventory
        if (toAdd->getId() == i->getId()) {
            i->add();
            return;
        }
    }

    this->items.at(type).push_back(std::move(toAdd));
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

Pokemon &Trainer::operator[](const int index) {
    try {
        return this->party.at(index);
    }
    catch (const std::out_of_range &e) {
        throw std::out_of_range(std::string("Error accessing party: ") + e.what() + '\n');
    }
}

const Pokemon &Trainer::operator[](const int index) const {
    try {
        return this->party.at(index);
    }
    catch (const std::out_of_range &e) {
        throw std::out_of_range(std::string("Error accessing party: ") + e.what() + '\n');
    }
}

Trainer::operator bool() const {
    return not this->party.empty();
}

bool Trainer::canFight() const {
    return not this->party.empty();
}
