//
// Created by Miles Youngblood on 7/10/2023.
//

#include "Map.h"

SDL_Texture *Map::free = nullptr;
SDL_Texture *Map::obstruction = nullptr;
SDL_Texture *Map::grass = nullptr;
SDL_Texture *Map::tallGrass = nullptr;
SDL_Texture *Map::water = nullptr;

bool Map::isTrainerHere(const int x, const int y) const {
    for (int i = 0; i < this->trainers.size(); ++i) {
        if (trainers[i]->getX() == x and trainers[i]->getY() == y) {
            return true;
        }
    }
    return false;
}

Map::Map(const char *name, const char *music, int width, int height) : name(name), music(music), width(width), height(height) {
    // initialize the layout with grass
    this->layout.resize(this->width);
    for (int i = 0; i < this->width; ++i) {
        this->layout[i].resize(this->height);

        for (int j = 0; j < this->height; ++j) {
            this->layout[i][j] = { Map::TileID::GRASS, i * TILE_SIZE, j * TILE_SIZE, TILE_SIZE, TILE_SIZE };
        }
    }

    // set the top border
    for (int x = 0; x < this->width; ++x) {
        this->layout[x][0].id = Map::TileID::OBSTRUCTION;
    }

    // set the inner layer borders
    for (int y = 1; y < this->height; ++y) {
        this->layout[0][y].id = Map::TileID::OBSTRUCTION;
        this->layout[this->width - 1][y].id = Map::TileID::OBSTRUCTION;
    }

    // set the bottom border
    for (int x = 0; x < this->width; ++x) {
        this->layout[x][this->height - 1].id = Map::TileID::OBSTRUCTION;
    }

    Map::obstruction = TextureManager::LoadTexture(PROJECT_PATH + R"(\sprites\pokeball.png)");
    Map::grass = TextureManager::LoadTexture(PROJECT_PATH + R"(\sprites\grass.png)");
}

Map::Map(const char *name, const char *music, const int width, const int height, const std::vector<Map::ExitPoint> &exitPoints) : name(name), music(music), width(width), height(height), exitPoints(exitPoints) {
    // initialize the layout with grass
    this->layout.resize(this->width);
    for (int i = 0; i < this->width; ++i) {
        this->layout[i].resize(this->height);

        for (int j = 0; j < this->height; ++j) {
            this->layout[i][j] = { Map::TileID::GRASS, i * TILE_SIZE, j * TILE_SIZE, TILE_SIZE, TILE_SIZE };
        }
    }

    // set the top border
    for (int x = 0; x < this->width; ++x) {
        this->layout[x][0].id = Map::TileID::OBSTRUCTION;
    }

    // set the inner layer borders
    for (int y = 1; y < this->height; ++y) {
        this->layout[0][y].id = Map::TileID::OBSTRUCTION;
        this->layout[this->width - 1][y].id = Map::TileID::OBSTRUCTION;
    }

    // set the bottom border
    for (int x = 0; x < this->width; ++x) {
        this->layout[x][this->height - 1].id = Map::TileID::OBSTRUCTION;
    }

    // set any exit points
    for (const ExitPoint &exitPoint : this->exitPoints) {
        this->layout[exitPoint.x][exitPoint.y].id = Map::TileID::GRASS;
    }

    Map::obstruction = TextureManager::LoadTexture(PROJECT_PATH + R"(\sprites\pokeball.png)");
    Map::grass = TextureManager::LoadTexture(PROJECT_PATH + R"(\sprites\grass.png)");
}

//FIXME try not to copy vector parameter
Map::Map(const char *name, const char *music, const int width, const int height, const std::vector<Map::ExitPoint> &exitPoints, std::vector<std::unique_ptr<Trainer>> &trainerList)
    : Map(name, music, width, height, exitPoints) {
    this->trainers.resize(trainerList.size());
    for (int i = 0; i < this->trainers.size(); ++i) {
        this->trainers[i] = std::move(trainerList[i]);
    }
}

Map::~Map() {
    SDL_DestroyTexture(Map::free);
    SDL_DestroyTexture(Map::obstruction);
    SDL_DestroyTexture(Map::grass);
    SDL_DestroyTexture(Map::tallGrass);
    SDL_DestroyTexture(Map::water);
}

// returns true if an obstruction is at the passed coordinates
bool Map::isObstructionHere(const int x, const int y) const {
    // out of bounds or an NPC is already in this spot
    if ((x < 0 or this->width - 1 < x) or (y < 0 or this->height - 1 < y) or this->isTrainerHere(x, y)) {
        return true;
    }

    return this->layout[x][y].id == Map::TileID::OBSTRUCTION;
}

