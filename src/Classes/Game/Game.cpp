//
// Created by Miles on 10/2/2023.
//

#include "Game.h"

#include "../../Data/Data.h"

const static int WINDOW_HEIGHT = TILE_SIZE * 7;         // height of the window
const static int WINDOW_WIDTH = TILE_SIZE * 9;          // width of the window
const static int SCROLL_SPEED = TILE_SIZE / 10.0;       // scroll speed

static SDL_Window *window = SDL_CreateWindow("Pokemon", 0x2FFF0000u, 0x2FFF0000u, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
static SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);

static SDL_Event event;

static bool isRunning = true;                           // determines whether the game is running

static int x_pos = (WINDOW_WIDTH - TILE_SIZE) / 2;      // player's x-coordinates on the map
static int y_pos = (WINDOW_HEIGHT - TILE_SIZE) / 2;     // player's y-coordinates on the map

static bool up = false;
static bool down = false;
static bool left = false;
static bool right = false;

static bool keepMovingUp = false;
static bool keepMovingDown = false;
static bool keepMovingLeft = false;
static bool keepMovingRight = false;

static int counter = 0;

Player *player = nullptr;

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

Game::Game() {
    if (not SDL_InitSubSystem(SDL_INIT_EVERYTHING)) {
        std::cout << "Subsystems initialized!" << std::endl;
    }
    else {
        std::cerr << "Error initializing subsystems " << SDL_GetError() << std::endl;
        exit(1);
    }

    if (window) {
        std::cout << "Window created!" << std::endl;
    }
    else {
        std::cerr << "Error creating window " << SDL_GetError();
        SDL_Quit();
        exit(1);
    }

    if (renderer) {
        std::cout << "Renderer created!" << std::endl;
    }
    else {
        std::cerr << "Error creating renderer " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        exit(1);
    }

    const char *iconPath = desktop ?
            R"(C:\Users\Miles\Documents\GitHub\PokemonBattle\pokeball.png)" :
            R"(C:\Users\Miles Youngblood\OneDrive\Documents\GitHub\PokemonBattle\pokeball.png)";

    SDL_Surface *surface = IMG_Load(iconPath);
    if (not surface) {
        std::cerr << "Error creating surface: " << SDL_GetError();
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        exit(1);
    }

    SDL_SetWindowIcon(window, surface);
    SDL_FreeSurface(surface);

    player = Player::getPlayer(renderer, x_pos, y_pos);
    std::cout << "Player created!" << std::endl;
}

void Game::handleEvents() {
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
    const int playerX = player->getX();
    const int playerY = player->getY();

    if (not maps[currentMapIndex]->isObstructionHere(playerX, playerY - 1) and (keepMovingUp or up)) {
        maps[currentMapIndex]->UpdateMap(SCROLL_SPEED, 1);
        y_pos -= SCROLL_SPEED;
        counter += SCROLL_SPEED;
    }
    else if (not maps[currentMapIndex]->isObstructionHere(playerX, playerY + 1) and (keepMovingDown or down)) {
        maps[currentMapIndex]->UpdateMap(SCROLL_SPEED, 2);
        y_pos += SCROLL_SPEED;
        counter += SCROLL_SPEED;
    }
    else if (not maps[currentMapIndex]->isObstructionHere(playerX - 1, playerY) and (keepMovingLeft or left)) {
        maps[currentMapIndex]->UpdateMap(SCROLL_SPEED, 3);
        x_pos -= SCROLL_SPEED;
        counter += SCROLL_SPEED;
    }
    else if (not maps[currentMapIndex]->isObstructionHere(playerX + 1, playerY) and (keepMovingRight or right)) {
        maps[currentMapIndex]->UpdateMap(SCROLL_SPEED, 4);
        x_pos += SCROLL_SPEED;
        counter += SCROLL_SPEED;
    }

    // if your sprite has reached a tile
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
}

void Game::render() {
    SDL_RenderClear(renderer);
    (*maps)[currentMapIndex].DrawMap();

    for (int i = 0; i < maps[currentMapIndex]->numNPCs(); ++i) {
        (*maps)[currentMapIndex][i].render();
    }
    player->render();

    SDL_RenderPresent(renderer);
}

void Game::clean() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();

    std::cout << "Game cleaned!" << std::endl;

    Player::destroyPlayer();
    std::cout << "Player destroyed!" << std::endl;
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
