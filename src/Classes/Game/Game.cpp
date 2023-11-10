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
        std::clog << "Error initializing subsystems: " << SDL_GetError() << '\n';
        return;
    }

    // create window
    Game::window = SDL_CreateWindow("Pokémon", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                  Game::WINDOW_WIDTH, Game::WINDOW_HEIGHT, 0U);
    if (Game::window != nullptr) {
        std::cout << "Window created!\n";
    }
    else {
        std::clog << "Error creating window: " << SDL_GetError() << '\n';
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
        std::clog << "Error loading icon: " << SDL_GetError() << '\n';
        return;
    }

    // set the window icon
    SDL_SetWindowIcon(Game::window, pokeball);
    SDL_FreeSurface(pokeball);

    // create renderer
    Game::renderer = SDL_CreateRenderer(Game::window, -1, 0U);
    if (Game::renderer != nullptr) {
        std::cout << "Renderer created!\n";
    }
    else {
        std::clog << "Error creating renderer: " << SDL_GetError() << '\n';
        return;
    }

    // initialize TextureManager
    TextureManager::getInstance().init(Game::renderer);

    // initialize true type font subsystems
    if (TTF_Init() == 0) {
        std::cout << "Initialized TTF subsystems!\n";
    }
    else {
        std::clog << "Error initializing TTF subsystems: " << SDL_GetError() << '\n';
        return;
    }

    // set the font for the message box
    Game::font = TTF_OpenFont(std::string_view(PROJECT_PATH + R"(\fonts\PokemonGb-RAeo.ttf)").data(), Game::FONT_SIZE);
    if (Game::font != nullptr) {
        std::cout << "Created font!\n";
    }
    else {
        std::clog << "Error creating font: " << SDL_GetError() << '\n';
        return;
    }

    // load the title image
    Game::logo = TextureManager::getInstance().loadTexture(PROJECT_PATH + R"(\sprites\Pokemon-Logo.png)");
    if (Game::logo != nullptr) {
        std::cout << "Loaded logo!\n";
    }
    else {
        std::clog << "Error loading logo: " << SDL_GetError() << '\n';
        return;
    }

    // load the text prompt
    Game::text = TextureManager::getInstance().loadText(Game::font, "Press enter to continue!", { 0, 0, 0 });
    if (Game::text != nullptr) {
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
        std::clog << "Could not open the default audio device: " << SDL_GetError() << '\n';
        return;
    }

    // load title screen music
    Game::music = Mix_LoadMUS(std::string_view(PROJECT_PATH + R"(\music\TitleScreen.mp3)").data());
    if (Game::music != nullptr) {
        std::cout << "Loaded \"TitleScreen\"!\n";
    }
    else {
        std::clog << "Error loading \"TitleScreen\": " << SDL_GetError() << '\n';
        return;
    }

    // play title screen music
    if (Mix_PlayMusic(Game::music, -1) == 0) {
        std::cout << "Playing \"TitleScreen\"!\n";
    }
    else {
        std::clog << "Error playing \"TitleScreen\": " << SDL_GetError() << '\n';
        return;
    }

    // instantiate KeyManager
    KeyManager::getInstance();

    SDL_SetRenderDrawColor(Game::renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

    isRunning = true;
}

Game &Game::getInstance() {
    static Game game;
    return game;
}

