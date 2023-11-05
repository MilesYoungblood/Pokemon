//
// Created by Miles on 10/2/2023.
//

#include "Game.h"

Game::Game() {
    // initialize subsystems
    if (SDL_InitSubSystem(SDL_INIT_TIMER | SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_EVENTS) == 0) {
        std::cout << "Subsystems isInitialized!\n";
    }
    else {
        std::cerr << "Error initializing subsystems: " << SDL_GetError() << '\n';
        return;
    }

    // create window
    gameWindow = SDL_CreateWindow("Pokémon", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                  WINDOW_WIDTH, WINDOW_HEIGHT, 0U);
    if (gameWindow != nullptr) {
        std::cout << "Window created!\n";
    }
    else {
        std::cerr << "Error creating window: " << SDL_GetError() << '\n';
        return;
    }

    // initialize image subsystems
    IMG_Init(IMG_INIT_PNG);

    // load window icon
    SDL_Surface *pokeball = IMG_Load(std::string_view(PROJECT_PATH + R"(\sprites\pokeball.png)").data());
    if (pokeball != nullptr) {
        std::cout << "Icon loaded!\n";
    }
    else {
        std::cerr << "Error loading icon: " << SDL_GetError() << '\n';
        return;
    }

    // set the window icon
    SDL_SetWindowIcon(gameWindow, pokeball);
    SDL_FreeSurface(pokeball);

    // create renderer
    gameRenderer = SDL_CreateRenderer(gameWindow, -1, 0U);
    if (gameRenderer != nullptr) {
        std::cout << "Renderer created!\n";
    }
    else {
        std::cerr << "Error creating renderer: " << SDL_GetError() << '\n';
        return;
    }

    // initialize TextureManager
    TextureManager::getInstance()->init(gameRenderer);

    // initialize true type font subsystems
    if (TTF_Init() == 0) {
        std::cout << "Initialized TTF subsystems!\n";
    }
    else {
        std::cerr << "Error initializing TTF subsystems: " << SDL_GetError() << '\n';
        return;
    }

    // set the font for the message box
    textFont = TTF_OpenFont(std::string_view(PROJECT_PATH + R"(\fonts\PokemonGb-RAeo.ttf)").data(), FONT_SIZE);
    if (textFont != nullptr) {
        std::cout << "Created font!\n";
    }
    else {
        std::cerr << "Error creating font: " << SDL_GetError() << '\n';
        return;
    }

    // load the title image
    logo = TextureManager::getInstance()->loadTexture(PROJECT_PATH + R"(\sprites\Pokemon-Logo.png)");
    if (logo == nullptr) {
        std::cerr << "Error loading logo: " << SDL_GetError() << '\n';
        return;
    }

    // load the text prompt
    text = TextureManager::getInstance()->loadText(textFont, "Press enter to continue!", { 0, 0, 0 });
    if (text != nullptr) {
        std::cout << "Loaded title text!\n";
    }
    else {
        std::cout << "Error loading title text: " << SDL_GetError() << '\n';
        return;
    }

    // initialize audio
    if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096) == 0) {
        std::cout << "Default audio device opened!\n";
    }
    else {
        std::cerr << "Could not open the default audio device: " << SDL_GetError() << '\n';
        return;
    }

    // load title screen music
    gameMusic = Mix_LoadMUS(std::string_view(PROJECT_PATH + R"(\music\TitleScreen.mp3)").data());
    if (gameMusic != nullptr) {
        std::cout << "Loaded \"TitleScreen\"!\n";
    }
    else {
        std::cerr << "Error loading \"TitleScreen\": " << SDL_GetError() << '\n';
        return;
    }

    // play title screen music
    if (Mix_PlayMusic(gameMusic, -1) == 0) {
        std::cout << "Playing \"TitleScreen\"!\n";
    }
    else {
        std::cerr << "Error playing \"TitleScreen\": " << SDL_GetError() << '\n';
        return;
    }

    // instantiate KeyManager
    KeyManager::getInstance();

    SDL_SetRenderDrawColor(gameRenderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

    isRunning = true;
}

