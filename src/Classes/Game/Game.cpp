//
// Created by Miles on 10/2/2023.
//

#include "Game.h"


#include "../../Data/Data.h"

Player *player = nullptr;

const static int WINDOW_WIDTH = 750;
const static int WINDOW_HEIGHT = 550;

const static int TILE_SIZE = 50;                    // size a tile occupies
const static int SCROLL_SPEED = TILE_SIZE / 10;     // scroll speed

static SDL_Window *window = SDL_CreateWindow("Pokemon", 0x2FFF0000u, 0x2FFF0000u, WINDOW_WIDTH, WINDOW_HEIGHT, 0);;
static SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);

static bool isRunning = true;
bool desktop = false;

int x_pos = (WINDOW_WIDTH - TILE_SIZE) / 2;
int y_pos = (WINDOW_HEIGHT - TILE_SIZE) / 2;

bool up = false;
bool down = false;
bool left = false;
bool right = false;

bool keepMovingUp = false;
bool keepMovingDown = false;
bool keepMovingLeft = false;
bool keepMovingRight = false;

int counter = 0;
SDL_Rect dest{};
SDL_Texture *txt;
Trainer* Joey = new Trainer({
    new Pikachu({ new Thunder, new QuickAttack, new IronTail, new VoltTackle }),
    new Lucario({ new AuraSphere, new FlashCannon, new DragonPulse, new DarkPulse })
}, 7, 6, 3, renderer);

Trainer* Red = new Trainer({
   new Pikachu(),
   new Venasaur(),
   new Charizard()
}, 2, 4, 3, renderer);

Map Route_1("Route 1", 13, 10, { Joey, Red }, { { 6, 0, MapIDs::ROUTE_2, 10, 18 } }, renderer);

Map Route_2("Route 2", 21, 20, { { 10, 19, MapIDs::ROUTE_1, 6, 1 }, { 0, 10, MapIDs::ROUTE_3, 19, 5 } }, renderer);
Map Route_3("Route 3", 21, 11, { { 20, 5, MapIDs::ROUTE_2, 1, 10 } }, renderer);

Map *maps[3] = { &Route_1, &Route_2, &Route_3 };

int currentMapIndex = 0;
Map *currentMap = maps[currentMapIndex];

Game::Game() {
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        std::cout << "Subsystems initialized!" << std::endl;

        //window = SDL_CreateWindow("Pokemon", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
        if (window) {
            std::cout << "Window created!" << std::endl;
        }

        //renderer = SDL_CreateRenderer(window, -1, 0);
        if (renderer) {
            std::cout << "Renderer created!" << std::endl;
        }
    }
    else {
        isRunning = false;
    }

    const char *logoPath = desktop ?
            R"(C:\Users\Miles\Documents\GitHub\PokemonBattle\pokeball.png)" :
            R"(C:\Users\Miles Youngblood\OneDrive\Documents\GitHub\PokemonBattle\pokeball.png)";

    SDL_Surface *surface = IMG_Load(logoPath);
    if (not surface) {
        std::cerr << "Error creating surface: " << SDL_GetError();
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        Player::destroyPlayer();
        exit(1);
    }

    SDL_SetWindowIcon(window, surface);
    SDL_FreeSurface(surface);

    player = Player::getPlayer(renderer);
    txt = TextureManager::LoadTexture(R"(C:\Users\Miles Youngblood\OneDrive\Documents\GitHub\PokemonBattle\grass.png)", renderer);
}

