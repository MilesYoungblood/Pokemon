//
// Created by Miles on 10/2/2023.
//

#include "Game.h"

std::unordered_map<Trainer *, int> pixelsTraveled;
std::unordered_map<Trainer *, bool> keepLooping;
Stopwatch keyDelay;

Game::Game() {
    // initialize subsystems
    if (SDL_InitSubSystem(SDL_INIT_TIMER | SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0) {
        std::clog << "Error initializing subsystems: " << SDL_GetError() << '\n';
        SDL_ClearError();
        return;
    }

    // create window
    this->window = SDL_CreateWindow("Pokémon", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                    this->WINDOW_WIDTH, this->WINDOW_HEIGHT, 0);
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
    this->renderer = SDL_CreateRenderer(this->window, -1, 0);
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

    // initialize audio
    if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096) == -1) {
        std::clog << "Error opening the default audio device: " << SDL_GetError() << '\n';
        SDL_ClearError();
        return;
    }

    Mixer::getInstance().playMusic("TitleScreen");

    // instantiate KeyManager
    KeyManager::getInstance();

    // initialize TextBox
    TextBox::init(this->renderer, this->font);

    SDL_SetRenderDrawColor(this->renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

    this->running = true;
}

Game::~Game() {
    Mix_HaltMusic();
    Mix_HookMusicFinished(nullptr);
    Mix_CloseAudio();

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
    if (SDL_PollEvent(&this->event) == 1) {
        switch (this->event.type) {
            case SDL_EventType::SDL_QUIT:
                this->running = false;
                break;
            case SDL_EventType::SDL_KEYDOWN:
                keyDelay.start();
                break;
            case SDL_EventType::SDL_KEYUP:
                keyDelay.stop();
                break;
            default:
                break;
        }
    }
}

void Game::update() {
    this->states.at(static_cast<std::size_t>(this->currentState))->update();
}

void Game::render() const {
    SDL_RenderClear(this->renderer);
    this->states.at(static_cast<std::size_t>(this->currentState))->render();
    SDL_RenderPresent(this->renderer);
}

void Game::terminate() {
    this->running = false;
}

void Game::saveData() {
    std::ofstream saveFile("../docs/data/SaveData.txt");
    if (not saveFile.is_open()) {
        std::clog << "Unable to open \"SaveData.txt\"\n";
        this->running = false;
        return;
    }

    saveFile << this->currentMapIndex;
    saveFile << '\n' << Player::getPlayer().getX() << ' ' << Player::getPlayer().getY() << ' '
             << static_cast<int>(Player::getPlayer().getDirection());
    saveFile << '\n' << Player::getPlayer().partySize();
    for (auto &pokemon : Player::getPlayer()) {
        saveFile << '\n' << pokemon->getId() << ' ';
        saveFile << '\n' << pokemon->getGender() << ' ';
        // TODO eventually remove try-catch
        try {
            saveFile << '\n' << pokemon->getAbility().getId() << ' ';
        }
        catch (const std::exception &e) {
            std::clog << "Error writing ability to file: " << e.what() << '\n';
        }

        const int num_moves = pokemon->numMoves();
        saveFile << num_moves << ' ';

        for (auto &move : *pokemon) {
            saveFile << move->getId() << ' ' << move->getPp() << ' ' << move->getMaxPp() << ' ';
        }
    }

    const std::size_t num_restore_items = Player::getPlayer().getNumItems<RestoreItem>();
    const std::size_t num_status_items = Player::getPlayer().getNumItems<StatusItem>();
    const std::size_t num_poke_balls = Player::getPlayer().getNumItems<PokeBall>();
    const std::size_t num_battle_items = Player::getPlayer().getNumItems<BattleItem>();

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

    for (std::size_t map = 0ULL; map < this->maps.size(); ++map) {
        for (int trainer = 0; trainer < this->maps.at(map).numTrainers(); ++trainer) {
            saveFile << '\n' << map << ' ' << trainer << ' ' << this->maps.at(map)[trainer].partySize();
            saveFile << static_cast<int>(this->maps.at(map)[trainer].getDirection());
        }
    }

    saveFile.close();
}

void defaultAction(Entity *entity) {
    if (GraphicsEngine::getInstance().hasAny<Rectangle>()) {
        return;
    }
    switch (generateInteger(1, 100 * Game::getInstance().getFps() / 30)) {
        case 1:
            entity->face(entity);
            break;

        case 2:
            if (entity->isFacing(Direction::UP) or entity->isFacing(Direction::DOWN)) {
                binomial() ? entity->setDirection(Direction::LEFT) : entity->setDirection(Direction::RIGHT);
            }
            else {
                binomial() ? entity->setDirection(Direction::UP) : entity->setDirection(Direction::DOWN);
            }
            break;
        default:
            break;
    }
}

