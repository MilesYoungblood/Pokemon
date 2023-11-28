//
// Created by Miles on 10/2/2023.
//

#include "Game.h"

Game::Game() {
    // dataFunction subsystems
    if (SDL_InitSubSystem(SDL_INIT_TIMER | SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0) {
        std::clog << "Error initializing subsystems: " << SDL_GetError() << '\n';
        SDL_ClearError();
        return;
    }

    // create window
    Game::window = SDL_CreateWindow("Pokémon", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                    Game::WINDOW_WIDTH, Game::WINDOW_HEIGHT, 0U);
    if (Game::window == nullptr) {
        std::clog << "Error creating window: " << SDL_GetError() << '\n';
        SDL_ClearError();
        return;
    }

    // dataFunction image subsystems
    if (IMG_Init(IMG_InitFlags::IMG_INIT_PNG) == 0) {
        std::clog << "Error initializing image subsystems: " << SDL_GetError() << '\n';
        SDL_ClearError();
        return;
    }

    // load window icon
    SDL_Surface *pokeball = IMG_Load("../assets/images/pokeball.png");
    if (pokeball == nullptr) {
        std::clog << "Error loading icon: " << SDL_GetError() << '\n';
        SDL_ClearError();
        return;
    }

    // set the window icon
    SDL_SetWindowIcon(Game::window, pokeball);
    SDL_FreeSurface(pokeball);

    // create renderer
    Game::renderer = SDL_CreateRenderer(Game::window, -1, 0U);
    if (Game::renderer == nullptr) {
        std::clog << "Error creating renderer: " << SDL_GetError() << '\n';
        SDL_ClearError();
        return;
    }

    // dataFunction TextureManager
    TextureManager::getInstance().init(Game::renderer);

    // dataFunction true type font subsystems
    if (TTF_Init() == -1) {
        std::clog << "Error initializing TTF subsystems: " << SDL_GetError() << '\n';
        SDL_ClearError();
        return;
    }

    // set the font for the message box
    Game::font = TTF_OpenFont("../assets/fonts/PokemonGb-RAeo.ttf", Game::FONT_SIZE);
    if (Game::font == nullptr) {
        std::clog << "Error creating font: " << SDL_GetError() << '\n';
        SDL_ClearError();
        return;
    }

    // load the title image
    Game::logo = TextureManager::getInstance().loadTexture("PokemonLogo.png");
    if (Game::logo == nullptr) {
        std::clog << "Error loading logo: " << SDL_GetError() << '\n';
        SDL_ClearError();
        return;
    }

    // load the text prompt
    Game::text = TextureManager::getInstance().loadText(Game::font, "Press enter to continue!", { 0, 0, 0 });
    if (Game::text == nullptr) {
        std::clog << "Error loading title text: " << SDL_GetError() << '\n';
        SDL_ClearError();
        return;
    }

    // dataFunction audio
    if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096) == -1) {
        std::clog << "Error opening the default audio device: " << SDL_GetError() << '\n';
        SDL_ClearError();
        return;
    }

    // load title screen music
    Game::music = Mix_LoadMUS("../assets/audio/music/TitleScreen.mp3");
    if (Game::music == nullptr) {
        std::clog << "Error loading \"TitleScreen\": " << SDL_GetError() << '\n';
        SDL_ClearError();
        return;
    }

    // play title screen music
    if (Mix_PlayMusic(Game::music, -1) == -1) {
        std::clog << "Error playing \"TitleScreen\": " << SDL_GetError() << '\n';
        SDL_ClearError();
        return;
    }

    // instantiate KeyManager
    KeyManager::getInstance();

    SDL_SetRenderDrawColor(Game::renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

    Game::isRunning = true;
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
    if (strlen(SDL_GetError()) > 0ULL) {
        std::clog << "Error destroying texture (texture may have already been deleted): " << SDL_GetError() << '\n';
        SDL_ClearError();
    }
    SDL_DestroyTexture(Game::logo);
    if (strlen(SDL_GetError()) > 0ULL) {
        std::clog << "Error destroying texture (texture may have already been deleted): " << SDL_GetError() << '\n';
        SDL_ClearError();
    }
    TTF_CloseFont(Game::font);
    TTF_Quit();

    IMG_Quit();

    SDL_DestroyRenderer(Game::renderer);
    if (strlen(SDL_GetError()) > 0ULL) {
        std::clog << "Unable to destroy renderer: " << SDL_GetError() << '\n';
        SDL_ClearError();
    }
    SDL_DestroyWindow(Game::window);
    if (strlen(SDL_GetError()) > 0ULL) {
        std::clog << "Unable to destroy window: " << SDL_GetError() << '\n';
        SDL_ClearError();
    }
    SDL_Quit();
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
    std::ofstream saveFile("../docs/data/SaveData.txt");
    if (not saveFile) {
        std::clog << "Unable to open \"SaveData.txt\"\n";
        isRunning = false;
        return;
    }

    saveFile << Game::currentMapIndex;
    saveFile << '\n' << Player::getPlayer().getX() << ' ' << Player::getPlayer().getY() << ' '
             << static_cast<int>(Player::getPlayer().getDirection());
    saveFile << '\n' << Player::getPlayer().partySize();
    for (int pokemon = 0; pokemon < Player::getPlayer().partySize(); ++pokemon) {
        saveFile << '\n' << static_cast<int>(Player::getPlayer()[pokemon].getId()) << ' ';

        const int num_moves = Player::getPlayer()[pokemon].numMoves();
        saveFile << num_moves << ' ';

        for (int move = 0; move < num_moves; ++move) {
            saveFile << static_cast<int>(Player::getPlayer()[pokemon][move].getId()) << ' '
                     << Player::getPlayer()[pokemon][move].getPp() << ' '
                     << Player::getPlayer()[pokemon][move].getMaxPp() << ' ';
        }
    }

    const int num_restore_items = Player::getPlayer().getNumItems<RestoreItem>();
    const int num_status_items = Player::getPlayer().getNumItems<StatusItem>();
    const int num_poke_balls = Player::getPlayer().getNumItems<PokeBall>();
    const int num_battle_items = Player::getPlayer().getNumItems<BattleItem>();

    saveFile << '\n' << num_restore_items;

    RestoreItem *restoreItem;
    for (int i = 0; i < num_restore_items; ++i) {
        restoreItem = &Player::getPlayer().getItem<RestoreItem>(i);
        saveFile << '\n' << static_cast<int>(restoreItem->getId()) << ' ' << restoreItem->getQuantity();
    }

    saveFile << '\n' << num_status_items;

    StatusItem *statusItem;
    for (int i = 0; i < num_status_items; ++i) {
        statusItem = &Player::getPlayer().getItem<StatusItem>(i);
        saveFile << '\n' << static_cast<int>(statusItem->getId()) << ' ' << statusItem->getQuantity();
    }

    saveFile << '\n' << num_poke_balls;

    PokeBall *pokeBall;
    for (int i = 0; i < num_poke_balls; ++i) {
        pokeBall = &Player::getPlayer().getItem<PokeBall>(i);
        saveFile << '\n' << static_cast<int>(pokeBall->getId()) << ' ' << pokeBall->getQuantity();
    }

    saveFile << '\n' << num_battle_items;

    BattleItem *battleItem;
    for (int i = 0; i < num_battle_items; ++i) {
        battleItem = &Player::getPlayer().getItem<BattleItem>(i);
        saveFile << '\n' << static_cast<int>(battleItem->getId()) << ' ' << battleItem->getQuantity();
    }

    for (int map = 0; map < Game::maps.size(); ++map) {
        for (int trainer = 0; trainer < Game::maps.at(map).numTrainers(); ++trainer) {
            saveFile << '\n' << map << ' ' << trainer << ' ' << Game::maps.at(map)[trainer].partySize();
            saveFile << static_cast<int>(Game::maps.at(map)[trainer].getDirection());
        }
    }

    saveFile.close();
}

