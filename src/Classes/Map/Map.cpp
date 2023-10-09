//
// Created by Miles Youngblood on 7/10/2023.
//

#include "Map.h"

//SDL_Renderer *Map::renderer = nullptr;
//SDL_Texture *Map::free = nullptr;
//SDL_Texture *Map::obstruction = nullptr;
//SDL_Texture *Map::grass = nullptr;
SDL_Texture *Map::tallGrass = nullptr;
SDL_Texture *Map::water = nullptr;

// places obstructions along the rim of the map
void Map::setBorders(const Map * from) {
    // set the top border
    for (int x = 0; x < from->width; ++x) {
        this->layout[x][0] = Map::Tile::OBSTRUCTION;
    }

    // set the inner layer borders
    for (int y = 1; y < from->height; ++y) {
        this->layout[0][y] = Map::Tile::OBSTRUCTION;
        this->layout[this->width - 1][y] = Map::Tile::OBSTRUCTION;
    }

    // set the bottom border
    for (int x = 0; x < from->width; ++x) {
        this->layout[x][this->height - 1] = Map::Tile::OBSTRUCTION;
    }
}

bool Map::isTrainerHere(int x, int y) const {
    return std::any_of(this->trainers.begin(), this->trainers.end(), [&x, &y](const Trainer *npc){ return npc->getX() == x and npc->getY() == y; });
}

Map::Map(const char *name, int width, int height, const std::vector<ExitPoint> &exitPoints, SDL_Renderer *r) : src(), dest() {
    this->width = width;
    this->height = height;

    this->name = name;

    this->layout = std::vector<std::vector<Tile>>(this->width, std::vector<Tile>(this->height, Map::Tile::FREE));
    this->setBorders(this);

    this->exitPoints = exitPoints;
    for (ExitPoint &exitPoint : this->exitPoints) {
        this->layout[exitPoint.x][exitPoint.y] = Map::Tile::FREE;
    }

    this->src.x = this->src.y = 0;
    this->src.w = this->dest.w = 50;
    this->src.h = this->dest.h = 50;

    this->dest.x = this->dest.y = 0;

    Map::renderer = r;
    this->free = TextureManager::LoadTexture(R"(C:\Users\Miles Youngblood\OneDrive\Documents\GitHub\PokemonBattle\grass.png)", Map::renderer);
    this->obstruction = TextureManager::LoadTexture(R"(C:\Users\Miles Youngblood\OneDrive\Documents\GitHub\PokemonBattle\pokeball.png)", Map::renderer);
    this->grass = nullptr;
}

Map::Map(const char *name, int width, int height, const std::initializer_list<Trainer*> &trainerList, const std::vector<ExitPoint> &exitPoints, SDL_Renderer *r) : Map(name, width, height, exitPoints, r) {
    this->trainers = trainerList;
}

Map::~Map() {
    for (Trainer *trainer : this->trainers) {
        delete trainer;
    }
    SDL_DestroyTexture(this->free);
    SDL_DestroyTexture(this->obstruction);
    SDL_DestroyTexture(this->grass);
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
        return this->layout[x][y] == Map::Tile::OBSTRUCTION;
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
        this->layout[x][y] = Map::Tile::OBSTRUCTION;
    }
}

// 242 = green, 244 = red, 240 = black

// prints the map and everything in it
void Map::print(const Trainer *player) const {
    system("cls");

    for (int y = 0; y < this->height; ++y) {
        for (int x = 0; x < this->width; ++x) {
            // if an obstruction is in this spot
            if (this->layout[x][y]) {
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
            if (not this->layout[x][y] and not found) {
                std::cout << ' ';
            }
        }
        std::cout << '\n';
    }
    std::cout << this->name;
}

void Map::DrawMap() {
    for (int row = 0; row < this->width; ++row) {
        for (int column = 0; column < this->height; ++column) {
            this->dest.x = row * 50;
            this->dest.y = column * 50;

            switch (this->layout[row][column]) {
                case Map::Tile::FREE:
                    TextureManager::Draw(Map::renderer, this->free, this->dest);
                    break;

                case Map::Tile::OBSTRUCTION:
                    TextureManager::Draw(Map::renderer, this->obstruction, this->dest);
                    break;

                default:
                    TextureManager::Draw(Map::renderer, this->grass, this->dest);
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
