//
// Created by Miles Youngblood on 7/10/2023.
//

#include "Map.h"

void Map::setBorders(const Map * from) {
    // set the top border
    for (int x = 0; x < from->width; ++x) {
        this->layout[x][0] = true;
    }

    // set the inner layer borders
    for (int y = 1; y < from->height; ++y) {
        this->layout[0][y] = true;
        this->layout[this->width - 1][y] = true;
    }

    // set the bottom border
    for (int x = 0; x < from->width; ++x) {
        this->layout[x][this->height - 1] = true;
    }
}

bool Map::isNPCHere(int x, int y) const {
    return std::any_of(this->npcArray.begin(), this->npcArray.end(), [&x, &y](const NPC &npc){ return npc.getX() == x and npc.getY() == y; });
}

Map::Map(const char * name, int width, int height, const std::vector<ExitPoint> &exitPoints) {
    this->width = width;
    this->height = height;

    this->name = name;

    this->layout = std::vector<std::vector<bool>>(this->width, std::vector<bool>(this->height, false));
    this->setBorders(this);

    this->exitPoints = exitPoints;
    for (ExitPoint &exitPoint : this->exitPoints) {
        this->layout[exitPoint.x][exitPoint.y] = false;
    }
}

Map::Map(const char * name, int width, int height, const std::vector<NPC> &npcArray, const std::vector<ExitPoint> &exitPoints) : Map(name, width, height, exitPoints){
    this->npcArray = npcArray;
}

Map::Map(const Map &toCopy) {
    this->width = toCopy.width;
    this->height = toCopy.height;

    this->npcArray = toCopy.npcArray;
    this->exitPoints = toCopy.exitPoints;

    this->layout = toCopy.layout;
    this->setBorders(&toCopy);

    for (ExitPoint &exitPoint : this->exitPoints) {
        this->layout[exitPoint.x][exitPoint.y] = false;
    }
}

Map& Map::operator=(const Map &rhs) {
    if (this != &rhs) {
        this->width = rhs.width;
        this->height = rhs.height;

        this->npcArray = rhs.npcArray;
        this->exitPoints = rhs.exitPoints;

        this->layout = rhs.layout;
        this->setBorders(&rhs);

        for (ExitPoint &exitPoint : this->exitPoints) {
            this->layout[exitPoint.x][exitPoint.y] = false;
        }
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

std::pair<std::pair<int, int>, int> Map::isExitPointHere(int x, int y) const {
    for (const ExitPoint &exitPoint : this->exitPoints) {
        if (exitPoint.x == x and exitPoint.y == y) {
            return std::make_pair(std::make_pair(exitPoint.newX, exitPoint.newY), exitPoint.newMap);
        }
    }
    return std::make_pair(std::make_pair(0, 0), -1);
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
    std::cout << "Press ESC to quit\n";

    for (int y = 0; y < this->height; ++y) {
        for (int x = 0; x < this->width; ++x) {
            // if an obstruction is in this spot
            if (this->layout[x][y]) {
                std::cout << 'X';
                continue;
            }
            // if the player is currently at these coordinates
            else if (x == trainer.getX() and y == trainer.getY()) {
                // change color of the text to green
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
                std::cout << trainer.getModel();

                // change color of the text back to white
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
                continue;
            }
            bool found = false;      // necessary because an NPC might not be found

            // if the npc is currently at these coordinates
            for (const NPC &npc : this->npcArray) {
                if (x == npc.getX() and y == npc.getY()) {
                    // change color of the text to red
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
                    std::cout << npc.getModel();

                    // change color of the text back to white
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
                    found = true;
                    break;
                }
            }
            // empty space if all else is false
            if (not this->layout[x][y] and not found) {
                std::cout << ' ';
            }
        }
        std::cout << '\n';
    }
    std::cout << this->name;
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