void Game::initializeGame() {
    Game::currentMapIndex = Map::Id::ROUTE_1;
    Game::currentMap = &Game::maps.at(Game::currentMapIndex);

    Game::maps[Map::Id::ROUTE_1].addTrainer("Cheren", 10, 8, Direction::DOWN, 3);
    Game::maps[Map::Id::ROUTE_1][0].addPokemon(Pokemon::Id::SAMUROTT);
    Game::maps[Map::Id::ROUTE_1].addTrainer("Bianca", 5, 6, Direction::DOWN, 3);
    Game::maps[Map::Id::ROUTE_1][1].addPokemon(Pokemon::Id::SERPERIOR);

    // default values for player
    Player::getPlayer().init("Hilbert", 9, 10, Direction::DOWN);

    Player::getPlayer().addPokemon(Pokemon::Id::EMBOAR);

    Player::getPlayer().addPokemon(Pokemon::Id::ZEBSTRIKA);
    Player::getPlayer()[1].addMove<VoltTackle>();

    Player::getPlayer().addPokemon(Pokemon::Id::EXCADRILL);

    Player::getPlayer().addPokemon(Pokemon::Id::CARRACOSTA);

    Player::getPlayer().addPokemon(Pokemon::Id::BRAVIARY);

    Player::getPlayer().addPokemon(Pokemon::Id::HYDREIGON);
    Player::getPlayer()[3].addMove<DarkPulse>();
    Player::getPlayer()[3].addMove<DragonPulse>();
    Player::getPlayer()[3].addMove<Flamethrower>();
    Player::getPlayer()[3].addMove<FocusBlast>();

    Player::getPlayer().addItem<RestoreItem>(RestoreItem::Id::POTION, 5);
    Player::getPlayer().addItem<RestoreItem>(RestoreItem::Id::SUPER_POTION, 5);
    Player::getPlayer().addItem<RestoreItem>(RestoreItem::Id::HYPER_POTION, 5);
    Player::getPlayer().addItem<RestoreItem>(RestoreItem::Id::MAX_POTION, 5);
    Player::getPlayer().addItem<RestoreItem>(RestoreItem::Id::ETHER, 5);
    Player::getPlayer().addItem<RestoreItem>(RestoreItem::Id::ETHER, 5);

    Player::getPlayer().addItem<StatusItem>(StatusItem::Id::PARALYZE_HEAL, 5);
    Player::getPlayer().addItem<StatusItem>(StatusItem::Id::BURN_HEAL, 5);
    Player::getPlayer().addItem<StatusItem>(StatusItem::Id::ICE_HEAL, 5);
    Player::getPlayer().addItem<StatusItem>(StatusItem::Id::ANTIDOTE, 5);
    Player::getPlayer().addItem<StatusItem>(StatusItem::Id::AWAKENING, 5);

    Player::getPlayer().addItem<PokeBall>(PokeBall::Id::POKE_BALL, 5);
    Player::getPlayer().addItem<PokeBall>(PokeBall::Id::GREAT_BALL, 5);
    Player::getPlayer().addItem<PokeBall>(PokeBall::Id::ULTRA_BALL, 5);
    Player::getPlayer().addItem<PokeBall>(PokeBall::Id::MASTER_BALL, 1);

    Player::getPlayer().addItem<BattleItem>(BattleItem::Id::X_ATTACK, 5);
    Player::getPlayer().addItem<BattleItem>(BattleItem::Id::X_DEFENSE, 5);
    Player::getPlayer().addItem<BattleItem>(BattleItem::Id::X_SP_ATTACK, 5);
    Player::getPlayer().addItem<BattleItem>(BattleItem::Id::X_SP_DEFENSE, 5);
    Player::getPlayer().addItem<BattleItem>(BattleItem::Id::X_SPEED, 5);
    Player::getPlayer().addItem<BattleItem>(BattleItem::Id::X_ACCURACY, 5);
}

