//
// Created by Miles on 10/2/2023.
//

#include "Game.h"

bool print = false;

std::vector<int> pixelsTraveled;
std::vector<bool> lockTrainer;
std::vector<bool> keepLooping;

int numPages = 1;
int currentPage = 1;

Game::Game() {
    // initialize subsystems
    if (SDL_InitSubSystem(SDL_INIT_TIMER | SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0) {
        std::clog << "Error initializing subsystems: " << SDL_GetError() << '\n';
        SDL_ClearError();
        return;
    }

    // create window
    this->window = SDL_CreateWindow("Pokémon", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                    this->WINDOW_WIDTH, this->WINDOW_HEIGHT, 0U);
    if (this->window == nullptr) {
        std::clog << "Error creating window: " << SDL_GetError() << '\n';
        SDL_ClearError();
        return;
    }

    // initialize image subsystems
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
    SDL_SetWindowIcon(this->window, pokeball);
    SDL_FreeSurface(pokeball);

    // create renderer
    this->renderer = SDL_CreateRenderer(this->window, -1, 0U);
    if (this->renderer == nullptr) {
        std::clog << "Error creating renderer: " << SDL_GetError() << '\n';
        SDL_ClearError();
        return;
    }

    // initialize TextureManager
    TextureManager::getInstance().init(this->renderer);

    // initialize true type font subsystems
    if (TTF_Init() == -1) {
        std::clog << "Error initializing TTF subsystems: " << SDL_GetError() << '\n';
        SDL_ClearError();
        return;
    }

    // set the font for the message box
    this->font = TTF_OpenFont("../assets/fonts/PokemonGb-RAeo.ttf", this->FONT_SIZE);
    if (this->font == nullptr) {
        std::clog << "Error creating font: " << SDL_GetError() << '\n';
        SDL_ClearError();
        return;
    }

    // load the title image
    this->logo = TextureManager::getInstance().loadTexture("PokemonLogo.png");
    if (this->logo == nullptr) {
        std::clog << "Error loading logo: " << SDL_GetError() << '\n';
        SDL_ClearError();
        return;
    }

    // load the text prompt
    this->text = TextureManager::getInstance().loadText(this->font, "Press enter to continue!", { 0, 0, 0 });
    if (this->text == nullptr) {
        std::clog << "Error loading title text: " << SDL_GetError() << '\n';
        SDL_ClearError();
        return;
    }

    // initialize audio
    if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096) == -1) {
        std::clog << "Error opening the default audio device: " << SDL_GetError() << '\n';
        SDL_ClearError();
        return;
    }

    // load title screen music
    this->music = Mix_LoadMUS("../assets/audio/music/TitleScreen.mp3");
    if (this->music == nullptr) {
        std::clog << "Error loading \"TitleScreen\": " << SDL_GetError() << '\n';
        SDL_ClearError();
        return;
    }

    // play title screen music
    if (Mix_PlayMusic(this->music, -1) == -1) {
        std::clog << "Error playing \"TitleScreen\": " << SDL_GetError() << '\n';
        SDL_ClearError();
        return;
    }

    // instantiate KeyManager
    KeyManager::getInstance();

    SDL_SetRenderDrawColor(this->renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

    this->isRunning = true;
}

Game &Game::getInstance() {
    static Game game;
    return game;
}

Game::~Game() {
    Mix_HaltMusic();
    Mix_HookMusicFinished(nullptr);
    Mix_FreeMusic(this->music);
    Mix_CloseAudio();

    SDL_DestroyTexture(this->text);
    if (strlen(SDL_GetError()) > 0ULL) {
        std::clog << "Error destroying texture (texture may have already been deleted): " << SDL_GetError() << '\n';
        SDL_ClearError();
    }
    SDL_DestroyTexture(this->logo);
    if (strlen(SDL_GetError()) > 0ULL) {
        std::clog << "Error destroying texture (texture may have already been deleted): " << SDL_GetError() << '\n';
        SDL_ClearError();
    }
    TTF_CloseFont(this->font);
    TTF_Quit();

    IMG_Quit();

    SDL_DestroyRenderer(this->renderer);
    if (strlen(SDL_GetError()) > 0ULL) {
        std::clog << "Unable to destroy renderer: " << SDL_GetError() << '\n';
        SDL_ClearError();
    }
    SDL_DestroyWindow(this->window);
    if (strlen(SDL_GetError()) > 0ULL) {
        std::clog << "Unable to destroy window: " << SDL_GetError() << '\n';
        SDL_ClearError();
    }
    SDL_Quit();
}

