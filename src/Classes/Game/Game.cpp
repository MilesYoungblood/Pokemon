//
// Created by Miles on 10/2/2023.
//

#include "Game.h"
#include "../../Data/Data.h"

constexpr static int WINDOW_HEIGHT = TILE_SIZE * 7;     // height of the window
constexpr static int WINDOW_WIDTH = TILE_SIZE * 9;      // width of the window
constexpr static int SCROLL_SPEED = TILE_SIZE / 10;     // scroll speed

constexpr static int NUM_FUNCTION_STATES = 3;           // number of function states

namespace {
    SDL_Window *gameWindow = SDL_CreateWindow("Pokémon", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    SDL_Renderer *gameRenderer = SDL_CreateRenderer(gameWindow, -1, 0);
    SDL_Event event;
    Mix_Music *gameMusic = nullptr;

    [[maybe_unused]] TextureManager textureManager(gameRenderer);

    bool isRunning = true;                              // determines whether the game is running

    bool canMove = true;                                // determines whether the player can move

    std::array<bool, 4> moveDirection = {               // flags that determine when the player attempts to move
            false, false, false, false
    };

    std::array<bool, 4> keepMovingDirection = {         // ultimately, determine when the player stops moving
            false, false, false, false
    };

    bool interact = false;                              // signals when the player is trying to interact with something

    int walkCounter = 0;                                // measures how many screen pixels the player has moved

    std::vector<int> walkCounters;                      // measures how many screen pixels a trainer has moved
    std::vector<bool> lockOn;                           // determines whether a trainer can move spontaneously

    Player *player = nullptr;

    // TODO eventually change to 0 to start at title screen
    int functionState = 1;                              // determines which set of functions to use

    const std::array<void (*)(), NUM_FUNCTION_STATES> handleFunctions = {
            Game::handleTitleScreenEvents, Game::handleOverworldEvents, Game::handleBattleEvents
    };
    const std::array<void (*)(), NUM_FUNCTION_STATES> updateFunctions = {
            Game::updateTitleScreen, Game::updateOverworld, Game::updateBattle
    };
    const std::array<void (*)(), NUM_FUNCTION_STATES> renderFunctions = {
            Game::renderTitleScreen, Game::renderOverworld, Game::renderBattle
    };
}

Game::Game() {
    if (SDL_InitSubSystem(SDL_INIT_EVERYTHING) == 0) {
        std::cout << "Subsystems initialized!\n";
    }
    else {
        std::cerr << "Error initializing subsystems: " << SDL_GetError() << '\n';
        abort();
    }

    if (gameWindow != nullptr) {
        std::cout << "Window created!\n";
    }
    else {
        std::cerr << "Error creating window: " << SDL_GetError() << '\n';
        SDL_Quit();
        abort();
    }

    if (gameRenderer != nullptr) {
        std::cout << "Renderer created!\n";
    }
    else {
        std::cerr << "Error creating renderer: " << SDL_GetError() << '\n';
        SDL_DestroyWindow(gameWindow);
        SDL_Quit();
        abort();
    }

    SDL_Surface *pokeball = IMG_Load(std::string_view(PROJECT_PATH + R"(\sprites\pokeball.png)").data());
    if (pokeball != nullptr) {
        std::cout << "Icon loaded!\n";
    }
    else {
        std::cerr << "Error loading icon: " << SDL_GetError() << '\n';
        SDL_DestroyRenderer(gameRenderer);
        SDL_DestroyWindow(gameWindow);
        SDL_Quit();
        abort();
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
        abort();
    }

    player = Player::getPlayer();
    Game::loadData();

    const int extension_length = 4;
    const std::string_view music_path(currentMap->getMusic());
    const std::string_view song_name = music_path.substr(0, music_path.length() - extension_length);

    gameMusic = Mix_LoadMUS(std::string_view(PROJECT_PATH + "\\music\\" + currentMap->getMusic()).data());
    if (gameMusic != nullptr) {
        std::cout << "Loaded \"" << song_name << "\"!\n";
    }
    else {
        std::cerr << "Could not play sound: " << SDL_GetError() << '\n';
        Mix_CloseAudio();
        SDL_DestroyRenderer(gameRenderer);
        SDL_DestroyWindow(gameWindow);
        SDL_Quit();
        abort();
    }

    Mix_PlayMusic(gameMusic, -1);
    std::cout << "Playing \"" << song_name << "\"!\n";

    player->setRestoreItems({ new Potion(5), new SuperPotion(5), new HyperPotion(5), new Ether(5) });
    player->setStatusItems({ new ParalyzeHeal(5), new BurnHeal(5), new IceHeal(5), new Antidote(5), new Awakening(5) });
    player->setPokeBalls({ new PokeBall(5), new GreatBall(5), new UltraBall(5), new MasterBall(1) });
    player->setBattleItems({ new XAttack(5), new XDefense(5), new XSpAttack(5), new XSpDefense(5), new XSpeed(5), new XAccuracy(5) });

    Camera::lockOnPlayer(player, [](Direction direct, int dist) -> void { currentMap->updateMap(direct, dist); });

    walkCounters = std::vector<int>(currentMap->numTrainers(), 0);
    lockOn = std::vector<bool>(currentMap->numTrainers(), false);
}

Game::~Game() {
    Mix_HaltMusic();
    Mix_FreeMusic(gameMusic);
    Mix_CloseAudio();
    SDL_DestroyRenderer(gameRenderer);
    gameRenderer = nullptr;
    SDL_DestroyWindow(gameWindow);
    SDL_Quit();

    std::cout << "Game cleaned!\n";

    Player::destroyPlayer();
}

void Game::handleEvents() {
    SDL_PollEvent(&event);
    handleFunctions.at(functionState)();
}

void Game::update() {
    updateFunctions.at(functionState)();
}

void Game::render() {
    renderFunctions.at(functionState)();
}

void Game::saveData() {
    std::ofstream saveFile(PROJECT_PATH + R"(\src\Data\SaveData.txt)");
    if (not saveFile) {
        throw std::runtime_error("Could not open file");
    }

    saveFile << currentMapIndex;
    saveFile << '\n' << player->getX() << ' ' << player->getY() << ' ' << player->getDirection();
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
        for (int trainer = 0; trainer < maps.at(map)->numTrainers(); ++trainer) {
            saveFile << '\n' << map << ' ' << trainer << ' ' << (*maps.at(map))[trainer].partySize();
            saveFile << (*maps.at(map))[trainer].getDirection();
        }
    }

