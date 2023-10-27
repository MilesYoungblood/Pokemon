//
// Created by Miles on 10/2/2023.
//

#include "Game.h"

Game::Game() {
    // initialize subsystems
    if (SDL_InitSubSystem(SDL_INIT_EVERYTHING) == 0) {
        std::cout << "Subsystems initialized!\n";
    }
    else {
        std::cerr << "Error initializing subsystems: " << SDL_GetError() << '\n';
        abort();
    }

    // create window
    gameWindow = SDL_CreateWindow("Pokémon", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    if (gameWindow != nullptr) {
        std::cout << "Window created!\n";
    }
    else {
        std::cerr << "Error creating window: " << SDL_GetError() << '\n';
        SDL_Quit();
        abort();
    }

    // load window icon
    SDL_Surface *pokeball = IMG_Load(std::string_view(PROJECT_PATH + R"(\sprites\pokeball.png)").data());
    if (pokeball != nullptr) {
        std::cout << "Icon loaded!\n";
    }
    else {
        std::cerr << "Error loading icon: " << SDL_GetError() << '\n';
        SDL_DestroyWindow(gameWindow);
        SDL_Quit();
        abort();
    }

    // set the window icon
    SDL_SetWindowIcon(gameWindow, pokeball);
    SDL_FreeSurface(pokeball);

    // create renderer
    gameRenderer = SDL_CreateRenderer(gameWindow, -1, 0);
    if (gameRenderer != nullptr) {
        std::cout << "Renderer created!\n";
    }
    else {
        std::cerr << "Error creating textureRenderer: " << SDL_GetError() << '\n';
        SDL_DestroyWindow(gameWindow);
        SDL_Quit();
        abort();
    }

    // assign the TextureManager's renderer
    TextureManager::textureRenderer = gameRenderer;

    // initialize audio
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

    // load music
    gameMusic = Mix_LoadMUS(std::string_view(PROJECT_PATH + R"(\music\TitleScreen.mp3)").data());
    if (gameMusic != nullptr) {
        std::cout << "Loaded \"TitleScreen\"!\n";
    }
    else {
        std::cerr << "Error loading \"TitleScreen\": " << SDL_GetError() << '\n';
        Player::destroyPlayer();
        Mix_CloseAudio();
        SDL_DestroyRenderer(gameRenderer);
        SDL_DestroyWindow(gameWindow);
        SDL_Quit();
        abort();
    }

    Mix_PlayMusic(gameMusic, -1);
    std::cout << "Playing \"TitleScreen\"!\n";

    if (TTF_Init() == 0) {
        std::cout << "Initialized TTF subsystems!\n";
    }
    else {
        std::cerr << "Error initializing TTF subsystems: " << SDL_GetError() << '\n';
        Player::destroyPlayer();
        Mix_HaltMusic();
        Mix_FreeMusic(gameMusic);
        Mix_CloseAudio();
        SDL_DestroyRenderer(gameRenderer);
        SDL_DestroyWindow(gameWindow);
        SDL_Quit();
        abort();
    }

    textFont = TTF_OpenFont(std::string_view(PROJECT_PATH + R"(\fonts\PokemonGb-RAeo.ttf)").data(), FONT_SIZE);
    if (textFont != nullptr) {
        std::cout << "Created font!\n";
    }
    else {
        std::cerr << "Error creating font: " << SDL_GetError() << '\n';
        Player::destroyPlayer();
        TTF_Quit();
        Mix_HaltMusic();
        Mix_FreeMusic(gameMusic);
        Mix_CloseAudio();
        SDL_DestroyRenderer(gameRenderer);
        SDL_DestroyWindow(gameWindow);
        SDL_Quit();
        abort();
    }

    text = TextureManager::LoadText(textFont, "Press enter to continue!", { 0, 0, 0 });

    logo = TextureManager::LoadTexture(PROJECT_PATH + R"(\sprites\Pokemon-Logo.png)");
    if (logo == nullptr) {
        std::cerr << "Error loading logo: " << SDL_GetError() << '\n';
        isRunning = false;
        return;
    }

    SDL_SetRenderDrawColor(gameRenderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
}

Game::~Game() {
    SDL_DestroyTexture(text);
    TTF_CloseFont(textFont);
    TTF_Quit();
    Mix_HaltMusic();
    Mix_FreeMusic(gameMusic);
    Mix_CloseAudio();
    SDL_DestroyRenderer(gameRenderer);
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
            saveFile << (*player)[pokemon][move].getID() << ' ' << (*player)[pokemon][move].getPP() << ' ';
        }
    }

    saveFile << '\n' << player->getNumItems(0) + player->getNumItems(1) + player->getNumItems(2) + player->getNumItems(3);
    for (int t = 0; t < 4; ++t) {
        const Item *item;
        for (int i = 0; i < player->getNumItems(t); ++i) {
            item = &player->getItem(t, i);
            saveFile << '\n' << static_cast<int>(item->getID()) << ' ' << item->getQuantity();
        }
    }

    for (int map = 0; map < maps.size(); ++map) {
        // moving the pointers takes it out of the array,
        // therefore, maps.at(map) will be nullptr;
        // we need to set currentMap's data manually
        if (map == currentMapIndex) {
            for (int trainer = 0; trainer < currentMap->numTrainers(); ++trainer) {
                saveFile << '\n' << map << ' ' << trainer << ' ' << (*currentMap)[trainer].partySize();
                saveFile << (*currentMap)[trainer].getDirection();
            }
            continue;
        }
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

        // grab the player's playerX-coordinates
        std::getline(saveFile, buffer, ' ');
        const int playerX = std::stoi(buffer);

        // grab the player's playerY-coordinates
        std::getline(saveFile, buffer, ' ');
        const int playerY = std::stoi(buffer);

        // grab the player's direction
        std::getline(saveFile, buffer);

        player = Player::getPlayer(playerX, playerY, buffer[0] - '0');

        // load the player's party size
        std::getline(saveFile, buffer);
        const int partySize = buffer[0] - '0';

        // load each Pokémon's data
        for (int pokemon = 0; pokemon < partySize; ++pokemon) {
            std::getline(saveFile, buffer, ' ');
            player->addPokemon(PokemonFactory::getPokemon(static_cast<PokemonID>(std::stoi(buffer))));

            // grabs the number of moves for this Pokémon
            std::getline(saveFile, buffer, ' ');
            const int numMoves = buffer[0] - '0';

            // load each move for this Pokémon
            for (int move = 0; move < numMoves; ++move) {
                std::getline(saveFile, buffer, ' ');
                const int id = std::stoi(buffer);

                std::getline(saveFile, buffer, ' ');
                const int savedPP = std::stoi(buffer);

                (*player)[pokemon].addMove(MoveFactory::getMove(static_cast<MoveID>(id), savedPP));
            }

            // necessary to grab the next line
            std::getline(saveFile, buffer);
        }

        // grab the total number of items in the player's bag
        std::getline(saveFile, buffer);
        const int totalNumItems = std::stoi(buffer);

        // load each item
        for (int i = 0; i < totalNumItems; ++i) {
            std::getline(saveFile, buffer, ' ');
            const int item = std::stoi(buffer);

            std::getline(saveFile, buffer);
            const int quantity = std::stoi(buffer);

            player->addItem(ItemFactory::getItem(static_cast<ItemID>(item), quantity));
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
                // FIXME change to adding Pokémon if not defeated
                (*maps.at(map))[trainer].clearParty();
            }

            (*maps.at(map))[trainer].setDirection(static_cast<Direction>(buffer[1] - '0'));
        }

        currentMap = std::move(maps.at(currentMapIndex));

        saveFile.close();
    }
    else {
        currentMapIndex = 0;
        currentMap = std::move(maps[0]);

        // default values for player
        player = Player::getPlayer();

        player->addPokemon<Greninja>();
        (*player)[0].addMove(std::make_unique<WaterShuriken>());
        (*player)[0].addMove(std::make_unique<DarkPulse>());
        (*player)[0].addMove(std::make_unique<IceBeam>());
        (*player)[0].addMove(std::make_unique<Extrasensory>());

        player->addPokemon<Charizard>();
        (*player)[1].addMove(std::make_unique<Flamethrower>());
        (*player)[1].addMove(std::make_unique<AirSlash>());
        (*player)[1].addMove(std::make_unique<DragonPulse>());
        (*player)[1].addMove(std::make_unique<SolarBeam>());

        player->addPokemon<Hydreigon>();
        (*player)[2].addMove(std::make_unique<DarkPulse>());
        (*player)[2].addMove(std::make_unique<DragonPulse>());
        (*player)[2].addMove(std::make_unique<Flamethrower>());
        (*player)[2].addMove(std::make_unique<FocusBlast>());

        player->addItem(std::make_unique<Potion>(5));
        player->addItem(std::make_unique<SuperPotion>(5));
        player->addItem(std::make_unique<HyperPotion>(5));
        player->addItem(std::make_unique<Ether>(5));

        player->addItem(std::make_unique<ParalyzeHeal>(5));
        player->addItem(std::make_unique<BurnHeal>(5));
        player->addItem(std::make_unique<IceHeal>(5));
        player->addItem(std::make_unique<Antidote>(5));
        player->addItem(std::make_unique<Awakening>(5));

        player->addItem(std::make_unique<PokeBall>(5));
        player->addItem(std::make_unique<GreatBall>(5));
        player->addItem(std::make_unique<UltraBall>(5));
        player->addItem(std::make_unique<MasterBall>(1));

        player->addItem(std::make_unique<XAttack>(5));
        player->addItem(std::make_unique<XDefense>(5));
        player->addItem(std::make_unique<XSpAttack>(5));
        player->addItem(std::make_unique<XSpDefense>(5));
        player->addItem(std::make_unique<XSpeed>(5));
        player->addItem(std::make_unique<XAccuracy>(5));
    }
}

Game::operator bool() const {
    return isRunning;
}
