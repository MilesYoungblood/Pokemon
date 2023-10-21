//
// Created by Miles Youngblood on 6/13/2022.
//

#include "Trainer.h"

Trainer::Trainer() : items(), numItems() {}

Trainer::Trainer(const int x, const int y) : Entity(x, y), items(), numItems() {}

Trainer::Trainer(const std::initializer_list<Pokemon*> &pokemon, const int x, const int y) : Trainer(x, y) {
    for (const auto &p : pokemon) {
        if (this->numPokemon == Trainer::MAX_POKEMON) {
            break;
        }

        this->party.push_back(p);
        ++this->numPokemon;
    }
}

Trainer::Trainer(const std::initializer_list<Pokemon *> &pokemon, const int x, const int y, int vision) : Trainer(pokemon, x, y) {
    this->setVision(vision);

    //FIXME change these to not be Hilbert
    this->setFrontModel(TextureManager::LoadTexture(PROJECT_PATH + R"(\sprites\Hilbert_front.png)"));
    this->setBackModel(TextureManager::LoadTexture(PROJECT_PATH + R"(\sprites\Hilbert_back.png)"));
    this->setLeftModel(TextureManager::LoadTexture(PROJECT_PATH + R"(\sprites\Hilbert_left.png)"));
    this->setRightModel(TextureManager::LoadTexture(PROJECT_PATH + R"(\sprites\Hilbert_right.png)"));

    this->setCurrentModel(this->getFrontModel());
}

Trainer::~Trainer() {
    std::cout << "Trainer destructor called!\n";
    for (int i = 0; i < this->numPokemon; ++i) {
        std::cout << "\tDeleting " << this->party[i]->getName() << "!\n";
        delete this->party[i];
        this->party[i] = nullptr;
    }
    std::cout << '\n';

    for (int i = 0; i < Trainer::NUM_ITEM_TYPES; ++i) {
        for (int j = 0; j < this->numItems.at(i); ++j) {
            std::cout << "Deleting " << this->items.at(i)[j]->getName() << "!\n";
            delete this->items.at(i)[j];
            this->items.at(i)[j] = nullptr;
        }
    }
}

auto Trainer::partySize() const -> int {
    return this->numPokemon;
}

void Trainer::addPokemon(Pokemon *toAdd) {
    if (this->numPokemon == Trainer::MAX_POKEMON) {
        return;
    }

    this->party.push_back(toAdd);
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
    delete this->party[index];
    this->party[index] = nullptr;

    this->party.erase(this->party.begin() + index);

    --this->numPokemon;
}

void Trainer::clearParty() {
    for (int i = 0; i < this->numPokemon; ++i) {
        delete this->party[i];
        this->party[i] = nullptr;
    }
    this->numPokemon = 0;
}

auto Trainer::getNumItems(const int type) const -> int {
    if (type < 0 or 3 < type) {
        throw std::runtime_error("Out of bounds: getNumItems");
    }
    return this->numItems.at(type);
}

auto Trainer::getItem(const int type, const int item) const -> Item& {
    return *this->items.at(type)[item];
}

void Trainer::addItem(const int type, Item *toAdd) {
    if (type < 0 or 3 < type or this->numItems.at(type) == Trainer::MAX_ITEMS) {
        return;
    }

    this->items.at(type).push_back(toAdd);
    ++this->numItems.at(type);
}

void Trainer::removeItem(const int type, const int index) {
    if (type < 0 or 3 < type) {
        throw std::runtime_error("Out of bounds: removeItem");
    }

    delete this->items.at(type)[index];
    this->items.at(type)[index] = nullptr;

    this->items.at(type).erase(this->items.at(type).begin() + index);

    --this->numItems.at(type);
}

void Trainer::setRestoreItems(const std::initializer_list<Item *> &inventory) {
    for (const auto &item : inventory) {
        if (this->numItems[0] == Trainer::MAX_ITEMS) {
            break;
        }

        this->items[0].push_back(item);
        ++this->numItems[0];
    }
}

void Trainer::setStatusItems(const std::initializer_list<Item *> &inventory) {
    for (const auto &item : inventory) {
        if (this->numItems[1] == Trainer::MAX_ITEMS) {
            break;
        }

        this->items[1].push_back(item);
        ++this->numItems[1];
    }
}

void Trainer::setPokeBalls(const std::initializer_list<Item *> &inventory) {
    for (const auto &item : inventory) {
        if (this->numItems[2] == Trainer::MAX_ITEMS) {
            break;
        }

        this->items[2].push_back(item);
        ++this->numItems[2];
    }
}

void Trainer::setBattleItems(const std::initializer_list<Item *> &inventory) {
    for (const auto &item : inventory) {
        if (this->numItems[3] == Trainer::MAX_ITEMS) {
            break;
        }

        this->items[3].push_back(item);
        ++this->numItems[3];
    }
}

void Trainer::incFaintCount() {
    ++this->numFainted;
}

void Trainer::decFaintCount() {
    --this->numFainted;
}

auto Trainer::getFaintCount() const -> int {
    return this->numFainted;
}

void Trainer::swapPokemon(const int first, const int second) {
    Pokemon *copy = this->party[first];
    this->party[first] = this->party[second];
    this->party[second] = copy;
}

auto Trainer::operator[](const int spot) -> Pokemon&  {
    if (5 < spot or spot < 0) {
        throw std::runtime_error("Index out of bounds");
    }
    return *this->party[spot];
}

auto Trainer::operator[](const int spot) const -> const Pokemon& {
    if (5 < spot or spot < 0) {
        throw std::runtime_error("Index out of bounds");
    }
    return *this->party[spot];
}

Trainer::operator bool() const {
    return this->numPokemon > 0;
}

auto Trainer::canFight() const -> bool {
    return this->numPokemon > 0;
}