    saveFile.close();
}

void Game::loadData() {
    std::ifstream saveFile(PROJECT_PATH + R"(\src\Data\SaveData.txt)");

    if (saveFile) {
        std::string buffer;

        // load the current map
        std::getline(saveFile, buffer);
        currentMapIndex = buffer[0] - '0';
        currentMap = maps.at(currentMapIndex);

        // load the player's x-coordinates
        std::getline(saveFile, buffer, ' ');
        const int x = std::stoi(buffer);

        // load the player's y-coordinates
        std::getline(saveFile, buffer, ' ');
        const int y = std::stoi(buffer);

        player->setCoordinates(x, y);

        // load the player's direction
        std::getline(saveFile, buffer);
        player->setDirection(Direction(buffer[0] - '0'));

        // load the player's party size
        std::getline(saveFile, buffer);
        const int partySize = buffer[0] - '0';

        // load each Pokémon's data
        for (int pokemon = 0; pokemon < partySize; ++pokemon) {
            std::getline(saveFile, buffer, ' ');
            player->addPokemon(PokemonFactory::getPokemon(PokemonID(std::stoi(buffer))));

            // grabs the number of moves for this Pokémon
            std::getline(saveFile, buffer, ' ');
            const int numMoves = buffer[0] - '0';

            // load each move for this Pokémon
            for (int move = 0; move < numMoves; ++move) {
                std::getline(saveFile, buffer, ' ');
                (*player)[pokemon].addMove(MoveFactory::getMove(MoveID(std::stoi(buffer))));
            }

            // necessary to grab the next line
            std::getline(saveFile, buffer);
        }

        // load each trainer's data for every map
        while (std::getline(saveFile, buffer)) {
            std::stringstream ss(buffer);

            // grabs the map
            std::getline(ss, buffer, ' ');
            const int map = std::stoi(buffer);

            // grabs the trainer
            std::getline(ss, buffer, ' ');
            const int trainer = std::stoi(buffer);

            // grabs the trainer's party size
            std::getline(ss, buffer);
            if (buffer[0] == '0') {
                // deletes the Pokémon set if the trainer has been defeated
                (*maps.at(map))[trainer].clearParty();
            }

            (*maps.at(map))[trainer].setDirection(Direction(buffer[1] - '0'));
        }

        saveFile.close();
    }
    else {
        // default values for player
        // FIXME change
        player->addPokemon(new Greninja({ new WaterShuriken, new DarkPulse, new IceBeam, new Extrasensory }));
        player->addPokemon(new Charizard({ new Flamethrower, new AirSlash, new DragonPulse, new SolarBeam }));
        player->addPokemon(new Hydreigon({ new DarkPulse, new DragonPulse, new Flamethrower, new FocusBlast }));
    }
}

