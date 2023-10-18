//
// Created by Miles on 10/2/2023.
//

#include "Game.h"
#include "../../Data/Data.h"

const static std::string PATH = std::filesystem::current_path().parent_path().generic_string();

constexpr static int WINDOW_HEIGHT = TILE_SIZE * 7;     // height of the window
constexpr static int WINDOW_WIDTH = TILE_SIZE * 9;      // width of the window
constexpr static int SCROLL_SPEED = TILE_SIZE / 10;     // scroll speed

static SDL_Window *gameWindow = SDL_CreateWindow("Pokémon", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
static SDL_Renderer *gameRenderer = SDL_CreateRenderer(gameWindow, -1, 0);
static SDL_Event event;
static Mix_Chunk *music = nullptr;

__attribute__((unused)) static TextureManager textureManager(gameRenderer);

static bool isRunning = true;                           // determines whether the game is running

static bool canMove = true;                             // determines whether the player can move

static bool moveUp = false;                             // becomes true when the user presses 'w'
static bool moveDown = false;                           // becomes true when the user presses 's'
static bool moveLeft = false;                           // becomes true when the user presses 'a'
static bool moveRight = false;                          // becomes true when the user presses 'd'

static bool keepMovingUp = false;
static bool keepMovingDown = false;
static bool keepMovingLeft = false;
static bool keepMovingRight = false;

static bool interact = false;

static int walkCounter = 0;                             // measures how many screen pixels an entity has moved

static std::vector<int> walkCounters;
static std::vector<bool> lockOn;

static Player *player = nullptr;

static int functionState = 0;                           // denotes which set of functions to use

constexpr static int NUM_STATES = 2;
static std::array<void (*)(), NUM_STATES> handleFunctions = { Game::handleOverworldEvents, Game::handleBattleEvents };
static std::array<void (*)(), NUM_STATES> updateFunctions = { Game::updateOverworld, Game::updateBattle };
static std::array<void (*)(), NUM_STATES> renderFunctions = { Game::renderOverworld, Game::renderBattle };

Game::Game() {
    if (SDL_InitSubSystem(SDL_INIT_EVERYTHING) == 0) {
        std::cout << "Subsystems initialized!\n";
    }
    else {
        std::cerr << "Error initializing subsystems: " << SDL_GetError() << '\n';
        exit(1);
    }

    if (gameWindow) {
        std::cout << "Window created!\n";
    }
    else {
        std::cerr << "Error creating window: " << SDL_GetError() << '\n';
        SDL_Quit();
        exit(1);
    }

    if (gameRenderer) {
        std::cout << "Renderer created!\n";
    }
    else {
        std::cerr << "Error creating renderer: " << SDL_GetError() << '\n';
        SDL_DestroyWindow(gameWindow);
        SDL_Quit();
        exit(1);
    }

    SDL_Surface *pokeball = IMG_Load((PATH + R"(\sprites\pokeball.png)").c_str());
    if (not pokeball) {
        std::cerr << "Error creating surface: " << SDL_GetError() << '\n';
        SDL_DestroyRenderer(gameRenderer);
        SDL_DestroyWindow(gameWindow);
        SDL_Quit();
        exit(1);
    }

    SDL_SetWindowIcon(gameWindow, pokeball);
    SDL_FreeSurface(pokeball);

    if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096) == 0) {
        std::cout << "Default audio device opened!\n";
    }
    else {
        std::cerr << "Could not open the default audio device: " << SDL_GetError() << '\n';
        SDL_DestroyRenderer(gameRenderer);
        SDL_DestroyWindow(gameWindow);
        SDL_Quit();
        exit(1);
    }

    music = Mix_LoadWAV((PATH + R"(\music\TrainerBattleMusic.wav)").c_str());
    if (not music) {
        std::cerr << "Could not play sound: " << SDL_GetError() << '\n';
        Mix_CloseAudio();
        SDL_DestroyRenderer(gameRenderer);
        SDL_DestroyWindow(gameWindow);
        SDL_Quit();
        exit(1);
    }
    Mix_PlayChannel(-1, music, -1);

    player = Player::getPlayer();
    std::cout << "Player created!\n\n";

    void (*instructions)(int, int) = [](int d, int f) -> void { currentMap->updateMap(d, f); };
    Camera::lockOnPlayer(player, (WINDOW_WIDTH - TILE_SIZE) / 2, (WINDOW_HEIGHT - TILE_SIZE) / 2, instructions);

    walkCounters = std::vector<int>(currentMap->numTrainers(), 0);
    lockOn = std::vector<bool>(currentMap->numTrainers(), false);
}

