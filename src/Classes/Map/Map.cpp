//
// Created by Miles Youngblood on 7/10/2023.
//

#include "Map.h"

void Map::createMap(const Map * from, bool copy) {
    this->layout = new bool * [from->width];
    for (int x = 0; x < from->width; ++x) {
        this->layout[x] = new bool[from->height];

        if (copy) {
            for (int y = 0; y < from->height; ++y) {
                this->layout[x][y] = from->layout[x][y];
            }
        }
        else {
            for (int y = 0; y < from->height; ++y) {
                this->layout[x][y] = false;
            }
        }
    }
}

void Map::deleteMap() {
    for (int x = 0; x < this->width; ++x) {
        delete [] this->layout[x];
    }
    delete [] this->layout;
}

bool Map::isNPCHere(int x, int y) const {
    return std::any_of(this->npcArray.begin(), this->npcArray.end(), [&x, &y](const NPC &npc){ return npc.getX() == x and npc.getY() == y; });
}

Map::Map(int width, int height) {
    this->width = width;
    this->height = height;

    this->layout = nullptr;
    this->createMap(this, false);
}

Map::Map(int width, int height, const std::vector<NPC> &npcArray) : Map(width, height) {
    this->npcArray = npcArray;
}

Map::Map(const Map &toCopy) {
    this->width = toCopy.width;
    this->height = toCopy.height;

    this->npcArray = toCopy.npcArray;

    this->layout = nullptr;
    this->createMap(&toCopy, true);
}

Map::~Map() {
    this->deleteMap();
}

Map& Map::operator=(const Map &rhs) {
    if (this != &rhs) {
        this->width = rhs.width;
        this->height = rhs.height;

        this->npcArray = rhs.npcArray;

        // safe delete the map just in case of reassignment
        this->deleteMap();

        // recreate the map
        this->createMap(&rhs, true);
    }
    return *this;
}

bool Map::getTile(int x, int y) const {
    // out of bounds or an NPC is already in this spot
    if ((x < 0 or this->width - 1 < x) or (y < 0 or this->height - 1 < y) or this->isNPCHere(x, y)) {
        return true;
    }
    else {
        return this->layout[x][y];
    }
}

int Map::numNPCs() {
    return static_cast<int>(this->npcArray.size());
}

NPC& Map::operator[](int index) {
    return this->npcArray[index];
}

void Map::setObstruction(int x, int y) {
    if (not this->isNPCHere(x, y)) {
        this->layout[x][y] = true;
    }
}

// 242 = green, 244 = red, 240 = black
void Map::print(const Trainer &trainer) const {
    system("cls");
    //SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

    std::cout << "Press ESC to quit\n";

    // top border
    std::cout << '+';
    std::cout << std::string(this->width, '-');
    std::cout << "+\n";

    for (int y = 0; y < this->height; ++y) {
        std::cout << '|';
        for (int x = 0; x < this->width; ++x) {
            // if an obstruction is in this spot
            if (this->layout[x][y]) {
                std::cout << 'X';
                continue;
            }
            // if the player is currently at these coordinates
            else if (x == trainer.getX() and y == trainer.getY()) {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
                std::cout << trainer.getModel();
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
                continue;
            }
            bool skip = false;
            // if the npc is currently at these coordinates
            for (const auto &npc : this->npcArray) {
                if (x == npc.getX() and y == npc.getY()) {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
                    std::cout << npc.getModel();
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
                    skip = true;
                }
            }
            // empty space
            if (not this->layout[x][y] and not skip) {
                std::cout << ' ';
            }
        }
        std::cout << "|\n";
    }

    // bottom border
    std::cout << '+';
    std::cout << std::string(this->width, '-');
    std::cout << '+' << std::flush;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// moves the NPC to the player
void NPC::moveToPlayer(const Map &map, const Trainer &trainer) {
    if (this->hasVisionOf(&trainer) and not this->isDefeated()) {
        if (this->isFacingNorth()) {
            while (not this->isNextTo(&trainer)) {
                this->moveNorth();
                Sleep(250);
                map.print(trainer);
            }
        }
        else if (this->isFacingEast()) {
            while (not this->isNextTo(&trainer)) {
                this->moveEast();
                Sleep(250);
                map.print(trainer);
            }
        }
        else if (this->isFacingSouth()) {
            while (not this->isNextTo(&trainer)) {
                this->moveSouth();
                Sleep(250);
                map.print(trainer);
            }
        }
        else if (this->isFacingWest()) {
            while (not this->isNextTo(&trainer)) {
                this->moveWest();
                Sleep(250);
                map.print(trainer);
            }
        }
    }
}