Game::~Game() {
    Mix_HaltMusic();
    Mix_HookMusicFinished(nullptr);
    Mix_FreeMusic(Game::music);
    Mix_CloseAudio();

    SDL_DestroyTexture(Game::text);
    if (strlen(SDL_GetError()) == 0ULL) {
        std::cout << "Texture destroyed!\n";
    }
    else {
        std::clog << "Error destroying texture (texture may have already been deleted): " << SDL_GetError() << '\n';
        SDL_ClearError();
    }
    SDL_DestroyTexture(Game::logo);
    if (strlen(SDL_GetError()) == 0ULL) {
        std::cout << "Texture destroyed!\n";
    }
    else {
        std::clog << "Error destroying texture (texture may have already been deleted): " << SDL_GetError() << '\n';
        SDL_ClearError();
    }
    TTF_CloseFont(Game::font);
    TTF_Quit();

    IMG_Quit();

    SDL_DestroyRenderer(Game::renderer);
    if (strlen(SDL_GetError()) == 0ULL) {
        std::cout << "Rendered destroyed!\n";
    }
    else {
        std::clog << "Unable to destroy renderer: " << SDL_GetError() << '\n';
        SDL_ClearError();
    }
    SDL_DestroyWindow(Game::window);
    if (strlen(SDL_GetError()) == 0ULL) {
        std::cout << "Window destroyed!\n";
    }
    else {
        std::clog << "Unable to destroy window: " << SDL_GetError() << '\n';
    }
    SDL_Quit();

    std::cout << "Game cleaned!\n";
}

void Game::handleEvents() {
    SDL_PollEvent(&Game::event);
    this->HANDLE_FUNCTIONS.at(Game::currentState)();
}

void Game::update() {
    this->UPDATE_FUNCTIONS.at(Game::currentState)();
}

void Game::render() {
    SDL_RenderClear(Game::renderer);
    this->RENDER_FUNCTIONS.at(Game::currentState)();
    SDL_RenderPresent(Game::renderer);
}

void Game::saveData() {
    std::ofstream saveFile(PROJECT_PATH + R"(\Data\SaveData.txt)");
    if (not saveFile) {
        std::clog << "Unable to open \"SaveData.txt\"\n";
        isRunning = false;
        return;
    }

    saveFile << Game::currentMapIndex;
    saveFile << '\n' << Player::getPlayer().getX() << ' ' << Player::getPlayer().getY() << ' '
             << Player::getPlayer().getDirection();
    saveFile << '\n' << Player::getPlayer().partySize();
    for (int pokemon = 0; pokemon < Player::getPlayer().partySize(); ++pokemon) {
        saveFile << '\n' << Player::getPlayer()[pokemon].getID() << ' ';

        const int num_moves = Player::getPlayer()[pokemon].numMoves();
        saveFile << num_moves << ' ';

        for (int move = 0; move < num_moves; ++move) {
            saveFile << Player::getPlayer()[pokemon][move].getID() << ' '
                     << Player::getPlayer()[pokemon][move].getPP() << ' ';
        }
    }

    Item *item;

    const int num_restore_items = Player::getPlayer().getNumItems<RestoreItem>();
    const int num_status_items = Player::getPlayer().getNumItems<StatusItem>();
    const int num_poke_balls = Player::getPlayer().getNumItems<PokeBall>();
    const int num_battle_items = Player::getPlayer().getNumItems<BattleItem>();

    saveFile << '\n' << num_restore_items + num_status_items + num_poke_balls + num_battle_items;

    for (int i = 0; i < num_restore_items; ++i) {
        item = &Player::getPlayer().getItem<RestoreItem>(i);
        saveFile << '\n' << static_cast<int>(item->getID()) << ' ' << item->getQuantity();
    }

    for (int i = 0; i < num_status_items; ++i) {
        item = &Player::getPlayer().getItem<StatusItem>(i);
        saveFile << '\n' << static_cast<int>(item->getID()) << ' ' << item->getQuantity();
    }

    for (int i = 0; i < num_poke_balls; ++i) {
        item = &Player::getPlayer().getItem<PokeBall>(i);
        saveFile << '\n' << static_cast<int>(item->getID()) << ' ' << item->getQuantity();
    }

    for (int i = 0; i < num_battle_items; ++i) {
        item = &Player::getPlayer().getItem<BattleItem>(i);
        saveFile << '\n' << static_cast<int>(item->getID()) << ' ' << item->getQuantity();
    }

    for (int map = 0; map < Game::maps.size(); ++map) {
        for (int trainer = 0; trainer < Game::maps.at(map).numTrainers(); ++trainer) {
            saveFile << '\n' << map << ' ' << trainer << ' ' << Game::maps.at(map)[trainer].partySize();
            saveFile << Game::maps.at(map)[trainer].getDirection();
        }
    }

    saveFile.close();
}

