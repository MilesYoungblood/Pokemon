//
// Created by Miles on 1/28/2024.
//

#include "../../../Game/Game.h"
#include "Overworld.h"

void defaultAction(Entity *entity) {
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
                entity->setState(Entity::State::WALKING);

                if (entity->hasVisionOf(&Player::getPlayer()) and
                    (Player::getPlayer().getState() == Entity::State::IDLE)) {
                    Player::getPlayer().setState(Entity::State::FROZEN);
                }
            }
            else {
                entity->setState(Entity::State::COLLIDING);
                entity->updateAnimation();
            }
            break;
        default:
            break;
    }
}

void Overworld::init() {
    // default values for player
    Player::getPlayer().init("Hilbert", 7, 17, Direction::DOWN);

    Player::getPlayer().addPokemon(pokemonMap.at(Pokemon::Id::EMBOAR)());
    Player::getPlayer()[0].addMove(moveMap.at(Move::Id::FLAMETHROWER)());

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

void Overworld::update() {
    Player::getPlayer().update();

    for (auto &trainer : *this->currentMap) {
        trainer.update();
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

    std::ifstream saveFile("../docs/data/SaveData.txt");

    this->maps[Map::Id::NUVEMA_TOWN].addTrainer(Entity::Id::YOUNGSTER, "Cheren", 12, 7, Direction::DOWN, 3);
    this->maps[Map::Id::NUVEMA_TOWN][0].setDialogue({ "Press ENTER to see the next message.", "Great job!" });
    this->maps[Map::Id::NUVEMA_TOWN][0].setAction(defaultAction);
    this->maps[Map::Id::NUVEMA_TOWN][0].addPokemon(pokemonMap.at(Pokemon::Id::SAMUROTT)());
    this->maps[Map::Id::NUVEMA_TOWN].addTrainer(Entity::Id::YOUNGSTER, "Bianca", 18, 16, Direction::DOWN, 3);
    this->maps[Map::Id::NUVEMA_TOWN][1].setDialogue(
            {
                    "Hmm... you look pretty tough...",
                    "This calls for a battle!",
                    "Prepare yourself!"
            }
    );
    this->maps[Map::Id::NUVEMA_TOWN][1].setAction(defaultAction);
    this->maps[Map::Id::NUVEMA_TOWN][1].addPokemon(pokemonMap.at(Pokemon::Id::SERPERIOR)());

    this->maps[Map::Id::NUVEMA_TOWN].addItem<PokeBall>(std::make_pair(7, 18), 0);

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
        this->init();
    }

    Entity::init();
    Map::init();

    loaded = true;
}

void Overworld::save() {
    std::ofstream saveFile("../docs/data/SaveData.txt");
    if (not saveFile.is_open()) {
        std::clog << "Unable to open \"SaveData.txt\"\n";
        Game::getInstance().terminate();
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

void Overworld::changeMap(const std::tuple<int, int, Map::Id> &data) {
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

    // move the new map into the current map variable
    this->currentMapIndex = std::get<2>(data);
    this->currentMap = &this->maps.at(this->currentMapIndex);

    // resets the states of these variables for each trainer
    for (auto &trainer : *this->currentMap) {
        keepLooping[&trainer] = true;
    }

    Player::getPlayer().setCoordinates(std::get<0>(data), std::get<1>(data));

    Camera::getInstance().lockOnPlayer(this->currentMap);
}

Map *Overworld::getCurrentMap() const {
    return this->currentMap;
}

int Overworld::getScrollSpeed() const {
    return this->scrollSpeed;
}

void Overworld::createTextBox(const std::vector<std::string> &messages) {
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
    GraphicsEngine::getInstance().getGraphic<TextBox>().setFinishedCallback([] -> void {
        KeyManager::getInstance().unlockKey(SDL_Scancode::SDL_SCANCODE_RETURN);
    });

    GraphicsEngine::getInstance().getGraphic<TextBox>().push(messages);
}

void Overworld::handleMove(SDL_Scancode scancode) {
    static const std::unordered_map<SDL_Scancode, Direction> direction_to_key{
            std::make_pair(SDL_Scancode::SDL_SCANCODE_W, Direction::UP),
            std::make_pair(SDL_Scancode::SDL_SCANCODE_A, Direction::LEFT),
            std::make_pair(SDL_Scancode::SDL_SCANCODE_S, Direction::DOWN),
            std::make_pair(SDL_Scancode::SDL_SCANCODE_D, Direction::RIGHT)
    };

    if (not GraphicsEngine::getInstance().hasAny<Rectangle>()) {
        if (not Player::getPlayer().isFacing(direction_to_key.at(scancode))) {
            Player::getPlayer().setDirection(direction_to_key.at(scancode));
        }
        if (KeyManager::getInstance().getKey(scancode) and (momentum or keyDelay >= 10)) {
            momentum = true;
            keyDelay.stop();
            keyDelay.reset();

            if (Player::getPlayer().canMoveForward(this->currentMap)) {
                Player::getPlayer().moveForward();
                Player::getPlayer().setState(Entity::State::WALKING);
            }
            else {
                Player::getPlayer().setState(Entity::State::COLLIDING);
                Player::getPlayer().updateAnimation();

                Mixer::getInstance().playSound("bump");
            }
        }
    }
}

void Overworld::handleReturn() {
    for (auto &trainer : *this->currentMap) {
        if (Player::getPlayer().hasVisionOf(&trainer)) {
            // if the player manually clicked Enter
            if (not GraphicsEngine::getInstance().hasAny<TextBox>()) {
                Player::getPlayer().setState(Entity::State::FROZEN);
                trainer.face(&Player::getPlayer());

                // only create the textbox here if the trainer cannot fight;
                // the program will loop back to checkForOpponents() in the next cycle
                // and create it there if the trainer can fight
                if (not trainer.canFight()) {
                    trainer.setState(Entity::State::FROZEN);
                    Overworld::createTextBox(trainer.getDialogue());
                }
            }
            else if (not GraphicsEngine::getInstance().getGraphic<TextBox>().isPrinting()) {
                // if the textbox still has messages to print
                if (not GraphicsEngine::getInstance().getGraphic<TextBox>().empty()) {
                    GraphicsEngine::getInstance().getGraphic<TextBox>().pop();

                    if (not GraphicsEngine::getInstance().getGraphic<TextBox>().empty()) {
                        Mixer::getInstance().playSound("accept");
                    }
                }
                if (GraphicsEngine::getInstance().getGraphic<TextBox>().empty()) {
                    GraphicsEngine::getInstance().removeGraphic<TextBox>();

                    if (trainer.canFight()) {
                        Game::getInstance().setState(State::Id::BATTLE);
                        Game::getInstance().setRenderColor(Constants::Color::WHITE);

                        State::getInstance<BattlePhase>().init(&trainer);

                        Mixer::getInstance().playMusic("TrainerBattle");
                    }
                    else {
                        Player::getPlayer().setState(Entity::State::IDLE);
                        trainer.setState(Entity::State::IDLE);
                    }
                }
                // re-lock the Enter key
                KeyManager::getInstance().lockKey(SDL_Scancode::SDL_SCANCODE_RETURN);

                // sets a cool-down period before the Enter key can be registered again;
                // this is needed because the program will register a button as
                // being pressed faster than the user can lift their finger
                std::thread coolDown([] -> void {
                    std::this_thread::sleep_for(std::chrono::milliseconds(500));
                    KeyManager::getInstance().unlockKey(SDL_Scancode::SDL_SCANCODE_RETURN);
                });
                coolDown.detach();

                keyDelay.reset();
                return;
            }
        }
    }
}