void Game::loadData() {
    std::ifstream saveFile("../docs/data/SaveData.txt");

    // dataFunction map class
    Map::initTextures();

    Game::maps[Map::Id::ROUTE_1].addExitPoint({ 8, 2, Map::Id::ROUTE_2, 12, 20 });
    Game::maps[Map::Id::ROUTE_1].addExitPoint({ 9, 2, Map::Id::ROUTE_2, 13, 20 });
    Game::maps[Map::Id::ROUTE_1].addExitPoint({ 10, 2, Map::Id::ROUTE_2, 14, 20 });

    Game::maps[Map::Id::ROUTE_2].addExitPoint({ 12, 21, Map::Id::ROUTE_1, 8, 3 });
    Game::maps[Map::Id::ROUTE_2].addExitPoint({ 13, 21, Map::Id::ROUTE_1, 9, 3 });
    Game::maps[Map::Id::ROUTE_2].addExitPoint({ 14, 21, Map::Id::ROUTE_1, 10, 3 });
    Game::maps[Map::Id::ROUTE_2].addExitPoint({ 3, 11, Map::Id::ROUTE_3, 22, 6 });
    Game::maps[Map::Id::ROUTE_2].addExitPoint({ 3, 12, Map::Id::ROUTE_3, 22, 7 });
    Game::maps[Map::Id::ROUTE_2].addExitPoint({ 3, 13, Map::Id::ROUTE_3, 22, 8 });

    Game::maps[Map::Id::ROUTE_3].addExitPoint({ 23, 6, Map::Id::ROUTE_2, 4, 11 });
    Game::maps[Map::Id::ROUTE_3].addExitPoint({ 23, 7, Map::Id::ROUTE_2, 4, 12 });
    Game::maps[Map::Id::ROUTE_3].addExitPoint({ 23, 8, Map::Id::ROUTE_2, 4, 13 });

    Trainer::init();

    Pokemon::initData([](Pokemon::Id id) -> Pokemon::Data {
        return {
                pokemonLookupTable.at(id).name,
                pokemonLookupTable.at(id).species,
                pokemonLookupTable.at(id).type1,
                pokemonLookupTable.at(id).type2,
                pokemonLookupTable.at(id).height,
                pokemonLookupTable.at(id).weight,
                pokemonLookupTable.at(id).baseHp,
                pokemonLookupTable.at(id).baseAttack,
                pokemonLookupTable.at(id).baseDefense,
                pokemonLookupTable.at(id).baseSpAttack,
                pokemonLookupTable.at(id).baseSpDefense,
                pokemonLookupTable.at(id).baseSpeed,
                pokemonLookupTable.at(id).baseLevel,
                pokemonLookupTable.at(id).catchRate
        };
    });

    // initialize RestoreItem class
    RestoreItem::initName([](RestoreItem::Id id) -> std::string {
        return std::string(restoreItems.at(id).name);
    });

    RestoreItem::initAmount([](RestoreItem::Id id) -> int {
        return restoreItems.at(id).amount;
    });

    RestoreItem::initHp([](RestoreItem::Id id) -> bool {
        return restoreItems.at(id).isHp;
    });

    // initialize StatusItem class
    StatusItem::initName([](StatusItem::Id id) -> std::string {
        return std::string(statusItems.at(id).name);
    });

    StatusItem::initStatus([](StatusItem::Id id) -> Status {
        return statusItems.at(id).status;
    });

    // initialize PokeBall class
    PokeBall::initName([](PokeBall::Id id) -> std::string {
        return std::string(pokeBalls.at(id).name);
    });

    PokeBall::initCatchRate([](PokeBall::Id id, const Pokemon &pokemon, Time time, int turn, bool isCave) -> double {
        return pokeBalls.at(id).catchRate(pokemon, time, turn, isCave);
    });

    PokeBall::initPostCatch([](PokeBall::Id id, Pokemon &pokemon) -> void {
        pokeBalls.at(id).postCatch(pokemon);
    });

    // initialize BattleItem class
    BattleItem::initName([](BattleItem::Id id) -> std::string {
        return std::string(battleItems.at(id).name);
    });

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
            Player::getPlayer().addPokemon(static_cast<Pokemon::Id>(std::stoi(buffer)));

            // grabs the number of moves for this Pokémon
            std::getline(saveFile, buffer, ' ');
            const int num_moves = buffer[0] - '0';

            // load each move for this Pokémon
            for (int move = 0; move < num_moves; ++move) {
                std::getline(saveFile, buffer, ' ');
                const int id = std::stoi(buffer);

                std::getline(saveFile, buffer, ' ');
                const int saved_pp = std::stoi(buffer);

                std::getline(saveFile, buffer, ' ');
                const int max_pp = std::stoi(buffer);

                Player::getPlayer()[pokemon].addMove(MoveFactory::getMove(static_cast<Move::Id>(id), saved_pp, max_pp));
            }

            // necessary to grab the next line
            std::getline(saveFile, buffer);
        }

        // grab the total number of restore items in the player's bag
        std::getline(saveFile, buffer);
        const int num_restore_items = std::stoi(buffer);

        // load each item
        for (int i = 0; i < num_restore_items; ++i) {
            std::getline(saveFile, buffer, ' ');
            const auto item = static_cast<RestoreItem::Id>(std::stoi(buffer));

            std::getline(saveFile, buffer);
            const int quantity = std::stoi(buffer);

            Player::getPlayer().addItem<RestoreItem>(item, quantity);
        }

        // grab the total number of status items in the player's bag
        std::getline(saveFile, buffer);
        const int num_status_items = std::stoi(buffer);

        // load each item
        for (int i = 0; i < num_status_items; ++i) {
            std::getline(saveFile, buffer, ' ');
            const auto item = static_cast<StatusItem::Id>(std::stoi(buffer));

            std::getline(saveFile, buffer);
            const int quantity = std::stoi(buffer);

            Player::getPlayer().addItem<StatusItem>(item, quantity);
        }

        // grab the total number of restore items in the player's bag
        std::getline(saveFile, buffer);
        const int num_poke_balls = std::stoi(buffer);

        // load each item
        for (int i = 0; i < num_poke_balls; ++i) {
            std::getline(saveFile, buffer, ' ');
            const PokeBall::Id item = static_cast<PokeBall::Id>(std::stoi(buffer));

            std::getline(saveFile, buffer);
            const int quantity = std::stoi(buffer);

            Player::getPlayer().addItem<PokeBall>(item, quantity);
        }

        // grab the total number of restore items in the player's bag
        std::getline(saveFile, buffer);
        const int num_battle_items = std::stoi(buffer);

        // load each item
        for (int i = 0; i < num_battle_items; ++i) {
            std::getline(saveFile, buffer, ' ');
            const auto item = static_cast<BattleItem::Id>(std::stoi(buffer));

            std::getline(saveFile, buffer);
            const int quantity = std::stoi(buffer);

            Player::getPlayer().addItem<BattleItem>(item, quantity);
        }

        Game::maps[Map::Id::ROUTE_1].addTrainer("Cheren", 10, 8, Direction::DOWN, 3);
        Game::maps[Map::Id::ROUTE_1][0].addPokemon(Pokemon::Id::SAMUROTT);
        Game::maps[Map::Id::ROUTE_1].addTrainer("Bianca", 5, 6, Direction::DOWN, 3);
        Game::maps[Map::Id::ROUTE_1][1].addPokemon(Pokemon::Id::SERPERIOR);

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

int Game::getFps() {
    return Game::currentFps;
}

Game::operator bool() const {
    return Game::isRunning;
}
