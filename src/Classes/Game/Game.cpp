//
// Created by Miles on 10/2/2023.
//

#include "Game.h"

#include "../../Data/Data.h"
#include "../../Classes/Camera/Camera.h"

constexpr static int WINDOW_HEIGHT = TILE_SIZE * 7;     // height of the window
constexpr static int WINDOW_WIDTH = TILE_SIZE * 9;      // width of the window
constexpr static int SCROLL_SPEED = TILE_SIZE / 10;     // scroll speed

static SDL_Window *window = SDL_CreateWindow("Pokémon", 0x2FFF0000u, 0x2FFF0000u, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
static SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);

__attribute__((unused)) static TextureManager r(renderer);

static SDL_Event event;

static bool isRunning = true;                           // determines whether the game is running

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
}, 7, 6, 3);

Trainer* Red = new Trainer({
    new Pikachu(),
    new Venasaur(),
    new Charizard()
}, 2, 4, 3);

Map Route_1("Route 1", 13, 10, { Joey, Red }, { { 6, 0, MapIDs::ROUTE_2, 10, 18 } });

Map Route_2("Route 2", 21, 20, { { 10, 19, MapIDs::ROUTE_1, 6, 1 }, { 0, 10, MapIDs::ROUTE_3, 19, 5 } });
Map Route_3("Route 3", 21, 11, { { 20, 5, MapIDs::ROUTE_2, 1, 10 } });

Map *maps[] = { &Route_1, &Route_2, &Route_3 };

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

    player = Player::getPlayer();
    std::cout << "Player created!" << std::endl << std::endl;
    Camera::lockOnPlayer(player, maps[currentMapIndex], (WINDOW_WIDTH - TILE_SIZE) / 2, (WINDOW_HEIGHT - TILE_SIZE) / 2);
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
                break;
            }
            switch (event.key.keysym.scancode) {
                case SDL_SCANCODE_W:
                    if (not player->isFacingNorth()) {
                        player->faceNorth();
                    }
                    else {
                        up = true;
                        keepMovingUp = true;
                    }
                    break;
                case SDL_SCANCODE_A:
                    if (not player->isFacingWest()) {
                        player->faceWest();
                    }
                    else {
                        left = true;
                        keepMovingLeft = true;
                    }
                    break;
                case SDL_SCANCODE_S:
                    if (not player->isFacingSouth()) {
                        player->faceSouth();
                    }
                    else {
                        down = true;
                        keepMovingDown = true;
                    }
                    break;
                case SDL_SCANCODE_D:
                    if (not player->isFacingEast()) {
                        player->faceEast();
                    }
                    else {
                        keepMovingRight = true;
                        right = true;
                    }
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
        Camera::shiftDown(SCROLL_SPEED);
        maps[currentMapIndex]->UpdateMap(SCROLL_SPEED, 1);
        counter += SCROLL_SPEED;

        if (counter % TILE_SIZE == 0) {
            player->moveNorth();
        }
    }
    else if (not maps[currentMapIndex]->isObstructionHere(playerX, playerY + 1) and (keepMovingDown or down)) {
        Camera::shiftUp(SCROLL_SPEED);
        maps[currentMapIndex]->UpdateMap(SCROLL_SPEED, 2);
        counter += SCROLL_SPEED;

        if (counter % TILE_SIZE == 0) {
            player->moveSouth();
        }
    }
    else if (not maps[currentMapIndex]->isObstructionHere(playerX - 1, playerY) and (keepMovingLeft or left)) {
        Camera::shiftRight(SCROLL_SPEED);
        maps[currentMapIndex]->UpdateMap(SCROLL_SPEED, 3);
        counter += SCROLL_SPEED;

        if (counter % TILE_SIZE == 0) {
            player->moveWest();
        }
    }
    else if (not maps[currentMapIndex]->isObstructionHere(playerX + 1, playerY) and (keepMovingRight or right)) {
        Camera::shiftLeft(SCROLL_SPEED);
        maps[currentMapIndex]->UpdateMap(SCROLL_SPEED, 4);
        counter += SCROLL_SPEED;

        if (counter % TILE_SIZE == 0) {
            player->moveEast();
        }
    }

    // if your sprite has reached a tile, and you are not inputting any directions
    if (counter % TILE_SIZE == 0 and not (up or down or left or right)) {
        keepMovingUp = false;
        keepMovingDown = false;
        keepMovingLeft = false;
        keepMovingRight = false;
        counter = 0;
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
}

const char *saveFilePath = desktop ?
                           R"(C:\Users\Miles\Documents\GitHub\PokemonBattle\src\Data\SaveData.txt)" :
                           R"(C:\Users\Miles Youngblood\OneDrive\Documents\GitHub\PokemonBattle\src\Data\SaveData.txt)";

void Game::saveData() {
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

    for (int i = 0; i < sizeof maps / sizeof maps[0]; ++i) {
        for (int j = 0; j < maps[i]->numNPCs(); ++i) {
            saveFile << '\n' << i << j << (*maps)[i][j].partySize();
            saveFile << (*maps)[i][j].getDirection();
        }
    }

    saveFile.close();
}

void Game::loadData() {
    std::ifstream saveFile(saveFilePath);

    auto loadDirection = [](Entity *entity, int direction) {
        switch (direction) {
            case 0:
                entity->faceNorth();
                break;

            case 1:
                entity->faceEast();
                break;

            case 2:
                entity->faceSouth();
                break;

            case 3:
                entity->faceWest();
                break;

            default:
                throw std::runtime_error("Unexpected error: lambda loadDirection");
        }
    };

    if (saveFile) {
        std::string buffer;

        std::getline(saveFile, buffer);
        currentMapIndex = buffer[0] - '0';

        std::getline(saveFile, buffer);
        player->setCoordinates(buffer[0] - '0', buffer[1] - '0');

        loadDirection(player, buffer[2] - '0');

        std::getline(saveFile, buffer);
        const int partySize = buffer[0] - '0';

        //player->clearParty();
        for (int i = 0; i < partySize; ++i) {
            std::getline(saveFile, buffer, ' ');
            player->addPokemon(PokemonFactory::getPokemon(PokemonID(std::stoi(buffer))));

            std::getline(saveFile, buffer, ' ');
            const int numMoves = buffer[0] - '0';

            for (int j = 0; j < numMoves; ++j) {
                std::getline(saveFile, buffer, ' ');
                (*player)[i].addMove(MoveFactory::getMove(MoveID(std::stoi(buffer))));
            }
            std::getline(saveFile, buffer);
        }

        while (std::getline(saveFile, buffer)) {
            const int map = buffer[0] - '0';
            const int trainer = buffer[1] - '0';

            if (buffer[2] == '0') {
                (*maps)[map][trainer].clearParty();
            }
            loadDirection(&(*maps)[map][trainer], buffer[3] - '0');
        }

        saveFile.close();
    }
    else {
        player->addPokemon(new Greninja({ new WaterShuriken, new DarkPulse, new IceBeam, new Extrasensory }));
        player->addPokemon(new Charizard({ new Flamethrower, new AirSlash, new DragonPulse, new SolarBeam }));
        player->addPokemon(new Hydreigon({ new DarkPulse, new DragonPulse, new Flamethrower, new FocusBlast }));
    }
}

void Game::eraseData() {
    std::remove(saveFilePath);
}

Game::operator bool() const {
    return isRunning;
}
