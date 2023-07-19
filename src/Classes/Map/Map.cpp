//
// Created by Miles Youngblood on 7/10/2023.
//

#include "Map.h"

void Map::createMap(const Map * from) {
    this->layout = new bool * [from->width];
    for (int x = 0; x < from->width; ++x) {
        this->layout[x] = new bool[from->height];

        // sets all values of the map to false initially
        for (int y = 0; y < from->height; ++y) {
            this->layout[x][y] = false;
        }
    }
}

void Map::deleteMap() {
    for (int x = 0; x < this->width; ++x) {
        delete [] this->layout[x];
    }
    delete [] this->layout;
}

Map::Map(int width, int height) : width(width), height(height) {
    this->layout = nullptr;
    this->createMap(this);
}

Map::Map(const Map &toCopy) {
    this->width = toCopy.width;
    this->height = toCopy.height;

    this->layout = nullptr;
    this->createMap(&toCopy);
}

Map::~Map() {
    this->deleteMap();
}

Map& Map::operator=(const Map &rhs) {
    if (this != &rhs) {
        this->width = rhs.width;
        this->height = rhs.height;

        // safe delete the map just in case of reassignment
        this->deleteMap();

        // recreate the map
        this->createMap(&rhs);
    }
    return *this;
}

int Map::getWidth() const {
    return this->width;
}

int Map::getHeight() const {
    return this->height;
}

bool Map::getTile(int x, int y) const {
    // out of bounds
    if ((x < 0 or this->width - 1 < x) or (y < 0 or this->height - 1 < y)) {
        return true;
    }
    else {
        return this->layout[x][y];
    }
}

void Map::setObstruction(int x, int y) {
    this->layout[x][y] = true;
}

// 242 = green, 244 = red, 240 = black
void Map::print(const Trainer &trainer, const std::vector<NPC> &npcArray) const {
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
            for (const auto &npc: npcArray) {
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

bool * Map::operator[](int index) {
    return this->layout[index];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// moves the NPC to the player
void NPC::moveToPlayer(const Map &map, const Trainer &trainer, const std::vector<NPC> &npcArray) {
    if (this->hasVisionOf(&trainer) and not this->isDefeated()) {
        if (this->isFacingNorth()) {
            while (not this->isNextTo(&trainer)) {
                this->moveNorth();
                Sleep(250);
                map.print(trainer, npcArray);
            }
        }
        else if (this->isFacingEast()) {
            while (not this->isNextTo(&trainer)) {
                this->moveEast();
                Sleep(250);
                map.print(trainer, npcArray);
            }
        }
        else if (this->isFacingSouth()) {
            while (not this->isNextTo(&trainer)) {
                this->moveSouth();
                Sleep(250);
                map.print(trainer, npcArray);
            }
        }
        else if (this->isFacingWest()) {
            while (not this->isNextTo(&trainer)) {
                this->moveWest();
                Sleep(250);
                map.print(trainer, npcArray);
            }
        }
    }
}