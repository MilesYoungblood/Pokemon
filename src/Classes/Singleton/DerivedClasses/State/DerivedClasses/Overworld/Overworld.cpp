//
// Created by Miles on 1/28/2024.
//

#include "../../../Game/Game.h"
#include "Overworld.h"

void defaultAction(Character *entity) {
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
        case 3:
            if (entity->canMoveForward(State::getInstance<Overworld>().getCurrentMap())) {
                entity->moveForward();
                entity->setState(Character::State::WALKING);

                if (entity->hasVisionOf(&Player::getPlayer()) and
                    (Player::getPlayer().getState() == Character::State::IDLE)) {
                    Player::getPlayer().setState(Character::State::IMMOBILE);
                }
            }
            else {
                entity->setState(Character::State::COLLIDING);
                entity->updateAnimation();
            }
            break;
        default:
            break;
    }
}

void Overworld::init() {
    // default values for player
    Player::getPlayer().setName("Hilbert");

    Player::getPlayer().addPokemon(Pokemon::Id::EMBOAR);
    Player::getPlayer()[0].addMove("Heat Crash");

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
}

Overworld::~Overworld() {
    delete this->currentMap;
}

void Overworld::update() {
    Player::getPlayer().update();

    for (auto &entity : *this->currentMap) {
        entity->update();
    }

    GraphicsEngine::getInstance().update();
}

void Overworld::render() {
    this->currentMap->render();
    GraphicsEngine::getInstance().render();
}

void Overworld::load() {
    // only allow loading once
    static bool loaded = false;
    if (loaded) {
        return;
    }

    std::vector<std::unique_ptr<Move>> moves;
    moves.push_back(std::move(moveMap.at("Dark Pulse")()));
    moves.push_back(std::move(moveMap.at("Dragon Pulse")()));
    moves.push_back(std::move(moveMap.at("Flamethrower")()));
    moves.push_back(std::move(moveMap.at("Focus Blast")()));

    this->currentMap = new Map("Nuvema Town");

    {
        std::unique_ptr<Trainer> trainer = std::make_unique<Trainer>("Youngster", "Cheren", 12, 7, Direction::DOWN, 3);
        trainer->addPokemon(Pokemon::Id::SAMUROTT);
        trainer->setDialogue({ "Press ENTER to see the next message.", "Great job!" });
        trainer->setAction(defaultAction);

        this->currentMap->addEntity(std::move(trainer));
    }
    {
        std::unique_ptr<Trainer> trainer = std::make_unique<Trainer>("Youngster", "Bianca", 18, 16, Direction::DOWN, 3);
        trainer->addPokemon(pokemonMap.at(Pokemon::Id::SERPERIOR)());
        trainer->setDialogue(
                {
                        "Hmm... you look pretty tough...",
                        "This calls for a battle!",
                        "Prepare yourself!"
                }
        );
        trainer->setAction(defaultAction);

        this->currentMap->addEntity(std::move(trainer));
    }

    std::unique_ptr<PokeBall> pokeBall = std::make_unique<PokeBall>(5, 7, 18);
    this->currentMap->addEntity(std::move(pokeBall));

    std::ifstream saveFile("../assets/data/SaveData.txt");

    if (saveFile) {
        std::string buffer;

        // load the current map
        std::getline(saveFile, buffer);
        this->currentMap = new Map(buffer.c_str());

        // grab the player's x-coordinates
        std::getline(saveFile, buffer, ' ');
        const int player_x = std::stoi(buffer);

        // grab the player's y-coordinates
        std::getline(saveFile, buffer, ' ');
        const int player_y = std::stoi(buffer);

        // grab the player's direction
        std::getline(saveFile, buffer);

        //TODO load player name dynamically
        Player::getPlayer().setName("Hilbert");
        Player::getPlayer().setCoordinates(player_x, player_y);
        Player::getPlayer().setDirection(static_cast<Direction>(buffer[0] - '0'));

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

                //Player::getPlayer()[pokemon].addMove(moveMap.at(static_cast<Move::Id>(id))());
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
            //const int trainer = std::stoi(buffer);

            // grabs the trainer's party size
            std::getline(ss, buffer);
            if (buffer[0] == '0') {
                // deletes the Pokémon set if the trainer has been defeated
                // FIXME change to adding Pokémon if not defeated
                //this->maps.at(map)[trainer].clearParty();
            }

            //this->maps.at(map)[trainer].setDirection(static_cast<Direction>(buffer[1] - '0'));

            // Clear the string stream and reset its state
            ss.str().clear();
            ss.clear();
        }

        saveFile.close();
    }
    else {
        this->init();
    }

    Character::init();
    Item::init();
    Map::init();

    loaded = true;
}

