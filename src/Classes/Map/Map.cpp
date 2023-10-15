//
// Created by Miles Youngblood on 7/10/2023.
//

#include "Map.h"

SDL_Texture *Map::free = nullptr;
SDL_Texture *Map::obstruction = nullptr;
SDL_Texture *Map::grass = nullptr;
SDL_Texture *Map::tallGrass = nullptr;
SDL_Texture *Map::water = nullptr;

// places obstructions along the rim of the map
void Map::setBorders(const Map *from) {
    // set the top border
    for (int x = 0; x < from->width; ++x) {
        this->layout[x][0].setID(TileID::OBSTRUCTION);
    }

    // set the inner layer borders
    for (int y = 1; y < from->height; ++y) {
        this->layout[0][y].setID(TileID::OBSTRUCTION);
        this->layout[this->width - 1][y].setID(TileID::OBSTRUCTION);
    }

    // set the bottom border
    for (int x = 0; x < from->width; ++x) {
        this->layout[x][this->height - 1].setID(TileID::OBSTRUCTION);
    }
}

bool Map::isTrainerHere(int x, int y) const {
    return std::any_of(this->trainers.begin(), this->trainers.end(), [&x, &y](const Trainer *npc){ return npc->getX() == x and npc->getY() == y; });
}

Map::Map(const char *name, int width, int height, const std::vector<Map::ExitPoint> &exitPoints) {
    this->name = name;

    this->width = width;
    this->height = height;

    this->layout.resize(this->width);
    for (int i = 0; i < this->width; ++i) {
        this->layout[i].resize(this->height);

        for (int j = 0; j < this->height; ++j) {
            this->layout[i][j] = Tile(TileID::GRASS, i * TILE_SIZE, j * TILE_SIZE);
        }
    }
    this->setBorders(this);

    this->exitPoints = exitPoints;
    for (ExitPoint &exitPoint : this->exitPoints) {
        this->layout[exitPoint.x][exitPoint.y].setID(TileID::GRASS);
    }

    Map::obstruction = TextureManager::LoadTexture(PROJECT_PATH + "\\sprites\\pokeball.png");
    Map::grass = TextureManager::LoadTexture(PROJECT_PATH + "\\sprites\\grass.png");
}

Map::Map(const char *name, int width, int height, const std::initializer_list<Trainer*> &trainerList, const std::vector<Map::ExitPoint> &exitPoints)
    : Map(name, width, height, exitPoints) {
    this->trainers = trainerList;
}

Map::~Map() {
    for (Trainer *trainer : this->trainers) {
        delete trainer;
    }

    SDL_DestroyTexture(Map::free);
    SDL_DestroyTexture(Map::obstruction);
    SDL_DestroyTexture(Map::grass);
    SDL_DestroyTexture(Map::tallGrass);
    SDL_DestroyTexture(Map::water);
}

// returns true if an obstruction is at the passed coordinates
bool Map::isObstructionHere(int x, int y) const {
    // out of bounds or an NPC is already in this spot
    if ((x < 0 or this->width - 1 < x) or (y < 0 or this->height - 1 < y) or this->isTrainerHere(x, y)) {
        return true;
    }
    else {
        return this->layout[x][y].getID() == TileID::OBSTRUCTION;
    }
}

// returns an array with the new x and y coordinates and the new map respectively
std::array<int, 3> Map::isExitPointHere(int x, int y) const {
    for (const ExitPoint &exitPoint : this->exitPoints) {
        if (exitPoint.x == x and exitPoint.y == y) {
            return { exitPoint.newX, exitPoint.newY, exitPoint.newMap };
        }
    }
    return { 0, 0, -1 };
}

// returns the number of NPCs
int Map::numTrainers() {
    return static_cast<int>(this->trainers.size());
}

Trainer& Map::operator[](int index) {
    return *this->trainers[index];
}

// places an obstruction at the passed coordinates
void Map::setObstruction(int x, int y) {
    if (not this->isTrainerHere(x, y)) {
        this->layout[x][y].setID(TileID::OBSTRUCTION);
    }
}

void Map::updateMap(int distance, int flag) {
    for (int row = 0; row < this->width; ++row) {
        for (int column = 0; column < this->height; ++column) {
            const int x = this->layout[row][column].getX();
            const int y = this->layout[row][column].getY();

            switch (flag) {
                case 1:
                    this->layout[row][column].update(x, y + distance);
                    break;
                case 2:
                    this->layout[row][column].update(x, y - distance);
                    break;
                case 3:
                    this->layout[row][column].update(x + distance, y);
                    break;
                case 4:
                    this->layout[row][column].update(x - distance, y);
                    break;
                default:
                    return;
            }
        }
    }

    for (Trainer *&trainer : this->trainers) {
        switch (flag) {
            case 1:
                trainer->shiftDownOnMap(distance);
                break;
            case 2:
                trainer->shiftUpOnMap(distance);
                break;
            case 3:
                trainer->shiftRightOnMap(distance);
                break;
            case 4:
                trainer->shiftLeftOnMap(distance);
                break;
            default:
                return;
        }
    }
}

void Map::renderMap() {
    for (int row = 0; row < this->width; ++row) {
        for (int column = 0; column < this->height; ++column) {
            const SDL_Rect *r = this->layout[row][column].getRect();
            // prevents rendering tiles that aren't onscreen
            if (not Camera::isInView(r)) {
                continue;
            }

            switch (this->layout[row][column].getID()) {
                case TileID::FREE:
                    TextureManager::Draw(Map::free, *r);
                    break;

                case TileID::OBSTRUCTION:
                    TextureManager::Draw(Map::obstruction, *r);
                    break;

                default:
                    TextureManager::Draw(Map::grass, *r);
                    break;
            }
        }
    }
}