Game::~Game() {
    Camera::deleteInstance();
    KeyManager::deleteInstance();
    TextureManager::deleteInstance();

    Mix_HaltMusic();
    Mix_HookMusicFinished([] -> void {});
    Mix_FreeMusic(gameMusic);
    Mix_CloseAudio();

    SDL_DestroyTexture(text);
    if (strlen(SDL_GetError()) == 0ULL) {
        std::cout << "Texture destroyed!\n";
    }
    else {
        std::cerr << "Error destroying texture (texture may have already been deleted): " << SDL_GetError() << '\n';
        SDL_ClearError();
    }
    SDL_DestroyTexture(logo);
    if (strlen(SDL_GetError()) == 0ULL) {
        std::cout << "Texture destroyed!\n";
    }
    else {
        std::cerr << "Error destroying texture (texture may have already been deleted): " << SDL_GetError() << '\n';
        SDL_ClearError();
    }
    TTF_CloseFont(textFont);
    TTF_Quit();

    IMG_Quit();

    SDL_DestroyRenderer(gameRenderer);
    if (strlen(SDL_GetError()) == 0ULL) {
        std::cout << "Rendered destroyed!\n";
    }
    else {
        std::cerr << "Unable to destroy renderer: " << SDL_GetError() << '\n';
        SDL_ClearError();
    }
    SDL_DestroyWindow(gameWindow);
    if (strlen(SDL_GetError()) == 0ULL) {
        std::cout << "Window destroyed!\n";
    }
    else {
        std::cerr << "Unable to destroy window: " << SDL_GetError() << '\n';
    }
    SDL_Quit();

    std::cout << "Game cleaned!\n";

    Player::destroyPlayer();
}

void Game::handleEvents() {
    SDL_PollEvent(&event);
    HANDLE_FUNCTIONS.at(gameState)();
}

void Game::update() {
    UPDATE_FUNCTIONS.at(gameState)();
}

void Game::render() {
    SDL_RenderClear(gameRenderer);
    RENDER_FUNCTIONS.at(gameState)();
    SDL_RenderPresent(gameRenderer);
}

void Game::saveData() {
    std::ofstream saveFile;
    if (not saveFile) {
        std::cerr << "Unable to open file\n";
        isRunning = false;
        return;
    }

    saveFile << currentMapIndex;
    saveFile << '\n' << player->getX() << ' ' << player->getY() << ' ' << player->getDirection();
    saveFile << '\n' << player->partySize();
    for (int pokemon = 0; pokemon < player->partySize(); ++pokemon) {
        saveFile << '\n' << (*player)[pokemon].getID() << ' ';

        const int num_moves = (*player)[pokemon].numMoves();
        saveFile << num_moves << ' ';

        for (int move = 0; move < num_moves; ++move) {
            saveFile << (*player)[pokemon][move].getID() << ' ' << (*player)[pokemon][move].getPP() << ' ';
        }
    }

    Item *item;

    const int num_restore_items = player->getNumItems<RestoreItem>();
    const int num_status_items = player->getNumItems<StatusItem>();
    const int num_poke_balls = player->getNumItems<PokeBall>();
    const int num_battle_items = player->getNumItems<BattleItem>();

    saveFile << '\n' << num_restore_items + num_status_items + num_poke_balls + num_battle_items;

    for (int i = 0; i < num_restore_items; ++i) {
        item = &player->getItem<RestoreItem>(i);
        saveFile << '\n' << static_cast<int>(item->getID()) << ' ' << item->getQuantity();
    }

    for (int i = 0; i < num_status_items; ++i) {
        item = &player->getItem<StatusItem>(i);
        saveFile << '\n' << static_cast<int>(item->getID()) << ' ' << item->getQuantity();
    }

    for (int i = 0; i < num_poke_balls; ++i) {
        item = &player->getItem<PokeBall>(i);
        saveFile << '\n' << static_cast<int>(item->getID()) << ' ' << item->getQuantity();
    }

    for (int i = 0; i < num_battle_items; ++i) {
        item = &player->getItem<BattleItem>(i);
        saveFile << '\n' << static_cast<int>(item->getID()) << ' ' << item->getQuantity();
    }

    for (int map = 0; map < maps.size(); ++map) {
        for (int trainer = 0; trainer < maps.at(map).numTrainers(); ++trainer) {
            saveFile << '\n' << map << ' ' << trainer << ' ' << maps.at(map)[trainer].partySize();
            saveFile << maps.at(map)[trainer].getDirection();
        }
    }

    saveFile.close();
}