void Game::handleEvents() {
    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type) {
        case SDL_QUIT:
            isRunning = false;
            break;

        case SDL_KEYDOWN:
            // do not accept keyboard input if your sprite is still moving
            if (keepMovingUp or keepMovingDown or keepMovingLeft or keepMovingRight) {
                return;
            }
            switch (event.key.keysym.scancode) {
                case SDL_SCANCODE_W:
                    up = true;
                    keepMovingUp = true;
                    break;
                case SDL_SCANCODE_A:
                    left = true;
                    keepMovingLeft = true;
                    break;
                case SDL_SCANCODE_S:
                    down = true;
                    keepMovingDown = true;
                    break;
                case SDL_SCANCODE_D:
                    keepMovingRight = true;
                    right = true;
                    break;
                default:
                    break;
            }
            break;

        case SDL_KEYUP:
            switch (event.key.keysym.scancode) {
                case SDL_SCANCODE_W:
                    up = false;
                    break;
                case SDL_SCANCODE_A:
                    left = false;
                    break;
                case SDL_SCANCODE_S:
                    down = false;
                    break;
                case SDL_SCANCODE_D:
                    right = false;
                    break;
                default:
                    break;
            }
            break;

        default:
            break;
    }
}

void Game::update() {
    if (up or keepMovingUp) {
        y_pos -= SCROLL_SPEED;
        counter += SCROLL_SPEED;
    }
    else if (down or keepMovingDown) {
        y_pos += SCROLL_SPEED;
        counter += SCROLL_SPEED;
    }
    else if (left or keepMovingLeft) {
        x_pos -= SCROLL_SPEED;
        counter += SCROLL_SPEED;
    }
    else if (right or keepMovingRight) {
        x_pos += SCROLL_SPEED;
        counter += SCROLL_SPEED;
    }

    // if your sprite is centered on a tile
    if (counter % TILE_SIZE == 0) {
        // update player coordinates
        player->setCoordinates(x_pos / TILE_SIZE, y_pos / TILE_SIZE);

        // if you are not inputting any directions
        if (not (up or down or left or right)) {
            keepMovingUp = false;
            keepMovingDown = false;
            keepMovingLeft = false;
            keepMovingRight = false;
            counter = 0;
        }
    }

    dest.x = 200;
    dest.y = 100;
    dest.h = 50;
    dest.h = 50;

    player->update(x_pos, y_pos);
    for (int i = 0; i < maps[currentMapIndex]->numNPCs(); ++i) {
        (*maps)[currentMapIndex][i].update((*maps)[currentMapIndex][i].getX() * 50, (*maps)[currentMapIndex][i].getY() * 50);
    }
}

void Game::render() {
    SDL_RenderClear(renderer);
    //(*maps)[currentMapIndex].DrawMap();

    SDL_RenderCopy(renderer, txt, nullptr, &dest);

    player->render();
    for (int i = 0; i < maps[currentMapIndex]->numNPCs(); ++i) {
        (*maps)[currentMapIndex][i].render();
    }

    SDL_RenderPresent(renderer);
}

void Game::clean() {
    SDL_DestroyTexture(txt);
    Player::destroyPlayer();
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();

    std::cout << "Game cleaned!" << std::endl;
}

void Game::saveData() {
    const char *saveFilePath = desktop ?
                               R"(C:\Users\Miles\Documents\GitHub\PokemonBattle\src\Data\SaveData.txt)" :
                               R"(C:\Users\Miles Youngblood\OneDrive\Documents\GitHub\PokemonBattle\src\Data\SaveData.txt)";
    std::cout << "Saving please wait...";

    std::ofstream saveFile(saveFilePath);
    if (not saveFile) {
        throw std::runtime_error("Could not open file");
    }

    saveFile << currentMapIndex;
    saveFile << '\n' << player->getX() << player->getY() << player->getDirection();
    saveFile << '\n' << player->partySize();

    for (int i = 0; i < player->partySize(); ++i) {
        saveFile << '\n' << (*player)[i].getID() << ' ';

        const int numMoves = (*player)[i].numMoves();
        saveFile << numMoves << ' ';
        for (int j = 0; j < numMoves; ++j) {
            saveFile << (*player)[i][j].getID() << ' ';
        }
    }

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < maps[i]->numNPCs(); ++i) {
            saveFile << '\n' << i << j << (*maps)[i][j].partySize();
            saveFile << (*maps)[i][j].getDirection();
        }
    }

    saveFile.close();
}

void Game::loadData() {

}

void Game::eraseData() {

}

Game::operator bool() const {
    return isRunning;
}
