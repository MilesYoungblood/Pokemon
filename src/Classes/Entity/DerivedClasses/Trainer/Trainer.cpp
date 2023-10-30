//
// Created by Miles Youngblood on 6/13/2022.
//

#include "Trainer.h"

Trainer::Trainer() : items(), numItems() {
    //FIXME change these to not be Hilbert
    this->setFrontModel(TextureManager::LoadTexture(PROJECT_PATH + R"(\sprites\Hilbert_front.png)"));
    this->setBackModel(TextureManager::LoadTexture(PROJECT_PATH + R"(\sprites\Hilbert_back.png)"));
    this->setLeftModel(TextureManager::LoadTexture(PROJECT_PATH + R"(\sprites\Hilbert_left.png)"));
    this->setRightModel(TextureManager::LoadTexture(PROJECT_PATH + R"(\sprites\Hilbert_right.png)"));

    this->setCurrentModel(this->getFrontModel());
}

Trainer::Trainer(const int x, const int y) : Entity(x, y), items(), numItems() {
    //FIXME change these to not be Hilbert
    this->setFrontModel(TextureManager::LoadTexture(PROJECT_PATH + R"(\sprites\Hilbert_front.png)"));
    this->setBackModel(TextureManager::LoadTexture(PROJECT_PATH + R"(\sprites\Hilbert_back.png)"));
    this->setLeftModel(TextureManager::LoadTexture(PROJECT_PATH + R"(\sprites\Hilbert_left.png)"));
    this->setRightModel(TextureManager::LoadTexture(PROJECT_PATH + R"(\sprites\Hilbert_right.png)"));

    this->setCurrentModel(this->getFrontModel());
}

Trainer::Trainer(const int x, const int y, const int direction) : Trainer(x, y) {
    this->setDirection(static_cast<Direction>(direction));
}

Trainer::Trainer(const int x, const int y, const int direction, const int vision) : Trainer(x, y, direction) {
    this->setVision(vision);
}

Trainer::~Trainer() {
    std::cout << "Trainer destructor called!\n";
    for (int i = 0; i < this->numPokemon; ++i) {
        std::cout << "\tDeleting " << this->party[i]->getName() << "!\n";
        //delete this->party[i];
        //this->party[i] = nullptr;
    }
    std::cout << '\n';

    for (int i = 0; i < Trainer::NUM_ITEM_TYPES; ++i) {
        for (int j = 0; j < this->numItems.at(i); ++j) {
            std::cout << "Deleting " << this->items.at(i)[j]->getName() << "!\n";
            //delete this->items.at(i)[j];
            //this->items.at(i)[j] = nullptr;
        }
    }
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

    // decrement the faint count if the Pokémon we're removing is fainted
    if (this->party[index]->isFainted()) {
        --this->numFainted;
    }
    //delete this->party[index];
    //this->party[index] = nullptr;

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

int Trainer::getNumItems(const int type) const {
    if (type < 0 or 3 < type) {
        throw std::runtime_error("Out of bounds: getNumItems");
    }
    return this->numItems.at(type);
}

Item & Trainer::getItem(const int type, const int item) const {
    return *this->items.at(type)[item];
}

void Trainer::addItem(std::unique_ptr<Item> toAdd) {
    const int type = static_cast<int>(toAdd->getType());
    if (this->numItems.at(type) == Trainer::MAX_ITEMS) {
        return;
    }

    this->items.at(type).push_back(std::move(toAdd));
    ++this->numItems.at(type);
}

void Trainer::removeItem(const int type, const int index) {
    if (type < 0 or 3 < type) {
        throw std::runtime_error("Out of bounds: removeItem");
    }

    //delete this->items.at(type)[index];
    //this->items.at(type)[index] = nullptr;

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

Pokemon & Trainer::operator[](const int spot) {
    if (5 < spot or spot < 0) {
        throw std::runtime_error("Index out of bounds");
    }
    return *this->party[spot];
}

const Pokemon & Trainer::operator[](const int spot) const {
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
