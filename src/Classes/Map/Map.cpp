//
// Created by Miles Youngblood on 7/10/2023.
//

#include "Map.h"

void Map::createMap(const Map * from) {
    this->layout = new bool * [from->xAxisLength];
    for (int x = 0; x < from->xAxisLength; ++x) {
        this->layout[x] = new bool[from->yAxisLength];

        // sets all values of the map to false initially
        for (int y = 0; y < from->yAxisLength; ++y) {
            this->layout[x][y] = false;
        }
    }
}

void Map::deleteMap() {
    for (int x = 0; x < this->xAxisLength; ++x) {
        delete [] this->layout[x];
    }
    delete [] this->layout;
}

Map::Map(int xAxisLength, int yAxisLength) : xAxisLength(xAxisLength), yAxisLength(yAxisLength) {
    this->layout = nullptr;
    this->createMap(this);
}

Map::~Map() {
    this->deleteMap();
}

Map& Map::operator=(const Map &rhs) {
    if (this != &rhs) {
        this->xAxisLength = rhs.xAxisLength;
        this->yAxisLength = rhs.yAxisLength;

        // safe delete the map just in case of reassignment
        this->deleteMap();

        // recreate the map
        this->createMap(&rhs);
    }
    return *this;
}

int Map::getXBounds() const {
    return this->xAxisLength;
}

int Map::getYBounds() const {
    return this->yAxisLength;
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
    std::cout << std::string(this->xAxisLength, '-');
    std::cout << "+\n";

    for (int y = 0; y < this->yAxisLength; ++y) {
        std::cout << '|';
        for (int x = 0; x < this->xAxisLength; ++x) {
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
    std::cout << std::string(this->xAxisLength, '-');
    std::cout << '+' << std::flush;
}

bool * Map::operator[](int index) {
    return this->layout[index];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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