//
// Created by Miles on 10/2/2023.
//

#include "Game.h"
#include "../../Data/Data.h"

const std::string PATH = std::filesystem::current_path().parent_path().generic_string();

constexpr static int WINDOW_HEIGHT = TILE_SIZE * 7;     // height of the window
constexpr static int WINDOW_WIDTH = TILE_SIZE * 9;      // width of the window
constexpr static int SCROLL_SPEED = TILE_SIZE / 10;     // scroll speed

static SDL_Window *window = SDL_CreateWindow("Pokémon", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
static SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
static SDL_Event event;
static Mix_Chunk *music = nullptr;

__attribute__((unused)) static TextureManager r(renderer);

static bool isRunning = true;                           // determines whether the game is running

static bool up = false;
static bool down = false;
static bool left = false;
static bool right = false;

static bool keepMovingUp = false;
static bool keepMovingDown = false;
static bool keepMovingLeft = false;
static bool keepMovingRight = false;

static int walkCounter = 0;                             // measures how many screen pixels an entity has moved

Player *player = nullptr;

Trainer *Joey = new Trainer({
    new Pikachu({ new Thunder, new QuickAttack, new IronTail, new VoltTackle }),
    new Lucario({ new AuraSphere, new FlashCannon, new DragonPulse, new DarkPulse })
}, 7, 6, 3);

Trainer *Red = new Trainer({
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
    if (SDL_InitSubSystem(SDL_INIT_EVERYTHING) == 0) {
        std::cout << "Subsystems initialized!\n";
    }
    else {
        std::cerr << "Error initializing subsystems " << SDL_GetError() << '\n';
        exit(1);
    }

    if (window) {
        std::cout << "Window created!\n";
    }
    else {
        std::cerr << "Error creating window " << SDL_GetError();
        SDL_Quit();
        exit(1);
    }

    if (renderer) {
        std::cout << "Renderer created!\n";
    }
    else {
        std::cerr << "Error creating renderer " << SDL_GetError() << '\n';
        SDL_DestroyWindow(window);
        SDL_Quit();
        exit(1);
    }

    SDL_Surface *surface = IMG_Load((PATH + R"(\sprites\pokeball.png)").c_str());
    if (not surface) {
        std::cerr << "Error creating surface: " << SDL_GetError();
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        exit(1);
    }

    SDL_SetWindowIcon(window, surface);
    SDL_FreeSurface(surface);

    if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096) == 0) {
        std::cout << "Default audio device opened!\n";
    }
    else {
        std::cerr << "Could not open the default audio device: " << SDL_GetError();
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        exit(1);
    }

    music = Mix_LoadWAV((PATH + R"(\music\TrainerBattleMusic.wav)").c_str());
    if (not music) {
        std::cerr << "Could not play sound " << SDL_GetError();
        Mix_CloseAudio();
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        exit(1);
    }
    Mix_PlayChannel(-1, music, -1);

    player = Player::getPlayer();
    std::cout << "Player created!\n\n";

    void (*instructions)(int, int) = [](int d, int f) -> void { maps[currentMapIndex]->updateMap(d, f); };
    Camera::lockOnPlayer(player, (WINDOW_WIDTH - TILE_SIZE) / 2, (WINDOW_HEIGHT - TILE_SIZE) / 2, instructions);
}

Game::~Game() {
    Mix_FreeChunk(music);
    Mix_CloseAudio();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    std::cout << "Game cleaned!\n";

    Player::destroyPlayer();
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
                        right = true;
                        keepMovingRight = true;
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
        maps[currentMapIndex]->updateMap(SCROLL_SPEED, 1);
        walkCounter += SCROLL_SPEED;

        if (walkCounter % TILE_SIZE == 0) {
            player->moveNorth();
        }
    }
    else if (not maps[currentMapIndex]->isObstructionHere(playerX, playerY + 1) and (keepMovingDown or down)) {
        Camera::shiftUp(SCROLL_SPEED);
        maps[currentMapIndex]->updateMap(SCROLL_SPEED, 2);
        walkCounter += SCROLL_SPEED;

        if (walkCounter % TILE_SIZE == 0) {
            player->moveSouth();
        }
    }
    else if (not maps[currentMapIndex]->isObstructionHere(playerX - 1, playerY) and (keepMovingLeft or left)) {
        Camera::shiftRight(SCROLL_SPEED);
        maps[currentMapIndex]->updateMap(SCROLL_SPEED, 3);
        walkCounter += SCROLL_SPEED;

        if (walkCounter % TILE_SIZE == 0) {
            player->moveWest();
        }
    }
    else if (not maps[currentMapIndex]->isObstructionHere(playerX + 1, playerY) and (keepMovingRight or right)) {
        Camera::shiftLeft(SCROLL_SPEED);
        maps[currentMapIndex]->updateMap(SCROLL_SPEED, 4);
        walkCounter += SCROLL_SPEED;

        if (walkCounter % TILE_SIZE == 0) {
            player->moveEast();
        }
    }

    // if your sprite has reached a tile, and you are not inputting any directions
    if (walkCounter % TILE_SIZE == 0 and not (up or down or left or right)) {
        keepMovingUp = false;
        keepMovingDown = false;
        keepMovingLeft = false;
        keepMovingRight = false;
        walkCounter = 0;
    }
}

void Game::render() {
    SDL_RenderClear(renderer);
    (*maps)[currentMapIndex].renderMap();

    for (int i = 0; i < maps[currentMapIndex]->numNPCs(); ++i) {
        // prevents rendering trainers that aren't onscreen
        if (Camera::isInView((*maps)[currentMapIndex][i].getRect())) {
            (*maps)[currentMapIndex][i].render();
        }
    }
    player->render();

    SDL_RenderPresent(renderer);
}

void Game::saveData() {
    std::cout << "Saving please wait...";

    std::ofstream saveFile(PATH + R"(\src\Data\SaveData.txt)");
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
    std::ifstream saveFile(PATH + R"(\src\Data\SaveData.txt)");

    void (*loadDirection)(Entity *, int) = [](Entity *entity, int direction) -> void {
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
    std::filesystem::remove(PATH + R"(\src\Data\SaveData.txt)");
}

Game::operator bool() const {
    return isRunning;
}