Game::~Game() {
    Mix_FreeChunk(music);
    Mix_CloseAudio();
    SDL_DestroyRenderer(gameRenderer);
    SDL_DestroyWindow(gameWindow);
    SDL_Quit();

    std::cout << "Game cleaned!\n";

    Player::destroyPlayer();
}

void Game::handleEvents() {
    SDL_PollEvent(&event);
    handleFunctions[functionState]();
}

void Game::update() {
    updateFunctions[functionState]();
}

void Game::render() {
    renderFunctions[functionState]();
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

    for (int pokemon = 0; pokemon < player->partySize(); ++pokemon) {
        saveFile << '\n' << (*player)[pokemon].getID() << ' ';

        const int numMoves = (*player)[pokemon].numMoves();
        saveFile << numMoves << ' ';
        for (int move = 0; move < numMoves; ++move) {
            saveFile << (*player)[pokemon][move].getID() << ' ';
        }
    }

    for (int map = 0; map < maps.size(); ++map) {
        for (int trainer = 0; trainer < maps[map]->numTrainers(); ++map) {
            saveFile << '\n' << map << trainer << (*maps[map])[trainer].partySize();
            saveFile << (*maps[map])[trainer].getDirection();
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

        for (int pokemon = 0; pokemon < partySize; ++pokemon) {
            std::getline(saveFile, buffer, ' ');
            player->addPokemon(PokemonFactory::getPokemon(PokemonID(std::stoi(buffer))));

            std::getline(saveFile, buffer, ' ');
            const int numMoves = buffer[0] - '0';

            for (int move = 0; move < numMoves; ++move) {
                std::getline(saveFile, buffer, ' ');
                (*player)[pokemon].addMove(MoveFactory::getMove(MoveID(std::stoi(buffer))));
            }
            std::getline(saveFile, buffer);
        }

        while (std::getline(saveFile, buffer)) {
            const int map = buffer[0] - '0';
            const int trainer = buffer[1] - '0';

            if (buffer[2] == '0') {
                (*maps[map])[trainer].clearParty();
            }
            loadDirection(&(*maps[map])[trainer], buffer[3] - '0');
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

void Game::handleOverworldEvents() {
    switch (event.type) {
        case SDL_QUIT:
            isRunning = false;
            break;

        case SDL_KEYDOWN:
            // FIXME change to account for ENTER key
            // do not accept keyboard input if your sprite is still moving
            if (keepMovingUp or keepMovingDown or keepMovingLeft or keepMovingRight) {
                break;
            }
            switch (event.key.keysym.scancode) {
                case SDL_SCANCODE_W:
                    if (canMove) {
                        if (not player->isFacingNorth()) {
                            player->faceNorth();
                        }
                        else {
                            moveUp = true;
                            keepMovingUp = true;
                        }
                    }
                    break;
                case SDL_SCANCODE_A:
                    if (canMove) {
                        if (not player->isFacingWest()) {
                            player->faceWest();
                        }
                        else {
                            moveLeft = true;
                            keepMovingLeft = true;
                        }
                    }
                    break;
                case SDL_SCANCODE_S:
                    if (canMove) {
                        if (not player->isFacingSouth()) {
                            player->faceSouth();
                        }
                        else {
                            moveDown = true;
                            keepMovingDown = true;
                        }
                    }
                    break;
                case SDL_SCANCODE_D:
                    if (canMove) {
                        if (not player->isFacingEast()) {
                            player->faceEast();
                        }
                        else {
                            moveRight = true;
                            keepMovingRight = true;
                        }
                    }
                    break;
                case SDL_SCANCODE_RETURN:
                    interact = true;
                    break;
                default:
                    break;
            }
            break;

        case SDL_KEYUP:
            switch (event.key.keysym.scancode) {
                case SDL_SCANCODE_W:
                    moveUp = false;
                    break;
                case SDL_SCANCODE_A:
                    moveLeft = false;
                    break;
                case SDL_SCANCODE_S:
                    moveDown = false;
                    break;
                case SDL_SCANCODE_D:
                    moveRight = false;
                    break;
                default:
                    break;
            }
            break;

        default:
            break;
    }
}

void Game::handleBattleEvents() {

}

void Game::updateOverworld() {
    const int playerX = player->getX();     // variable used to reduce the number of function calls
    const int playerY = player->getY();     // variable used to reduce the number of function calls

    const std::array<int, 3> mapData = currentMap->isExitPointHere(playerX, playerY);
    if (mapData[2] != -1) {
        currentMap->resetMap();

        currentMapIndex = mapData[2];
        currentMap = maps[currentMapIndex];

        walkCounters = std::vector<int>(currentMap->numTrainers(), 0);
        lockOn = std::vector<bool>(currentMap->numTrainers(), false);

        // set the player's new coordinates
        // FIXME get to a point where this is uncommented: player->setCoordinates(mapData[0], mapData[1]);
        player->setCoordinates(1, 1);
        void (*instructions)(int, int) = [](int d, int f) -> void { currentMap->updateMap(d, f); };
        Camera::lockOnPlayer(player, (WINDOW_WIDTH - TILE_SIZE) / 2, (WINDOW_HEIGHT - TILE_SIZE) / 2, instructions);
    }
    else if (interact) {
        for (int i = 0; i < currentMap->numTrainers(); ++i) {
            if (player->hasVisionOf(&(*currentMap)[i]) and not (*currentMap)[i].hasVisionOf(player)) {
                (*currentMap)[i].face(player);
                break;
            }
        }
        interact = false;
    }
    else if (not currentMap->isObstructionHere(playerX, playerY - 1) and (keepMovingUp or moveUp)) {
        Camera::shiftDown(SCROLL_SPEED);
        currentMap->updateMap(SCROLL_SPEED, 1);
        walkCounter += SCROLL_SPEED;

        if (walkCounter % TILE_SIZE == 0) {
            player->moveNorth();
        }
    }
    else if (not currentMap->isObstructionHere(playerX, playerY + 1) and (keepMovingDown or moveDown)) {
        Camera::shiftUp(SCROLL_SPEED);
        currentMap->updateMap(SCROLL_SPEED, 2);
        walkCounter += SCROLL_SPEED;

        if (walkCounter % TILE_SIZE == 0) {
            player->moveSouth();
        }
    }
    else if (not currentMap->isObstructionHere(playerX - 1, playerY) and (keepMovingLeft or moveLeft)) {
        Camera::shiftRight(SCROLL_SPEED);
        currentMap->updateMap(SCROLL_SPEED, 3);
        walkCounter += SCROLL_SPEED;

        if (walkCounter % TILE_SIZE == 0) {
            player->moveWest();
        }
    }
    else if (not currentMap->isObstructionHere(playerX + 1, playerY) and (keepMovingRight or moveRight)) {
        Camera::shiftLeft(SCROLL_SPEED);
        currentMap->updateMap(SCROLL_SPEED, 4);
        walkCounter += SCROLL_SPEED;

        if (walkCounter % TILE_SIZE == 0) {
            player->moveEast();
        }
    }

    // if the player's sprite is on a tile...
    if (walkCounter % TILE_SIZE == 0) {
        // resets movement variables if you are not inputting any directions
        if (not (moveUp or moveDown or moveLeft or moveRight)) {
            keepMovingUp = false;
            keepMovingDown = false;
            keepMovingLeft = false;
            keepMovingRight = false;
            walkCounter = 0;
        }

        // checks if the player is in LoS for any trainer
        for (int i = 0; i < currentMap->numTrainers(); ++i) {
            Trainer &trainer = (*currentMap)[i];    // variable used to reduce the number of function calls

            if (trainer.hasVisionOf(player) and trainer) {
                canMove = false;
                lockOn[i] = true;

                if (trainer.isNextTo(player)) {
                    // TODO open dialogue, start battle
                    // functionState = 1;
                    player->face(&trainer);
                    trainer.clearParty();
                    canMove = true;
                    lockOn[i] = false;
                }
                else if (trainer.isFacingNorth()) {
                    trainer.shiftUpOnMap(SCROLL_SPEED);
                    walkCounters[i] += SCROLL_SPEED;

                    if (walkCounters[i] % TILE_SIZE == 0) {
                        trainer.moveNorth();
                    }
                }
                else if (trainer.isFacingEast()) {
                    trainer.shiftRightOnMap(SCROLL_SPEED);
                    walkCounters[i] += SCROLL_SPEED;

                    if (walkCounters[i] % TILE_SIZE == 0) {
                        trainer.moveEast();
                    }
                }
                else if (trainer.isFacingSouth()) {
                    trainer.shiftDownOnMap(SCROLL_SPEED);
                    walkCounters[i] += SCROLL_SPEED;

                    if (walkCounters[i] % TILE_SIZE == 0) {
                        trainer.moveSouth();
                    }
                }
                else if (trainer.isFacingWest()) {
                    trainer.shiftLeftOnMap(SCROLL_SPEED);
                    walkCounters[i] += SCROLL_SPEED;

                    if (walkCounters[i] % TILE_SIZE == 0) {
                        trainer.moveWest();
                    }
                }

                break;
            }
        }
    }

    // FIXME possibly make trainers turn slower
    for (int trainer = 0; trainer < currentMap->numTrainers(); ++trainer) {
        // does not potentially make the trainer move if true
        if (lockOn[trainer]) {
            continue;
        }
        switch (generateInteger(1, 100)) {
            case 1:
                (*currentMap)[trainer].face(&(*currentMap)[trainer]);

                if ((*currentMap)[trainer].hasVisionOf(player) and (*currentMap)[trainer]) {
                    //engage();
                    return;
                }
                break;

            case 2:
                if ((*currentMap)[trainer].isFacingNorth() or (*currentMap)[trainer].isFacingSouth()) {
                    coinFlip() ? (*currentMap)[trainer].faceEast() : (*currentMap)[trainer].faceWest();
                }
                else if ((*currentMap)[trainer].isFacingEast() or (*currentMap)[trainer].isFacingWest()) {
                    coinFlip() ? (*currentMap)[trainer].faceNorth() : (*currentMap)[trainer].faceSouth();
                }

                if ((*currentMap)[trainer].hasVisionOf(player) and (*currentMap)[trainer]) {
                    //engage();
                    return;
                }
                break;
        }
    }
}

void Game::updateBattle() {

}

void Game::renderOverworld() {
    SDL_RenderClear(gameRenderer);
    currentMap->renderMap();

    for (int trainer = 0; trainer < currentMap->numTrainers(); ++trainer) {
        // prevents rendering trainers that aren't onscreen
        if (Camera::isInView((*currentMap)[trainer].getRect())) {
            (*currentMap)[trainer].render();
        }
    }
    player->render();

    SDL_RenderPresent(gameRenderer);
}

void Game::renderBattle() {

}

Game::operator bool() const {
    return isRunning;
}