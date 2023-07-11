//
// Created by Miles Youngblood on 7/10/2023.
//

#include "Map.h"

void Map::createMap(const Map * from) {
    this->layout = new bool * [from->yAxisLength];
    for (int y = 0; y < from->yAxisLength; ++y) {
        this->layout[y] = new bool[from->xAxisLength];

        // sets all values of the map to false initially
        for (int x = 0; x < from->xAxisLength; ++x) {
            this->layout[y][x] = false;
        }
    }
}

void Map::deleteMap() {
    for (int i = 0; i < this->yAxisLength; ++i) {
        delete [] this->layout[i];
    }
    delete [] this->layout;
}

Map::Map(int x, int y) : xAxisLength(x), yAxisLength(y) {
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

void Map::print(const Trainer &trainer, const std::vector<NPC> &npcArray) const {
    system("cls");

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
                std::cout << trainer.getModel();
                continue;
            }
            bool skip = false;
            // if the npc is currently at these coordinates
            for (const auto &npc: npcArray) {
                if (x == npc.getX() and y == npc.getY()) {
                    std::cout << npc.getModel();
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

bool NPC::check(const Map &map, Trainer &trainer, std::vector<NPC> &npcArray) {
    if (this->isInRange(trainer) and not this->isDefeated()) {
        if (this->isFacingNorth()) {
            while (this->y != trainer.getY() + 1) {
                this->move(directions::NORTH);
                Sleep(250);
                map.print(trainer, npcArray);
            }
            trainer.changeDirection(directions::SOUTH);
            map.print(trainer, npcArray);
        }
        else if (this->isFacingEast()) {
            while (this->x != trainer.getX() - 1) {
                this->move(directions::EAST);
                Sleep(250);
                map.print(trainer, npcArray);
            }
            trainer.changeDirection(directions::WEST);
            map.print(trainer, npcArray);
        }
        else if (this->isFacingSouth()) {
            while (this->y != trainer.getY() - 1) {
                this->move(directions::SOUTH);
                Sleep(250);
                map.print(trainer, npcArray);
            }
            trainer.changeDirection(directions::NORTH);
            map.print(trainer, npcArray);
        }
        else if (this->isFacingWest()) {
            while (this->x != trainer.getX() + 1) {
                this->move(directions::WEST);
                Sleep(250);
                map.print(trainer, npcArray);
            }
            trainer.changeDirection(directions::EAST);
            map.print(trainer, npcArray);
        }

        return true;
    }
    else {
        return false;
    }
}