void Map::addExitPoint(const ExitPoint &exitPoint) {
    this->exitPoints.push_back(exitPoint);
    this->layout[exitPoint.x][exitPoint.y].id = Map::TileID::GRASS;
}

// returns an array with the new x and y coordinates and the new map respectively,
// if no exit point is here, returns filler coordinates with the third element being -1
std::array<int, 3> Map::isExitPointHere(const int x, const int y) const {
    for (const ExitPoint &exitPoint : this->exitPoints) {
        if (exitPoint.x == x and exitPoint.y == y) {
            return { exitPoint.newX, exitPoint.newY, exitPoint.newMap };
        }
    }
    return { 0, 0, -1 };
}

void Map::addTrainer(std::unique_ptr<Trainer> toAdd) {
    this->trainers.push_back(std::move(toAdd));
}

// returns the number of NPCs
int Map::numTrainers() const {
    return static_cast<int>(this->trainers.size());
}

// returns the trainer at the passed index
Trainer & Map::operator[](const int index) {
    return *this->trainers[index];
}

const Trainer & Map::operator[](const int index) const {
    return *this->trainers[index];
}

const char * Map::getMusic() const {
    return this->music;
}

// places an obstruction at the passed coordinates
void Map::setObstruction(const int x, const int y) {
    if (not this->isTrainerHere(x, y)) {
        this->layout[x][y].id = Map::TileID::OBSTRUCTION;
    }
}

// shift the map and its trainers, according to a passed in flag
void Map::updateMap(const Direction direction, const int distance) {
    for (int row = 0; row < this->width; ++row) {
        for (int column = 0; column < this->height; ++column) {
            switch (direction) {
                case Direction::DOWN:
                    this->layout[row][column].dest.y += distance;
                    break;
                case Direction::UP:
                    this->layout[row][column].dest.y -= distance;
                    break;
                case Direction::RIGHT:
                    this->layout[row][column].dest.x += distance;
                    break;
                case Direction::LEFT:
                    this->layout[row][column].dest.x -= distance;
                    break;
                default:
                    return;
            }
        }
    }

    for (const std::unique_ptr<Trainer> &trainer : this->trainers) {
        switch (direction) {
            case Direction::DOWN:
                trainer->shiftDownOnMap(distance);
                break;
            case Direction::UP:
                trainer->shiftUpOnMap(distance);
                break;
            case Direction::RIGHT:
                trainer->shiftRightOnMap(distance);
                break;
            case Direction::LEFT:
                trainer->shiftLeftOnMap(distance);
                break;
            default:
                return;
        }
    }
}

void Map::renderMap() {
    SDL_Rect sdlRect;
    for (int row = 0; row < this->width; ++row) {
        for (int column = 0; column < this->height; ++column) {
            sdlRect = this->layout[row][column].dest;
            // prevents rendering tiles that aren't onscreen
            if (Camera::isInView(sdlRect) != 0U) {
                switch (this->layout[row][column].id) {
                    case Map::TileID::FREE:
                        TextureManager::Draw(Map::free, sdlRect);
                        break;

                    case Map::TileID::OBSTRUCTION:
                        TextureManager::Draw(Map::obstruction, sdlRect);
                        break;

                    default:
                        TextureManager::Draw(Map::grass, sdlRect);
                        break;
                }
            }
        }
    }

    for (const std::unique_ptr<Trainer> &trainer : this->trainers) {
        // prevents rendering trainers that aren't onscreen
        if (Camera::isInView(trainer->getRect()) != 0U) {
            trainer->render();
        }
    }
}

// resets the previous map's tile positions
// as well as the trainer's positions
void Map::resetMap() {
    for (int i = 0; i < this->width; ++i) {
        for (int j = 0; j < this->height; ++j) {
            this->layout[i][j] = { this->layout[i][j].id, i * TILE_SIZE, j * TILE_SIZE, TILE_SIZE, TILE_SIZE };
        }
    }

    for (auto &trainer : this->trainers) {
        trainer->resetPos();
    }
}

bool Entity::canMoveForward(const Map *map) const {
    switch (this->currentDirection) {
        case Direction::UP:
            return not map->isObstructionHere(this->x, this->y - 1);
        case Direction::RIGHT:
            return not map->isObstructionHere(this->x + 1, this->y);
        case Direction::DOWN:
            return not map->isObstructionHere(this->x, this->y + 1);
        case Direction::LEFT:
            return not map->isObstructionHere(this->x - 1, this->y);
        default:
            throw std::runtime_error("Unexpected error: function canMoveForward");
    }
}
