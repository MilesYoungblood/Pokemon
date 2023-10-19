//
// Created by Miles Youngblood on 6/13/2022.
//

#include "Trainer.h"

Trainer::Trainer() : Entity(), party(), items(), numItems() {
    this->dialogue = "";
    this->numFainted = 0;
    this->numPokemon = 0;
}

Trainer::Trainer(const int x, const int y) : Entity(x, y), party(), items(), numItems() {
    this->dialogue = "";
    this->numFainted = 0;
    this->numPokemon = 0;
}

Trainer::Trainer(const std::initializer_list<Pokemon*> &pokemon, const int x, const int y) : Trainer(x, y) {
    for (const auto &p : pokemon) {
        if (this->numPokemon == Trainer::MAX_POKEMON) {
            break;
        }

        this->party[this->numPokemon] = p;
        ++this->numPokemon;
    }
    for (int i = this->numPokemon; i < Trainer::MAX_POKEMON; ++i) {
        this->party[i] = nullptr;
    }
}

Trainer::Trainer(const std::initializer_list<Pokemon *> &pokemon, const int x, const int y, int vision) : Trainer(pokemon, x, y) {
    this->vision = vision;

    //FIXME change these to not be Hilbert
    this->frontModel = TextureManager::LoadTexture(PROJECT_PATH + R"(\sprites\Hilbert_front.png)");
    this->backModel = TextureManager::LoadTexture(PROJECT_PATH + R"(\sprites\Hilbert_back.png)");
    this->leftModel = TextureManager::LoadTexture(PROJECT_PATH + R"(\sprites\Hilbert_left.png)");
    this->rightModel = TextureManager::LoadTexture(PROJECT_PATH + R"(\sprites\Hilbert_right.png)");

    this->currentTexture = this->frontModel;
}

Trainer::~Trainer() {
    std::cout << "Trainer destructor called!\n";
    for (int i = 0; i < this->numPokemon; ++i) {
        std::cout << "\tDeleting " << this->party[i]->getName() << "!\n";
        delete this->party[i];
    }
    std::cout << '\n';

    for (int i = 0; i < Trainer::NUM_ITEM_TYPES; ++i) {
        for (int j = 0; j < this->numItems[i]; ++j) {
            std::cout << "Deleting " << this->items[i][j]->getName() << "!\n";
            delete items[i][j];
        }
    }
}

int Trainer::partySize() const {
    return this->numPokemon;
}

void Trainer::addPokemon(Pokemon *toAdd) {
    if (this->numPokemon == Trainer::MAX_POKEMON) {
        return;
    }

    this->party[this->numPokemon] = toAdd;
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

    // shifts over the Pokémon that were after it
    for (int i = index; i < this->numPokemon; ++i) {
        this->party[i] = this->party[i + 1];
    }

    --this->numPokemon;
}

void Trainer::clearParty() {
    for (int i = 0; i < this->numPokemon; ++i) {
        delete this->party[i];
    }
    this->numPokemon = 0;
}

int Trainer::getNumItems(const int type) const {
    if (type < 0 or 3 < type) {
        throw std::runtime_error("Out of bounds: getNumItems");
    }
    return this->numItems[type];
}

Item& Trainer::getItem(const int type, const int item) const {
    return *this->items[type][item];
}

void Trainer::addItem(const int type, Item *toAdd) {
    if (type < 0 or 3 < type or this->numItems[type] == Trainer::MAX_ITEMS) {
        return;
    }

    this->items[type][this->numItems[type]] = toAdd;
    ++this->numItems[type];
}

void Trainer::removeItem(const int type, const int index) {
    if (type < 0 or 3 < type) {
        throw std::runtime_error("Out of bounds: removeItem");
    }

    delete this->items[type][index];

    for (int i = index; i < this->numItems[type]; ++i) {
        this->items[type][i] = this->items[type][i + 1];
    }

    --this->numItems[type];
}

void Trainer::setRestoreItems(const std::vector<Item *> &inventory) {
    for (int i = 0; i < inventory.size(); ++i) {
        if (this->numItems[0] == Trainer::MAX_ITEMS) {
            break;
        }

        this->items[0][i] = inventory[i];
        ++this->numItems[0];
    }
}
void Trainer::setStatusItems(const std::vector<Item *> &inventory) {
    for (int i = 0; i < inventory.size(); ++i) {
        if (this->numItems[1] == Trainer::MAX_ITEMS) {
            break;
        }

        this->items[1][i] = inventory[i];
        ++this->numItems[1];
    }
}
void Trainer::setPokeBalls(const std::vector<Item *> &inventory) {
    for (int i = 0; i < inventory.size(); ++i) {
        if (this->numItems[2] == Trainer::MAX_ITEMS) {
            break;
        }

        this->items[2][i] = inventory[i];
        ++this->numItems[2];
    }
}
void Trainer::setBattleItems(const std::vector<Item *> &inventory) {
    for (int i = 0; i < inventory.size(); ++i) {
        if (this->numItems[3] == Trainer::MAX_ITEMS) {
            break;
        }

        this->items[3][i] = inventory[i];
        ++this->numItems[3];
    }
}

void Trainer::incFaintCount() {
    ++this->numFainted;
}

void Trainer::decFaintCount() {
    --this->numFainted;
}

void Trainer::swapPokemon(const int first, const int second) {
    Pokemon *copy = this->party[first];
    this->party[first] = this->party[second];
    this->party[second] = copy;
}

Pokemon& Trainer::operator[](const int spot)  {
    if (5 < spot or spot < 0)
        throw std::runtime_error("Index out of bounds");
    return *this->party[spot];
}

const Pokemon& Trainer::operator[](const int spot) const {
    if (5 < spot or spot < 0)
        throw std::runtime_error("Index out of bounds");
    return *this->party[spot];
}

Trainer::operator bool() const {
    return this->numPokemon > 0;
}

bool Trainer::canFight() const {
    return this->numPokemon > 0;
}