void initializeGame() {
    currentMapIndex = 0;
    currentMap = &maps.at(currentMapIndex);

    // initialize all maps
    Map::initTextures();

    maps[0].addTrainer(std::make_unique<Trainer>("Cheren", 7, 6, Direction::DOWN, 3));
    maps[0].addTrainer(std::make_unique<Trainer>("Bianca", 2, 4, Direction::DOWN, 3));
    maps[0][1].addPokemon<Serperior>();

    maps[0].addExitPoint({ 5, 0, MapID::ROUTE_2, 9, 18 });
    maps[0].addExitPoint({ 6, 0, MapID::ROUTE_2, 10, 18 });
    maps[0].addExitPoint({ 7, 0, MapID::ROUTE_2, 11, 18 });

    maps[1].addExitPoint({ 9, 19, MapID::ROUTE_1, 5, 1 });
    maps[1].addExitPoint({ 10, 19, MapID::ROUTE_1, 6, 1 });
    maps[1].addExitPoint({ 11, 19, MapID::ROUTE_1, 7, 1 });
    maps[1].addExitPoint({ 0, 10, MapID::ROUTE_3, 19, 5 });

    maps[2].addExitPoint({ 20, 5, MapID::ROUTE_2, 1, 10 });

    // default values for player
    player = Player::getPlayer();

    player->addPokemon<Greninja>();
    (*player)[0].addMove<WaterShuriken>();
    (*player)[0].addMove<DarkPulse>();
    (*player)[0].addMove<IceBeam>();
    (*player)[0].addMove<Extrasensory>();

    player->addPokemon<Charizard>();
    (*player)[1].addMove<Flamethrower>();
    (*player)[1].addMove<AirSlash>();
    (*player)[1].addMove<DragonPulse>();
    (*player)[1].addMove<SolarBeam>();

    player->addPokemon<Hydreigon>();
    (*player)[2].addMove<DarkPulse>();
    (*player)[2].addMove<DragonPulse>();
    (*player)[2].addMove<Flamethrower>();
    (*player)[2].addMove<FocusBlast>();

    player->addItem<Potion>(5);
    player->addItem<SuperPotion>(5);
    player->addItem<HyperPotion>(5);
    player->addItem<Ether>(5);

    player->addItem<ParalyzeHeal>(5);
    player->addItem<BurnHeal>(5);
    player->addItem<IceHeal>(5);
    player->addItem<Antidote>(5);
    player->addItem<Awakening>(5);

    player->addItem<PokeBall>(5);
    player->addItem<GreatBall>(5);
    player->addItem<UltraBall>(5);
    player->addItem<MasterBall>(1);

    player->addItem<XAttack>(5);
    player->addItem<XDefense>(5);
    player->addItem<XSpAttack>(5);
    player->addItem<XSpDefense>(5);
    player->addItem<XSpeed>(5);
    player->addItem<XAccuracy>(5);
}

void loadGame() {

}