void Game::initializeGame() {
    // default values for player
    Player::getPlayer().init("Hilbert", 7, 17, Direction::DOWN);

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

    Player::getPlayer().addItem<RestoreItem>(restoreItems.at(RestoreItem::Id::POTION)(5));
    Player::getPlayer().addItem<RestoreItem>(restoreItems.at(RestoreItem::Id::SUPER_POTION)(5));
    Player::getPlayer().addItem<RestoreItem>(restoreItems.at(RestoreItem::Id::HYPER_POTION)(5));
    Player::getPlayer().addItem<RestoreItem>(restoreItems.at(RestoreItem::Id::MAX_POTION)(5));
    Player::getPlayer().addItem<RestoreItem>(restoreItems.at(RestoreItem::Id::ETHER)(5));
    Player::getPlayer().addItem<RestoreItem>(restoreItems.at(RestoreItem::Id::MAX_ETHER)(5));

    Player::getPlayer().addItem<StatusItem>(statusItems.at(StatusItem::Id::AWAKENING)(5));
    Player::getPlayer().addItem<StatusItem>(statusItems.at(StatusItem::Id::ANTIDOTE)(5));
    Player::getPlayer().addItem<StatusItem>(statusItems.at(StatusItem::Id::BURN_HEAL)(5));
    Player::getPlayer().addItem<StatusItem>(statusItems.at(StatusItem::Id::ICE_HEAL)(5));
    Player::getPlayer().addItem<StatusItem>(statusItems.at(StatusItem::Id::PARALYZE_HEAL)(5));

    Player::getPlayer().addItem<PokeBall>(pokeBalls.at(PokeBall::Id::POKE_BALL)(5));
    Player::getPlayer().addItem<PokeBall>(pokeBalls.at(PokeBall::Id::GREAT_BALL)(5));
    Player::getPlayer().addItem<PokeBall>(pokeBalls.at(PokeBall::Id::ULTRA_BALL)(5));
    Player::getPlayer().addItem<PokeBall>(pokeBalls.at(PokeBall::Id::MASTER_BALL)(1));

    Player::getPlayer().addItem<BattleItem>(battleItems.at(BattleItem::Id::X_ATTACK)(5));
    Player::getPlayer().addItem<BattleItem>(battleItems.at(BattleItem::Id::X_DEFENSE)(5));
    Player::getPlayer().addItem<BattleItem>(battleItems.at(BattleItem::Id::X_SP_ATTACK)(5));
    Player::getPlayer().addItem<BattleItem>(battleItems.at(BattleItem::Id::X_SP_DEFENSE)(5));
    Player::getPlayer().addItem<BattleItem>(battleItems.at(BattleItem::Id::X_SPEED)(5));
    Player::getPlayer().addItem<BattleItem>(battleItems.at(BattleItem::Id::X_ACCURACY)(5));

    this->currentMapIndex = Map::Id::NUVEMA_TOWN;
    this->currentMap = &this->maps.at(this->currentMapIndex);
}

void Game::loadData() {
    std::ifstream saveFile("../docs/data/SaveData.txt");

    Map::loadTextures();

    this->maps[Map::Id::NUVEMA_TOWN].addTrainer("Cheren", 8, 8, Direction::DOWN, 3);
    this->maps[Map::Id::NUVEMA_TOWN][0].setDialogue({ "Press ENTER to see the next message.", "Great job!" });
    this->maps[Map::Id::NUVEMA_TOWN][0].setAction(defaultAction);
    this->maps[Map::Id::NUVEMA_TOWN][0].addPokemon(pokemonMap.at(Pokemon::Id::SAMUROTT)());
    this->maps[Map::Id::NUVEMA_TOWN].addTrainer("Bianca", 5, 6, Direction::DOWN, 3);
    this->maps[Map::Id::NUVEMA_TOWN][1].setDialogue(
            {
                    "Hmm... you look pretty tough...",
                    "This calls for a battle!",
                    "Prepare yourself!"
            }
    );
    this->maps[Map::Id::NUVEMA_TOWN][1].setAction(defaultAction);
    this->maps[Map::Id::NUVEMA_TOWN][1].addPokemon(pokemonMap.at(Pokemon::Id::SERPERIOR)());

    if (saveFile) {
        std::string buffer;

        // load the current map
        std::getline(saveFile, buffer);
        this->currentMapIndex = buffer[0] - '0';
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

            // sets the Pokémon's gender
            std::getline(saveFile, buffer, ' ');
            Player::getPlayer()[pokemon].setGender(static_cast<Pokemon::Gender>(std::stoi(buffer)));

            // sets the Pokémon's ability
            std::getline(saveFile, buffer, ' ');
            // TODO eventually remove try-catch
            try {
                Player::getPlayer()[pokemon].setAbility(abilityMap.at(static_cast<Ability::Id>(std::stoi(buffer)))());
            }
            catch (const std::exception &e) {
                std::clog << "Error adding Ability: " << e.what() << '\n';
                Player::getPlayer()[pokemon].setAbility(nullptr);
            }

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

            Player::getPlayer().addItem<RestoreItem>(restoreItems.at(item)(quantity));
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

            Player::getPlayer().addItem<StatusItem>(statusItems.at(item)(quantity));
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

            Player::getPlayer().addItem<PokeBall>(pokeBalls.at(item)(quantity));
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

            Player::getPlayer().addItem<BattleItem>(battleItems.at(item)(quantity));
        }

        std::stringstream ss;
        // load each trainer's data for every map
        while (std::getline(saveFile, buffer)) {
            ss << buffer;

            // grabs the map
            std::getline(ss, buffer, ' ');
            const std::size_t map = std::stoull(buffer);

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

            // Clear the string stream and reset its state
            ss.str().clear();
            ss.clear();
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

bool Game::isRunning() const {
    return this->running;
}

void Game::setRenderColor(SDL_Color color) {
    SDL_SetRenderDrawColor(this->renderer, color.r, color.g, color.b, color.a);
}

void Game::setState(State::Id id) {
    this->currentState = id;
}

int Game::getScrollSpeed() const {
    return this->SCROLL_SPEED;
}

int Game::getWindowWidth() const {
    return this->WINDOW_WIDTH;
}

int Game::getWindowHeight() const {
    return this->WINDOW_HEIGHT;
}

int Game::getFontSize() const {
    return this->FONT_SIZE;
}

TTF_Font *Game::getFont() const {
    return this->font;
}

void Game::changeMap(std::size_t index) {
    this->currentMapIndex = index;
    this->currentMap = &this->maps.at(this->currentMapIndex);
}

Map *Game::getCurrentMap() const {
    return this->currentMap;
}
