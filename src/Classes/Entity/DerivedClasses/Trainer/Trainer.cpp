//
// Created by Miles Youngblood on 6/13/2022.
//

#include "Trainer.h"

Trainer::Trainer(const char *name, const int x, const int y) : Entity(name, x, y), items(), numItems() {
    //FIXME change these to not be Hilbert
    this->setUpAnimation(
            TextureManager::getInstance().loadTexture(R"(\assets\images\sprites\Hilbert\HilbertSpriteSheetUp.png)"),
            4, 1);
    this->setDownAnimation(
            TextureManager::getInstance().loadTexture(R"(\assets\images\sprites\Hilbert\HilbertSpriteSheetDown.png)"),
            4, 1);
    this->setLeftAnimation(
            TextureManager::getInstance().loadTexture(R"(\assets\images\sprites\Hilbert\HilbertSpriteSheetLeft.png)"),
            4, 1);
    this->setRightAnimation(
            TextureManager::getInstance().loadTexture(R"(\assets\images\sprites\Hilbert\HilbertSpriteSheetRight.png)"),
            4, 1);
}

Trainer::Trainer(const char *name, const int x, const int y, const int direction) : Trainer(name, x, y) {
    this->setDirection(static_cast<Direction>(direction));
}

Trainer::Trainer(const char *name, const int x, const int y, const int direction, const int vision)
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
    return this->numPokemon;
}

void Trainer::addPokemon(std::unique_ptr<Pokemon> toAdd) {
    if (this->numPokemon == Trainer::MAX_POKEMON) {
        return;
    }

    this->party.push_back(std::move(toAdd));
    ++this->numPokemon;
}

void Trainer::removePokemon(const int index) {
    if (index < 0 or 5 < index) {
        return;
    }

    // decrement the faint counter if the Pokémon we're removing is fainted
    if (this->party[index]->isFainted()) {
        --this->numFainted;
    }

    this->party.erase(this->party.begin() + index);
    --this->numPokemon;
}

void Trainer::swapPokemon(const int first, const int second) {
    std::unique_ptr<Pokemon> copy = std::move(this->party[first]);
    this->party[first] = std::move(this->party[second]);
    this->party[second] = std::move(copy);
}

void Trainer::clearParty() {
    for (int i = 0; i < this->numPokemon; ++i) {
        this->party[i].reset();
    }
    this->numPokemon = 0;
}

void Trainer::addItem(std::unique_ptr<Item> toAdd) {
    const int type = static_cast<int>(toAdd->getType());
    if (this->numItems.at(type) == Trainer::MAX_ITEMS) {
        return;
    }

    for (int i = 0; i < this->numItems.at(type); ++i) {
        // if item already exists within our inventory
        if (toAdd->getID() == this->items.at(type)[i]->getID()) {
            this->items.at(type)[i]->add();
            return;
        }
    }

    this->items.at(type).push_back(std::move(toAdd));
    ++this->numItems.at(type);
}

void Trainer::removeItem(const int type, const int index) {
    if (type < 0 or 3 < type) {
        throw std::runtime_error("Out of bounds: removeItem");
    }

    this->items.at(type).erase(this->items.at(type).begin() + index);
    --this->numItems.at(type);
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

Pokemon &Trainer::operator[](const int spot) {
    if (5 < spot or spot < 0) {
        throw std::runtime_error("Index out of bounds");
    }
    return *this->party[spot];
}

const Pokemon &Trainer::operator[](const int spot) const {
    if (5 < spot or spot < 0) {
        throw std::runtime_error("Index out of bounds");
    }
    return *this->party[spot];
}

Trainer::operator bool() const {
    return this->numPokemon > 0;
}

bool Trainer::canFight() const {
    return this->numPokemon > 0;
}