void Overworld::save() {
    std::ofstream saveFile("../assets/data/SaveData.txt");
    if (not saveFile.is_open()) {
        std::clog << "Unable to open \"SaveData.txt\"\n";
        Game::getInstance().terminate();
        return;
    }

    saveFile << this->currentMapId;
    saveFile << '\n' << Player::getPlayer().getMapX() << ' ' << Player::getPlayer().getMapY() << ' '
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
            //saveFile << move->getId() << ' ' << move->getPp() << ' ' << move->getMaxPp() << ' ';
        }
    }

    const std::size_t num_restore_items = Player::getPlayer().getNumItems<RestoreItem>();
    const std::size_t num_status_items = Player::getPlayer().getNumItems<StatusItem>();
    const std::size_t num_poke_balls = Player::getPlayer().getNumItems<PokeBall>();
    const std::size_t num_battle_items = Player::getPlayer().getNumItems<BattleItem>();

    saveFile << '\n' << num_restore_items;

    RestoreItem *restoreItem;
    for (std::size_t i = 0; i < num_restore_items; ++i) {
        restoreItem = &Player::getPlayer().getItem<RestoreItem>(i);
        saveFile << '\n' << static_cast<int>(restoreItem->getId()) << ' ' << restoreItem->getQuantity();
    }

    saveFile << '\n' << num_status_items;

    StatusItem *statusItem;
    for (std::size_t i = 0; i < num_status_items; ++i) {
        statusItem = &Player::getPlayer().getItem<StatusItem>(i);
        saveFile << '\n' << static_cast<int>(statusItem->getId()) << ' ' << statusItem->getQuantity();
    }

    saveFile << '\n' << num_poke_balls;

    PokeBall *pokeBall;
    for (std::size_t i = 0; i < num_poke_balls; ++i) {
        pokeBall = &Player::getPlayer().getItem<PokeBall>(i);
        saveFile << '\n' << static_cast<int>(pokeBall->getId()) << ' ' << pokeBall->getQuantity();
    }

    saveFile << '\n' << num_battle_items;

    BattleItem *battleItem;
    for (std::size_t i = 0; i < num_battle_items; ++i) {
        battleItem = &Player::getPlayer().getItem<BattleItem>(i);
        saveFile << '\n' << static_cast<int>(battleItem->getId()) << ' ' << battleItem->getQuantity();
    }

    /*
    for (std::size_t map = 0; map < this->maps.size(); ++map) {
        for (std::size_t trainer = 0; trainer < this->maps.at(map).numTrainers(); ++trainer) {
            saveFile << '\n' << map << ' ' << trainer << ' ' << this->maps.at(map)[trainer].partySize();
            saveFile << static_cast<int>(this->maps.at(map)[trainer].getDirection());
        }
    }
     */

    saveFile.close();
}

void Overworld::changeMap(const std::tuple<int, int, std::string> &data) {
    if (Mix_FadeOutMusic(2000) == 0) {
        std::clog << "Error fading out \"" << this->currentMap->getMusic() << "\": "
                  << SDL_GetError() << '\n';
        SDL_ClearError();
        Game::getInstance().terminate();
        return;
    }

    Mix_HookMusicFinished([] -> void {
        Mixer::getInstance().playMusic(State::getInstance<Overworld>().currentMap->getMusic());
    });

    this->currentMap->reset();

    // resets the states of these variables for each trainer
    for (auto &entity : *this->currentMap) {
        keepLooping[entity.get()] = true;
    }

    // move the new map into the current map variable
    this->currentMapId = std::get<2>(data);
    delete this->currentMap;
    this->currentMap = new Map(this->currentMapId.c_str());

    Player::getPlayer().setCoordinates(std::get<0>(data), std::get<1>(data));

    Camera::getInstance().lockOnPlayer(this->currentMap);
}

gsl::owner<Map *> Overworld::getCurrentMap() const {
    return this->currentMap;
}

int Overworld::getScrollSpeed() const {
    return this->scrollSpeed;
}

void Overworld::createTextBox(const std::vector<std::string> &dialogue) {
    const int box_width = Map::TILE_SIZE * 7;
    const int box_height = Map::TILE_SIZE * 2;
    const SDL_Rect rect(
            Game::WINDOW_WIDTH / 2 - box_width / 2,
            Game::WINDOW_HEIGHT - box_height,
            box_width,
            box_height - Map::TILE_SIZE / 2
    );

    GraphicsEngine::getInstance().addGraphic<TextBox>(
            rect,
            rect.h / (Map::TILE_SIZE * 3 / 10),
            rect.x + Map::TILE_SIZE / 10,
            rect.y + Map::TILE_SIZE / 10
    );

    const std::function<void()> callback = [] -> void {
        KeyManager::getInstance().unlockKey(SDL_Scancode::SDL_SCANCODE_RETURN);
    };
    GraphicsEngine::getInstance().getGraphic<TextBox>().push(
            dialogue,
            std::vector<std::function<void()>>({ callback, callback, callback })
    );
}

/// \brief converts a SDL_Scancode to a Direction
/// \param scancode the scancode to convert
/// \return the corresponding Direction
Direction scancodeToDirection(SDL_Scancode scancode) {
    switch (scancode) {
        case SDL_Scancode::SDL_SCANCODE_W:
            return Direction::UP;
        case SDL_Scancode::SDL_SCANCODE_A:
            return Direction::LEFT;
        case SDL_Scancode::SDL_SCANCODE_S:
            return Direction::DOWN;
        case SDL_Scancode::SDL_SCANCODE_D:
            return Direction::RIGHT;
        default:
            throw std::invalid_argument("Invalid argument passed into scancodeToDirection");
    }
}

void Overworld::handleMove(SDL_Scancode scancode) {
    if (not GraphicsEngine::getInstance().hasAny<SelectionBox>()) {
        // turns the player
        if (not Player::getPlayer().isFacing(scancodeToDirection(scancode))) {
            Player::getPlayer().setDirection(scancodeToDirection(scancode));
        }
        // if the user is still holding down the key after 10ms, begin movement
        if (KeyManager::getInstance().getKey(scancode) and (momentum or keyDelay >= 10)) {
            momentum = true;
            keyDelay.stop();
            keyDelay.reset();

            if (Player::getPlayer().canMoveForward(this->currentMap)) {
                Player::getPlayer().moveForward();
                Player::getPlayer().setState(Character::State::WALKING);
            }
            else {
                Player::getPlayer().setState(Character::State::COLLIDING);
                Player::getPlayer().updateAnimation();

                Mixer::getInstance().playSound("bump");
            }
        }
    }
}

void Overworld::handleReturn() {
    for (auto &entity : *this->currentMap) {
        if (Player::getPlayer().hasVisionOf(entity.get())) {
            entity->interact();
            return;
        }
    }
}