void Game::initializeGame() {
    Game::currentMapIndex = 0;
    Game::currentMap = &Game::maps.at(Game::currentMapIndex);

    Game::maps[Map::ID::ROUTE_1].addTrainer(std::make_unique<Trainer>("Cheren", 10, 8, Direction::DOWN, 3));
    Game::maps[Map::ID::ROUTE_1][0].addPokemon<Samurott>();
    Game::maps[Map::ID::ROUTE_1].addTrainer(std::make_unique<Trainer>("Bianca", 5, 6, Direction::DOWN, 3));
    Game::maps[Map::ID::ROUTE_1][1].addPokemon<Serperior>();

    // default values for player
    Player::getPlayer().init("Hilbert", 9, 10, Direction::DOWN);

    Player::getPlayer().addPokemon<Emboar>();

    Player::getPlayer().addPokemon<Zebstrika>();
    Player::getPlayer()[1].addMove<VoltTackle>();

    Player::getPlayer().addPokemon<Excadrill>();
    Player::getPlayer()[2].addMove<Flamethrower>();
    Player::getPlayer()[2].addMove<AirSlash>();
    Player::getPlayer()[2].addMove<DragonPulse>();
    Player::getPlayer()[2].addMove<SolarBeam>();

    Player::getPlayer().addPokemon<Hydreigon>();
    Player::getPlayer()[3].addMove<DarkPulse>();
    Player::getPlayer()[3].addMove<DragonPulse>();
    Player::getPlayer()[3].addMove<Flamethrower>();
    Player::getPlayer()[3].addMove<FocusBlast>();

    Player::getPlayer().addItem<Potion>(5);
    Player::getPlayer().addItem<SuperPotion>(5);
    Player::getPlayer().addItem<HyperPotion>(5);
    Player::getPlayer().addItem<Ether>(5);

    Player::getPlayer().addItem<ParalyzeHeal>(5);
    Player::getPlayer().addItem<BurnHeal>(5);
    Player::getPlayer().addItem<IceHeal>(5);
    Player::getPlayer().addItem<Antidote>(5);
    Player::getPlayer().addItem<Awakening>(5);

    Player::getPlayer().addItem<PokeBall>(5);
    Player::getPlayer().addItem<GreatBall>(5);
    Player::getPlayer().addItem<UltraBall>(5);
    Player::getPlayer().addItem<MasterBall>(1);

    Player::getPlayer().addItem<XAttack>(5);
    Player::getPlayer().addItem<XDefense>(5);
    Player::getPlayer().addItem<XSpAttack>(5);
    Player::getPlayer().addItem<XSpDefense>(5);
    Player::getPlayer().addItem<XSpeed>(5);
    Player::getPlayer().addItem<XAccuracy>(5);
}