void Game::eraseData() {
    std::filesystem::remove(PROJECT_PATH + R"(\src\Data\SaveData.txt)");
}

void Game::handleTitleScreenEvents() {

}

void Game::handleOverworldKeyDown() {
    switch (event.key.keysym.scancode) {
        case SDL_SCANCODE_RETURN:
            interact = true;
            break;
        default:
            if (not canMove) {
                return;
            }
            switch (event.key.keysym.scancode) {
                case SDL_SCANCODE_W:
                    if (not player->isFacingNorth()) {
                        player->faceNorth();
                    }
                    else {
                        moveDirection[Direction::NORTH] = true;
                        keepMovingDirection[Direction::NORTH] = true;
                    }
                    break;
                case SDL_SCANCODE_A:
                    if (not player->isFacingWest()) {
                        player->faceWest();
                    }
                    else {
                        moveDirection[Direction::WEST] = true;
                        keepMovingDirection[Direction::WEST] = true;
                    }
                    break;
                case SDL_SCANCODE_S:
                    if (not player->isFacingSouth()) {
                        player->faceSouth();
                    }
                    else {
                        moveDirection[Direction::SOUTH] = true;
                        keepMovingDirection[Direction::SOUTH] = true;
                    }
                    break;
                case SDL_SCANCODE_D:
                    if (not player->isFacingEast()) {
                        player->faceEast();
                    }
                    else {
                        moveDirection[Direction::EAST] = true;
                        keepMovingDirection[Direction::EAST] = true;
                    }
                    break;
                default:
                    return;
            }
    }
}