void Game::loadData() {
    std::ifstream saveFile(PROJECT_PATH + R"(\src\Data\SaveData.txt)");

    Trainer::init();

    if (saveFile) {
        std::string buffer;

        // load the current map
        std::getline(saveFile, buffer);
        currentMapIndex = buffer[0] - '0';

        // grab the player's x-coordinates
        std::getline(saveFile, buffer, ' ');
        const int player_x = std::stoi(buffer);

        // grab the player's y-coordinates
        std::getline(saveFile, buffer, ' ');
        const int player_y = std::stoi(buffer);

        // grab the player's direction
        std::getline(saveFile, buffer);

        //TODO load player name dynamically
        player = Player::getPlayer("Hilbert", player_x, player_y, static_cast<Direction>(buffer[0] - '0'));

        // load the player's party size
        std::getline(saveFile, buffer);
        const int party_size = buffer[0] - '0';

        // load each Pokémon's data
        for (int pokemon = 0; pokemon < party_size; ++pokemon) {
            std::getline(saveFile, buffer, ' ');
            player->addPokemon(PokemonFactory::getPokemon(static_cast<PokemonID>(std::stoi(buffer))));

            // grabs the number of moves for this Pokémon
            std::getline(saveFile, buffer, ' ');
            const int num_moves = buffer[0] - '0';

            // load each move for this Pokémon
            for (int move = 0; move < num_moves; ++move) {
                std::getline(saveFile, buffer, ' ');
                const int id = std::stoi(buffer);

                std::getline(saveFile, buffer, ' ');
                const int saved_pp = std::stoi(buffer);

                (*player)[pokemon].addMove(MoveFactory::getMove(static_cast<MoveID>(id), saved_pp));
            }

            // necessary to grab the next line
            std::getline(saveFile, buffer);
        }

        // grab the total number of items in the player's bag
        std::getline(saveFile, buffer);
        const int total_num_items = std::stoi(buffer);

        // load each item
        for (int i = 0; i < total_num_items; ++i) {
            std::getline(saveFile, buffer, ' ');
            const int item = std::stoi(buffer);

            std::getline(saveFile, buffer);
            const int quantity = std::stoi(buffer);

            player->addItem(ItemFactory::getItem(static_cast<ItemID>(item), quantity));
        }

        // initialize all maps
        Map::initTextures();

        maps[MapID::ROUTE_1].addTrainer(std::make_unique<Trainer>("Cheren", 7, 6, Direction::DOWN, 3));
        maps[MapID::ROUTE_1].addTrainer(std::make_unique<Trainer>("Bianca", 2, 4, Direction::DOWN, 3));
        maps[MapID::ROUTE_1][1].addPokemon<Serperior>();
        maps[MapID::ROUTE_1].addExitPoint({ 5, 0, MapID::ROUTE_2, 9, 18 });
        maps[MapID::ROUTE_1].addExitPoint({ 6, 0, MapID::ROUTE_2, 10, 18 });
        maps[MapID::ROUTE_1].addExitPoint({ 7, 0, MapID::ROUTE_2, 11, 18 });

        maps[MapID::ROUTE_2].addExitPoint({ 9, 19, MapID::ROUTE_1, 5, 1 });
        maps[MapID::ROUTE_2].addExitPoint({ 10, 19, MapID::ROUTE_1, 6, 1 });
        maps[MapID::ROUTE_2].addExitPoint({ 11, 19, MapID::ROUTE_1, 7, 1 });
        maps[MapID::ROUTE_2].addExitPoint({ 0, 9, MapID::ROUTE_3, 19, 4 });
        maps[MapID::ROUTE_2].addExitPoint({ 0, 10, MapID::ROUTE_3, 19, 5 });
        maps[MapID::ROUTE_2].addExitPoint({ 0, 11, MapID::ROUTE_3, 19, 6 });

        maps[MapID::ROUTE_3].addExitPoint({ 20, 4, MapID::ROUTE_2, 1, 9 });
        maps[MapID::ROUTE_3].addExitPoint({ 20, 5, MapID::ROUTE_2, 1, 10 });
        maps[MapID::ROUTE_3].addExitPoint({ 20, 6, MapID::ROUTE_2, 1, 11 });

        std::stringstream ss;
        // load each trainer's data for every map
        while (std::getline(saveFile, buffer)) {
            ss >> buffer;

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
                maps.at(map)[trainer].clearParty();
            }

            maps.at(map)[trainer].setDirection(static_cast<Direction>(buffer[1] - '0'));
        }

        currentMap = &maps.at(currentMapIndex);

        saveFile.close();
    }
    else {
        initializeGame();
    }
}

Game::operator bool() const {
    return isRunning;
}