void Game::loadData() {
    std::ifstream saveFile(PROJECT_PATH + R"(\Data\SaveData.txt)");

    // initialize all maps
    Map::initTextures();

    Game::maps[Map::ID::ROUTE_1].addExitPoint({ 8, 2, Map::ID::ROUTE_2, 12, 20 });
    Game::maps[Map::ID::ROUTE_1].addExitPoint({ 9, 2, Map::ID::ROUTE_2, 13, 20 });
    Game::maps[Map::ID::ROUTE_1].addExitPoint({ 10, 2, Map::ID::ROUTE_2, 14, 20 });

    Game::maps[Map::ID::ROUTE_2].addExitPoint({ 12, 21, Map::ID::ROUTE_1, 8, 3 });
    Game::maps[Map::ID::ROUTE_2].addExitPoint({ 13, 21, Map::ID::ROUTE_1, 9, 3 });
    Game::maps[Map::ID::ROUTE_2].addExitPoint({ 14, 21, Map::ID::ROUTE_1, 10, 3 });
    Game::maps[Map::ID::ROUTE_2].addExitPoint({ 3, 11, Map::ID::ROUTE_3, 22, 6 });
    Game::maps[Map::ID::ROUTE_2].addExitPoint({ 3, 12, Map::ID::ROUTE_3, 22, 7 });
    Game::maps[Map::ID::ROUTE_2].addExitPoint({ 3, 13, Map::ID::ROUTE_3, 22, 8 });

    Game::maps[Map::ID::ROUTE_3].addExitPoint({ 23, 6, Map::ID::ROUTE_2, 4, 11 });
    Game::maps[Map::ID::ROUTE_3].addExitPoint({ 23, 7, Map::ID::ROUTE_2, 4, 12 });
    Game::maps[Map::ID::ROUTE_3].addExitPoint({ 23, 8, Map::ID::ROUTE_2, 4, 13 });

    Trainer::init();

    if (saveFile) {
        std::string buffer;

        // load the current map
        std::getline(saveFile, buffer);
        Game::currentMapIndex = buffer[0] - '0';
        Game::currentMap = &Game::maps.at(Game::currentMapIndex);

        // grab the player's x-coordinates
        std::getline(saveFile, buffer, ' ');
        const int player_x = std::stoi(buffer);

        // grab the player's y-coordinates
        std::getline(saveFile, buffer, ' ');
        const int player_y = std::stoi(buffer);

        // grab the player's direction
        std::getline(saveFile, buffer);

        //TODO load player name dynamically
        Player::getPlayer().init("Hilbert", player_x, player_y, static_cast<Direction>(buffer[0] - '0'));

        // load the player's party size
        std::getline(saveFile, buffer);
        const int party_size = buffer[0] - '0';

        // load each Pokémon's data
        for (int pokemon = 0; pokemon < party_size; ++pokemon) {
            std::getline(saveFile, buffer, ' ');
            Player::getPlayer().addPokemon(PokemonFactory::getPokemon(static_cast<Pokemon::ID>(std::stoi(buffer))));

            // grabs the number of moves for this Pokémon
            std::getline(saveFile, buffer, ' ');
            const int num_moves = buffer[0] - '0';

            // load each move for this Pokémon
            for (int move = 0; move < num_moves; ++move) {
                std::getline(saveFile, buffer, ' ');
                const int id = std::stoi(buffer);

                std::getline(saveFile, buffer, ' ');
                const int saved_pp = std::stoi(buffer);

                Player::getPlayer()[pokemon].addMove(MoveFactory::getMove(static_cast<Move::ID>(id), saved_pp));
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

            Player::getPlayer().addItem(ItemFactory::getItem(static_cast<Item::ID>(item), quantity));
        }

        Game::maps[Map::ID::ROUTE_1].addTrainer(std::make_unique<Trainer>("Cheren", 10, 8, Direction::DOWN, 3));
        Game::maps[Map::ID::ROUTE_1][0].addPokemon<Samurott>();
        Game::maps[Map::ID::ROUTE_1].addTrainer(std::make_unique<Trainer>("Bianca", 5, 6, Direction::DOWN, 3));
        Game::maps[Map::ID::ROUTE_1][1].addPokemon<Serperior>();

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
                Game::maps.at(map)[trainer].clearParty();
            }

            Game::maps.at(map)[trainer].setDirection(static_cast<Direction>(buffer[1] - '0'));
        }

        saveFile.close();
    }
    else {
        Game::initializeGame();
    }
}

int Game::getFPS() {
    return Game::currentFps;
}

Game::operator bool() const {
    return Game::isRunning;
}