void Game::handleOverworldEvents() {
    switch (event.type) {
        case SDL_QUIT:
            saveData();
            isRunning = false;
            break;

        case SDL_KEYDOWN:
            // do not accept keyboard input if your sprite is still moving
            if (keepMovingDirection[0] or keepMovingDirection[1] or keepMovingDirection[2] or keepMovingDirection[3]) {
                return;
            }
            Game::handleOverworldKeyDown();
            break;

        case SDL_KEYUP:
            switch (event.key.keysym.scancode) {
                case SDL_SCANCODE_W:
                    moveDirection[Direction::NORTH] = false;
                    break;
                case SDL_SCANCODE_A:
                    moveDirection[Direction::WEST] = false;
                    break;
                case SDL_SCANCODE_S:
                    moveDirection[Direction::SOUTH] = false;
                    break;
                case SDL_SCANCODE_D:
                    moveDirection[Direction::EAST] = false;
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

void Game::updateTitleScreen() {

}

void Game::changeMap(const std::array<int, 3> &data) {
    const int extension_length = 4;
    const std::string_view music_path(currentMap->getMusic());

    if (Mix_FadeOutMusic(2000) != 0) {
        std::cout << "Fading out \"" << music_path.substr(0, music_path.length() - extension_length) << "\"!\n";
    }

    Mix_HookMusicFinished([] -> void {
        Mix_FreeMusic(gameMusic);

        gameMusic = Mix_LoadMUS(std::string_view(PROJECT_PATH + "\\music\\" + currentMap->getMusic()).data());
        if (gameMusic != nullptr) {
            const std::string_view music_path(currentMap->getMusic());
            const std::string_view song_name = music_path.substr(0, music_path.length() - extension_length);
            std::cout << "Loaded \"" << song_name << "\"!\n";

            Mix_PlayMusic(gameMusic, -1);
            std::cout << "Playing \"" << song_name << "\"!\n";
        }
    });

    currentMap->resetMap();

    // switches the map
    currentMapIndex = data[2];
    currentMap = maps.at(currentMapIndex);

    // resets the states of these variables for each trainer
    walkCounters = std::vector<int>(currentMap->numTrainers(), 0);
    lockOn = std::vector<bool>(currentMap->numTrainers(), false);

    player->setCoordinates(data[0], data[1]);

    Camera::lockOnPlayer(player, [](Direction direct, int dist) -> void { currentMap->updateMap(direct, dist); });
}

void Game::checkForOpponents() {
    void (*resetVariables)() = [] -> void {
        keepMovingDirection[0] = false;
        keepMovingDirection[1] = false;
        keepMovingDirection[2] = false;
        keepMovingDirection[3] = false;
        walkCounter = 0;
    };

    // resets movement variables if you are not inputting any directions
    if (not (moveDirection[0] or moveDirection[1] or moveDirection[2] or moveDirection[3])) {
        resetVariables();
    }

    Trainer *trainer;

    // checks if the player is in LoS for any trainer
    for (int i = 0; i < currentMap->numTrainers(); ++i) {
        trainer = &(*currentMap)[i];

        if (trainer->hasVisionOf(player) and *trainer) {
            resetVariables();
            canMove = false;
            lockOn[i] = true;

            if (trainer->isNextTo(player)) {
                // TODO open dialogue, start battle
                // functionState = 1;
                player->face(trainer);
                trainer->clearParty();
                walkCounters[i] = 0;
                lockOn[i] = false;
                canMove = true;
            }

            trainer->shiftDirectionOnMap(trainer->getDirection(), SCROLL_SPEED);
            walkCounters[i] += SCROLL_SPEED;

            if (walkCounters[i] % TILE_SIZE == 0) {
                trainer->moveForward();
            }

            break;
        }
    }
}

void Game::updateTrainers() {
    Trainer *trainer;

    // FIXME possibly make trainers turn slower
    for (int i = 0; i < currentMap->numTrainers(); ++i) {
        // does not potentially make the trainer move spontaneously if true
        if (lockOn[i]) {
            continue;
        }

        trainer = &(*currentMap)[i];
        switch (generateInteger(1, 100)) {
            case 1:
                trainer->face(trainer);

                if (trainer->hasVisionOf(player) and *trainer) {
                    //engage();
                    return;
                }
                break;

            case 2:
                if (trainer->isFacingNorth() or trainer->isFacingSouth()) {
                    coinFlip() ? trainer->faceEast() : trainer->faceWest();
                }
                else if (trainer->isFacingEast() or trainer->isFacingWest()) {
                    coinFlip() ? trainer->faceNorth() : trainer->faceSouth();
                }

                if (trainer->hasVisionOf(player) and *trainer) {
                    //engage();
                    return;
                }
                break;
        }
    }
}

void Game::updateOverworld() {
    const Direction pDirection = player->getDirection();

    const std::array<int, 3> mapData = currentMap->isExitPointHere(player->getX(), player->getY());
    if (mapData[2] != -1) {
        Game::changeMap(mapData);
    }
    else if (interact) {
        Trainer *trainer;       // variable used to reduce the number of function calls

        for (int i = 0; i < currentMap->numTrainers(); ++i) {
            trainer = &(*currentMap)[i];

            if (player->hasVisionOf(trainer) and not trainer->hasVisionOf(player)) {
                trainer->face(player);
                break;
            }
        }
        interact = false;
    }
    else if (player->canMoveForward(currentMap) and (moveDirection.at(pDirection) or keepMovingDirection.at(pDirection))) {
        const Direction qDirection = oppositeDirection(pDirection);

        Camera::shift(pDirection, SCROLL_SPEED);
        currentMap->updateMap(qDirection, SCROLL_SPEED);
        walkCounter += SCROLL_SPEED;

        if (walkCounter % TILE_SIZE == 0) {
            player->moveForward();
        }
    }

    // if the player's sprite is on a tile...
    if (walkCounter % TILE_SIZE == 0) {
        Game::checkForOpponents();
    }

    Game::updateTrainers();
}

void Game::updateBattle() {

}

void Game::renderTitleScreen() {

}

void Game::renderOverworld() {
    SDL_RenderClear(gameRenderer);
    currentMap->renderMap();

    Trainer *trainer;       // variable to reduce the number of function calls
    for (int i = 0; i < currentMap->numTrainers(); ++i) {
        trainer = &(*currentMap)[i];
        // prevents rendering trainers that aren't onscreen
        if (Camera::isInView(trainer->getRect()) != 0U) {
            trainer->render();
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