void Game::handleEvents() {
    SDL_PollEvent(&this->event);
    this->HANDLE_FUNCTIONS.at(static_cast<std::size_t>(this->currentState))();
}

void Game::update() {
    this->UPDATE_FUNCTIONS.at(static_cast<std::size_t>(this->currentState))();
}

void Game::render() {
    SDL_RenderClear(this->renderer);
    this->RENDER_FUNCTIONS.at(static_cast<std::size_t>(this->currentState))();
    SDL_RenderPresent(this->renderer);
}

void Game::saveData() {
    std::ofstream saveFile("../docs/data/SaveData.txt");
    if (not saveFile) {
        std::clog << "Unable to open \"SaveData.txt\"\n";
        isRunning = false;
        return;
    }

    saveFile << this->currentMapIndex;
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

    for (int map = 0; map < this->maps.size(); ++map) {
        for (int trainer = 0; trainer < this->maps.at(map).numTrainers(); ++trainer) {
            saveFile << '\n' << map << ' ' << trainer << ' ' << this->maps.at(map)[trainer].partySize();
            saveFile << this->maps.at(map)[trainer].getDirection();
        }
    }

    saveFile.close();
}

void Game::initializeGame() {
    this->currentMapIndex = Map::Id::ROUTE_1;
    this->currentMap = &this->maps.at(this->currentMapIndex);

    this->maps[Map::Id::ROUTE_1].addTrainer("Cheren", 10, 8, Direction::DOWN, 3);
    this->maps[Map::Id::ROUTE_1][0].addPokemon(pokemonMap.at(Pokemon::Id::SAMUROTT)());
    this->maps[Map::Id::ROUTE_1].addTrainer("Bianca", 5, 6, Direction::DOWN, 3);
    this->maps[Map::Id::ROUTE_1][1].addPokemon(pokemonMap.at(Pokemon::Id::SERPERIOR)());

    // default values for player
    Player::getPlayer().init("Hilbert", 9, 10, Direction::DOWN);

    Player::getPlayer().addPokemon(pokemonMap.at(Pokemon::Id::EMBOAR)());

    //Player::getPlayer().addPokemon(pokemonMap.at(Pokemon::Id::ZEBSTRIKA)());
    //Player::getPlayer()[1].addMove(Move::Id::VOLT_TACKLE);

    //Player::getPlayer().addPokemon(pokemonMap.at(Pokemon::Id::EXCADRILL)());

    //Player::getPlayer().addPokemon(pokemonMap.at(Pokemon::Id::CARRACOSTA)());

    //Player::getPlayer().addPokemon(pokemonMap.at(Pokemon::Id::BRAVIARY)());

    //Player::getPlayer().addPokemon(pokemonMap.at(Pokemon::Id::HYDREIGON)());
    //Player::getPlayer()[3].addMove(Move::Id::DARK_PULSE);
    //Player::getPlayer()[3].addMove(Move::Id::DRAGON_PULSE);
    //Player::getPlayer()[3].addMove(Move::Id::FLAMETHROWER);
    //Player::getPlayer()[3].addMove(Move::Id::FOCUS_BLAST);

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

    // initialize map class
    Map::init();

    this->maps[Map::Id::ROUTE_1].addExitPoint({ 8, 2, Map::Id::ROUTE_2, 12, 20 });
    this->maps[Map::Id::ROUTE_1].addExitPoint({ 9, 2, Map::Id::ROUTE_2, 13, 20 });
    this->maps[Map::Id::ROUTE_1].addExitPoint({ 10, 2, Map::Id::ROUTE_2, 14, 20 });

    this->maps[Map::Id::ROUTE_2].addExitPoint({ 12, 21, Map::Id::ROUTE_1, 8, 3 });
    this->maps[Map::Id::ROUTE_2].addExitPoint({ 13, 21, Map::Id::ROUTE_1, 9, 3 });
    this->maps[Map::Id::ROUTE_2].addExitPoint({ 14, 21, Map::Id::ROUTE_1, 10, 3 });
    this->maps[Map::Id::ROUTE_2].addExitPoint({ 3, 11, Map::Id::ROUTE_3, 22, 6 });
    this->maps[Map::Id::ROUTE_2].addExitPoint({ 3, 12, Map::Id::ROUTE_3, 22, 7 });
    this->maps[Map::Id::ROUTE_2].addExitPoint({ 3, 13, Map::Id::ROUTE_3, 22, 8 });

    this->maps[Map::Id::ROUTE_3].addExitPoint({ 23, 6, Map::Id::ROUTE_2, 4, 11 });
    this->maps[Map::Id::ROUTE_3].addExitPoint({ 23, 7, Map::Id::ROUTE_2, 4, 12 });
    this->maps[Map::Id::ROUTE_3].addExitPoint({ 23, 8, Map::Id::ROUTE_2, 4, 13 });

    Trainer::init();

    // initialize RestoreItem class
    RestoreItem::init([](RestoreItem::Id id) -> RestoreItem::Data {
        return {
                restoreItems.at(id).name,
                restoreItems.at(id).amount,
                restoreItems.at(id).isHp
        };
    });

    // initialize StatusItem class
    StatusItem::init([](StatusItem::Id id) -> StatusItem::Data {
        return {
                statusItems.at(id).name,
                statusItems.at(id).status
        };
    });

    // initialize PokeBall class
    PokeBall::init([](PokeBall::Id id) -> PokeBall::Data {
        return {
                pokeBalls.at(id).name,
                pokeBalls.at(id).catchRate,
                pokeBalls.at(id).postCatch
        };
    });

    // initialize BattleItem class
    BattleItem::init([](BattleItem::Id id) -> BattleItem::Data {
        return {
                battleItems.at(id).name,
                battleItems.at(id).stat
        };
    });

    if (saveFile) {
        std::string buffer;

        // load the current map
        std::getline(saveFile, buffer);
        this->currentMapIndex = static_cast<Map::Id>(buffer[0] - '0');
        this->currentMap = &this->maps.at(this->currentMapIndex);

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
            Player::getPlayer().addPokemon(pokemonMap.at(static_cast<Pokemon::Id>(std::stoi(buffer)))());

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

                Player::getPlayer()[pokemon].addMove(moveMap.at(static_cast<Move::Id>(id))());
                Player::getPlayer()[pokemon][move].setPp(saved_pp);
                Player::getPlayer()[pokemon][move].setMaxPp(max_pp);
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
            const auto item = static_cast<PokeBall::Id>(std::stoi(buffer));

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

        this->maps[Map::Id::ROUTE_1].addTrainer("Cheren", 10, 8, Direction::DOWN, 3);
        this->maps[Map::Id::ROUTE_1][0].addPokemon(pokemonMap.at(Pokemon::Id::SAMUROTT)());
        this->maps[Map::Id::ROUTE_1].addTrainer("Bianca", 5, 6, Direction::DOWN, 3);
        this->maps[Map::Id::ROUTE_1][1].addPokemon(pokemonMap.at(Pokemon::Id::SERPERIOR)());

        std::stringstream ss;
        // load each trainer's data for every map
        while (std::getline(saveFile, buffer)) {
            ss >> buffer;

            // grabs the map
            std::getline(ss, buffer, ' ');
            const auto map = static_cast<Map::Id>(std::stoi(buffer));

            // grabs the trainer
            std::getline(ss, buffer, ' ');
            const int trainer = std::stoi(buffer);

            // grabs the trainer's party size
            std::getline(ss, buffer);
            if (buffer[0] == '0') {
                // deletes the Pokémon set if the trainer has been defeated
                // FIXME change to adding Pokémon if not defeated
                this->maps.at(map)[trainer].clearParty();
            }

            this->maps.at(map)[trainer].setDirection(static_cast<Direction>(buffer[1] - '0'));
        }

        saveFile.close();
    }
    else {
        this->initializeGame();
    }
}

int Game::getFps() const {
    return this->currentFps;
}

Game::operator bool() const {
    return this->isRunning;
}
