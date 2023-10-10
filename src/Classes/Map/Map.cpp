//
// Created by Miles Youngblood on 7/10/2023.
//

#include "Map.h"

SDL_Renderer *Map::renderer = nullptr;
SDL_Texture *Map::free = nullptr;
SDL_Texture *Map::obstruction = nullptr;
SDL_Texture *Map::grass = nullptr;
SDL_Texture *Map::tallGrass = nullptr;
SDL_Texture *Map::water = nullptr;

// places obstructions along the rim of the map
void Map::setBorders(const Map * from) {
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

Map::Map(const char *name, int width, int height, const std::vector<ExitPoint> &exitPoints, SDL_Renderer *r) : dest() {
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

    this->dest.w = TILE_SIZE;
    this->dest.h = TILE_SIZE;

    this->dest.x = this->dest.y = 0;

    Map::renderer = r;
    const char *obstructionPath = desktop ?
            R"(C:\Users\Miles\Documents\GitHub\PokemonBattle\pokeball.png)" :
            R"(C:\Users\Miles Youngblood\OneDrive\Documents\GitHub\PokemonBattle\pokeball.png)";

    Map::obstruction = TextureManager::LoadTexture(obstructionPath, Map::renderer);
    const char *grassPath = desktop ?
            R"(C:\Users\Miles\Documents\GitHub\PokemonBattle\grass.png)" :
            R"(C:\Users\Miles Youngblood\OneDrive\Documents\GitHub\PokemonBattle\grass.png)";

    Map::grass = TextureManager::LoadTexture(grassPath, Map::renderer);
}

Map::Map(const char *name, int width, int height, const std::initializer_list<Trainer*> &trainerList, const std::vector<ExitPoint> &exitPoints, SDL_Renderer *r)
    : Map(name, width, height, exitPoints, r) {
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
int Map::numNPCs() {
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

// 242 = green, 244 = red, 240 = black

// prints the map and everything in it
void Map::print(const Trainer *player) const {
    system("cls");

    for (int y = 0; y < this->height; ++y) {
        for (int x = 0; x < this->width; ++x) {
            // if an obstruction is in this spot
            if (this->layout[x][y].getID()) {
                std::cout << 'X';
                continue;
            }
            // if the player is currently at these coordinates
            else if (x == player->getX() and y == player->getY()) {
                // change color of the text to green
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
                std::cout << player->getModel();

                // change color of the text back to white
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
                continue;
            }
            bool found = false;      // necessary because an NPC might not be found

            // if the npc is currently at these coordinates
            for (const Trainer *npc : this->trainers) {
                if (x == npc->getX() and y == npc->getY()) {
                    // change color of the text to red
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
                    std::cout << npc->getModel();

                    // change color of the text back to white
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
                    found = true;
                    break;
                }
            }
            // empty space if all else is false
            if (not this->layout[x][y].getID() and not found) {
                std::cout << ' ';
            }
        }
        std::cout << '\n';
    }
    std::cout << this->name;
}

void Map::UpdateMap(int newCoord, int flag) {
    for (int row = 0; row < this->width; ++row) {
        for (int column = 0; column < this->height; ++column) {
            const int x = this->layout[row][column].getX();
            const int y = this->layout[row][column].getY();

            switch (flag) {
                case 1:
                    this->layout[row][column].update(x, y + newCoord);
                    break;
                case 2:
                    this->layout[row][column].update(x, y - newCoord);
                    break;
                case 3:
                    this->layout[row][column].update(x + newCoord, y);
                    break;
                case 4:
                    this->layout[row][column].update(x - newCoord, y);
                    break;
                default:
                    return;
            }
        }
    }

    for (Trainer *&trainer : this->trainers) {
        switch (flag) {
            case 1:
                trainer->shiftDownOnMap(newCoord);
                break;
            case 2:
                trainer->shiftUpOnMap(newCoord);
                break;
            case 3:
                trainer->shiftRightOnMap(newCoord);
                break;
            case 4:
                trainer->shiftLeftOnMap(newCoord);
                break;
            default:
                return;
        }
    }
}

void Map::DrawMap() {
    for (int row = 0; row < this->width; ++row) {
        for (int column = 0; column < this->height; ++column) {
            this->dest.x = this->layout[row][column].getX();
            this->dest.y = this->layout[row][column].getY();

            switch (this->layout[row][column].getID()) {
                case TileID::FREE:
                    TextureManager::Draw(Map::renderer, Map::free, this->dest);
                    break;

                case TileID::OBSTRUCTION:
                    TextureManager::Draw(Map::renderer, Map::obstruction, this->dest);
                    break;

                default:
                    TextureManager::Draw(Map::renderer, Map::grass, this->dest);
                    break;
            }
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// moves the Trainer to the player
void Trainer::moveToPlayer(const Map &map, const Trainer *player) {
    if (this->hasVisionOf(player)) {
        if (this->isFacingNorth()) {
            while (not this->isNextTo(player)) {
                this->moveNorth();
                std::this_thread::sleep_for(std::chrono::milliseconds(250));
                map.print(player);
            }
        }
        else if (this->isFacingEast()) {
            while (not this->isNextTo(player)) {
                this->moveEast();
                std::this_thread::sleep_for(std::chrono::milliseconds(250));
                map.print(player);
            }
        }
        else if (this->isFacingSouth()) {
            while (not this->isNextTo(player)) {
                this->moveSouth();
                std::this_thread::sleep_for(std::chrono::milliseconds(250));
                map.print(player);
            }
        }
        else if (this->isFacingWest()) {
            while (not this->isNextTo(player)) {
                this->moveWest();
                std::this_thread::sleep_for(std::chrono::milliseconds(250));
                map.print(player);
            }
        }
    }
}
