//
// Created by Miles Youngblood on 7/10/2023.
//

#include "../Singleton/DerivedClasses/Game/Game.h"
#include "../Singleton/DerivedClasses/Camera/Camera.h"
#include "Map.h"

std::string errorMessage(const std::string &filename, const char *name, const char *type) {
    const bool is_tmx = filename.substr(filename.size() - 5) == ".tmx";
    return "Invalid " + std::string(is_tmx ? "TMX" : "TSX") + " file \"" + filename + "\": missing \"" + name + "\" " + type + '\n';
}

void Map::parseTmx() {
    tinyxml2::XMLDocument tmxFile;
    if (tmxFile.LoadFile(std::string_view("../assets/Tiled/Tilemaps/" + this->music + ".tmx").data()) != tinyxml2::XMLError::XML_SUCCESS) {
        tmxFile.PrintError();
        std::terminate();
    }

    const tinyxml2::XMLElement *mapElement = tmxFile.FirstChildElement("map");
    if (mapElement == nullptr) {
        throw std::runtime_error(errorMessage(this->music + ".tmx", "map", "element"));
    }

    const int width = mapElement->IntAttribute("width");
    if (width == 0) {
        throw std::runtime_error(errorMessage(this->music + ".tmx", "width", "attribute"));
    }
    const int height = mapElement->IntAttribute("height");
    if (height == 0) {
        throw std::runtime_error(errorMessage(this->music + ".tmx", "height", "attribute"));
    }

    const tinyxml2::XMLElement *tilesetElement = mapElement->FirstChildElement("tileset");
    if (tilesetElement == nullptr) {
        throw std::runtime_error(errorMessage(this->music + ".tmx", "tileset", "element"));
    }

    // populate the maps with keys being the firstgid, and open each tsx file in the map
    while (tilesetElement != nullptr) {
        const std::string source_attribute(tilesetElement->Attribute("source"));
        if (source_attribute.empty()) {
            throw std::runtime_error(errorMessage(this->music + ".tmx", "source", "attribute"));
        }

        this->parseTsx(source_attribute);

        tilesetElement = tilesetElement->NextSiblingElement("tileset");
    }

    this->populate(mapElement, width, height);
}

void Map::parseTsx(const std::string &sourceAttribute) {
    tinyxml2::XMLDocument tsxFile;
    if (tsxFile.LoadFile(std::string("../assets/Tiled/Tilesets/" + sourceAttribute).c_str()) != tinyxml2::XMLError::XML_SUCCESS) {
        tsxFile.PrintError();
        std::terminate();
    }

    tinyxml2::XMLElement *tsElement = tsxFile.FirstChildElement("tileset");
    if (tsElement == nullptr) {
        throw std::runtime_error(errorMessage(sourceAttribute, "tileset", "element"));
    }

    const int tile_count = tsElement->IntAttribute("tilecount", -1);
    if (tile_count == -1) {
        throw std::runtime_error(errorMessage(sourceAttribute, "tilecount", "attribute"));
    }

    this->collision.reserve(tile_count);
    this->textures.reserve(tile_count);

    tinyxml2::XMLElement *gridElement = tsElement->FirstChildElement("grid");
    if (gridElement == nullptr) {
        throw std::runtime_error(errorMessage(sourceAttribute, "grid", "element"));
    }

    for (tinyxml2::XMLElement *tileElement = gridElement->NextSiblingElement("tile");
         tileElement != nullptr; tileElement = tileElement->NextSiblingElement("tile")) {
        const int id = tileElement->IntAttribute("id", -1);
        if (id == -1) {
            throw std::runtime_error(errorMessage(sourceAttribute, "id", "attribute"));
        }

        tinyxml2::XMLElement *propertyListElement = tileElement->FirstChildElement("properties");
        if (propertyListElement == nullptr) {
            throw std::runtime_error(errorMessage(sourceAttribute, "properties", "element"));
        }

        tinyxml2::XMLElement *propertyElement = propertyListElement->FirstChildElement("property");
        if (propertyElement == nullptr) {
            throw std::runtime_error(errorMessage(sourceAttribute, "property", "element"));
        }

        this->collision.push_back(propertyElement->BoolAttribute("value"));

        tinyxml2::XMLElement *imageElement = propertyListElement->NextSiblingElement("image");
        if (imageElement == nullptr) {
            throw std::runtime_error(errorMessage(sourceAttribute, "image", "element"));
        }

        std::string copy(imageElement->Attribute("source"));
        if (copy.empty()) {
            throw std::runtime_error(errorMessage(sourceAttribute, "source", "attribute"));
        }

        // strip off unnecessary characters
        copy.erase(0, 21);
        copy.erase(copy.size() - 4);

        this->textures.push_back(TextureManager::getInstance().loadTexture("terrain/" + copy + ".png"));
        if (this->textures.end().base() == nullptr) {
            throw std::runtime_error("Error loading texture at \"" + copy + "\"\n");
        }
    }
}

void Map::populate(const tinyxml2::XMLElement *mapElement, int width, int height) {
    const tinyxml2::XMLElement *layerElement = mapElement->FirstChildElement("layer");
    if (layerElement == nullptr) {
        throw std::runtime_error(errorMessage(music + ".tmx", "layer", "element"));
    }

    while (layerElement != nullptr) {
        const int id_attribute = layerElement->IntAttribute("id");
        if (id_attribute == 0) {
            throw std::runtime_error(errorMessage(music + ".tmx", "id", "attribute"));
        }

        const tinyxml2::XMLElement *dataElement = layerElement->FirstChildElement("data");
        if (dataElement == nullptr) {
            throw std::runtime_error(errorMessage(music + ".tmx", "data", "element"));
        }

        const char *csvData = dataElement->GetText();
        if (csvData == nullptr) {
            throw std::runtime_error(errorMessage(music + ".tmx", "data", "text"));
        }

        std::istringstream ss(csvData);
        layer layer(height, std::vector<tile>(width));
        int value;
        for (int row = 0; row < height; ++row) {
            for (int col = 0; col < width and ss >> value; ++col) {
                layer[row][col].id = value;
                layer[row][col].screenX = col * Map::TILE_SIZE;
                layer[row][col].screenY = row * Map::TILE_SIZE;
                if (ss.peek() == ',') {
                    ss.ignore();
                }
            }
        }

        this->layout.push_back(layer);
        layerElement = layerElement->NextSiblingElement("layer");
    }
}

void Map::loadEntities() {
    tinyxml2::XMLDocument xmlFile;
    // first try to load from temp files
    // this means that the Player has been to this switched from this map this session
    if (xmlFile.LoadFile(std::string("../assets/data/Map/temp/" + this->music + ".xml").data()) != tinyxml2::XMLError::XML_SUCCESS) {
        // then try to load from backup files;
        // this is the first time the Player has been to this map this session
        if (xmlFile.LoadFile(std::string_view("../assets/data/Map/backup/" + this->music + ".xml").data()) !=
            tinyxml2::XMLError::XML_SUCCESS) {
            // this will only be reached if there is no new save data for this map
            if (xmlFile.LoadFile(std::string_view("../assets/data/Map/initial/" + this->music + ".xml").data()) !=
                tinyxml2::XMLError::XML_SUCCESS) {
                xmlFile.PrintError();
                std::terminate();
            }
        }
    }

    tinyxml2::XMLElement *xmlElement = xmlFile.FirstChildElement("xml");
    if (xmlElement == nullptr) {
        throw std::runtime_error(errorMessage(this->music + ".xml", "xml", "element"));
    }

    tinyxml2::XMLElement *entityListElement = xmlElement->FirstChildElement("entities");
    if (entityListElement == nullptr) {
        throw std::runtime_error(errorMessage(this->music + ".xml", "entities", "element"));
    }

    for (tinyxml2::XMLElement *entityElement = entityListElement->FirstChildElement("entity"); entityElement != nullptr;
         entityElement = entityElement->NextSiblingElement("entity")) {
        const char *classAttribute = entityElement->Attribute("class");
        if (classAttribute == nullptr) {
            throw std::runtime_error(errorMessage(this->music + ".xml", "class", "attribute"));
        }

        if (strcmp(classAttribute, "Trainer") == 0) {
            this->loadTrainer1(entityElement);
        }
        else if (strcmp(classAttribute, "Item") == 0) {
            this->loadItem(entityElement);
        }
    }
}

void Map::loadTrainer1(tinyxml2::XMLElement *entityElement) {
    const char *idAttribute = entityElement->Attribute("id");
    if (idAttribute == nullptr) {
        throw std::runtime_error(errorMessage(this->music + ".xml", "id", "attribute"));
    }

    tinyxml2::XMLElement *nameElement = entityElement->FirstChildElement("name");
    if (nameElement == nullptr) {
        throw std::runtime_error(errorMessage(this->music + ".xml", "name", "element"));
    }

    const char *trainerName = nameElement->GetText();
    if (trainerName == nullptr) {
        throw std::runtime_error(errorMessage(this->music + ".xml", "name", "text"));
    }

    tinyxml2::XMLElement *positionElement = nameElement->NextSiblingElement("position");
    if (positionElement == nullptr) {
        throw std::runtime_error(errorMessage(this->music + ".xml", "position", "element"));
    }

    const int x_pos = positionElement->IntAttribute("x", -1);
    if (x_pos == -1) {
        throw std::runtime_error(errorMessage(this->music + ".xml", "x", "attribute"));
    }

    const int y_pos = positionElement->IntAttribute("y", -1);
    if (y_pos == -1) {
        throw std::runtime_error(errorMessage(this->music + ".xml", "y", "attribute"));
    }

    tinyxml2::XMLElement *directionElement = positionElement->NextSiblingElement("direction");
    if (directionElement == nullptr) {
        throw std::runtime_error(errorMessage(this->music + ".xml", "direction", "element"));
    }

    const int trainer_direction = directionElement->IntText(-1);
    if (trainer_direction == -1) {
        throw std::runtime_error(errorMessage(this->music + ".xml", "direction", "text"));
    }

    tinyxml2::XMLElement *visionElement = directionElement->NextSiblingElement("vision");
    if (visionElement == nullptr) {
        throw std::runtime_error(errorMessage(this->music + ".xml", "vision", "element"));
    }

    const int trainer_vision = visionElement->IntText(-1);
    if (trainer_vision == -1) {
        throw std::runtime_error(errorMessage(this->music + ".xml", "vision", "text"));
    }

    std::unique_ptr<Trainer> trainer(std::make_unique<Trainer>(idAttribute, trainerName, x_pos, y_pos, Direction(trainer_direction), trainer_vision));
    this->loadTrainer2(trainer, visionElement);
}

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

void Map::loadTrainer2(std::unique_ptr<Trainer> &trainer, tinyxml2::XMLElement *visionElement) {
    tinyxml2::XMLElement *dialogueListElement = visionElement->NextSiblingElement("dialogue");
    if (dialogueListElement == nullptr) {
        throw std::runtime_error(errorMessage(this->music + ".xml", "dialogue", "element"));
    }

    std::vector<std::string> messages;
    messages.reserve(dialogueListElement->ChildElementCount());

    for (tinyxml2::XMLElement *messageElement = dialogueListElement->FirstChildElement("message"); messageElement != nullptr;
         messageElement = messageElement->NextSiblingElement("message")) {
        const char *message = messageElement->GetText();
        if (message != nullptr) {
            messages.emplace_back(message);
        }
    }

    trainer->setDialogue(messages);

    tinyxml2::XMLElement *partyElement = dialogueListElement->NextSiblingElement("party");
    if (partyElement == nullptr) {
        throw std::runtime_error(errorMessage(this->music + ".xml", "party", "element"));
    }
    if (partyElement->ChildElementCount() == 0) {
        std::clog << "Invalid file format in file " << this->music << ".xml" << ": Trainer \"" << trainer->getName() << " must have at least 1 Pokemon\n";
        std::terminate();
    }

    for (tinyxml2::XMLElement *pokemonElement = partyElement->FirstChildElement("pokemon"); pokemonElement != nullptr;
         pokemonElement = pokemonElement->NextSiblingElement("pokemon")) {
        const char *idAttribute = pokemonElement->Attribute("id");
        if (idAttribute == nullptr) {
            throw std::runtime_error(errorMessage(this->music + ".xml", "id", "attribute"));
        }

        tinyxml2::XMLElement *moveSetElement = pokemonElement->FirstChildElement("move_set");
        if (moveSetElement == nullptr) {
            throw std::runtime_error(errorMessage(this->music + ".xml", "move_set", "element"));
        }

        if (moveSetElement->ChildElementCount() == 0) {
            std::clog << "Invalid file format in file " << this->music << ".xml" << ": Pokemon \"" << idAttribute << " must have at least 1 Move\n";
            std::terminate();
        }

        std::unique_ptr<Pokemon> pokemon(pokemonMap.at(idAttribute)());

        for (tinyxml2::XMLElement *moveElement = moveSetElement->FirstChildElement("move"); moveElement != nullptr;
             moveElement = moveElement->NextSiblingElement("move")) {
            const char *moveIdAttribute = moveElement->Attribute("id");
            if (moveIdAttribute == nullptr) {
                throw std::runtime_error(errorMessage(this->music + ".xml", "id", "attribute"));
            }

            pokemon->addMove(moveIdAttribute);
        }

        trainer->addPokemon(std::move(pokemon));
    }

    trainer->setAction(defaultAction);

    this->entities.push_back(std::move(trainer));
}

void Map::loadItem(tinyxml2::XMLElement *entityElement) {
    const char *idAttribute = entityElement->Attribute("id");
    if (idAttribute == nullptr) {
        throw std::runtime_error(errorMessage(this->music + ".xml", "id", "attribute"));
    }

    tinyxml2::XMLElement *quantityElement = entityElement->FirstChildElement("quantity");
    if (quantityElement == nullptr) {
        throw std::runtime_error(errorMessage(this->music + ".xml", "quantity", "element"));
    }

    const int quantity = quantityElement->IntText(-1);
    if (quantity == -1) {
        throw std::runtime_error(errorMessage(this->music + ".xml", "quantity", "text"));
    }

    tinyxml2::XMLElement *positionElement = quantityElement->NextSiblingElement("position");
    if (positionElement == nullptr) {
        throw std::runtime_error(errorMessage(this->music + ".xml", "position", "element"));
    }

    const int x_pos = positionElement->IntAttribute("x", -1);
    if (x_pos == -1) {
        throw std::runtime_error(errorMessage(this->music + ".xml", "x", "attribute"));
    }

    const int y_pos = positionElement->IntAttribute("y", -1);
    if (y_pos == -1) {
        throw std::runtime_error(errorMessage(this->music + ".xml", "y", "attribute"));
    }

    std::unique_ptr<Item> item(itemMap.at(idAttribute)(quantity));
    item->setCoordinates(x_pos, y_pos);

    this->entities.push_back(std::move(item));
}

Map::Map(const char *name) : name(name), music(name) {
    this->music.erase(std::remove_if(this->music.begin(), this->music.end(), [](char c) -> bool {
        return c == ' ';
    }), this->music.end());

    this->parseTmx();
    this->loadEntities();
}

Map::~Map() {
    for (auto &texture : this->textures) {
        if (texture != nullptr) {
            SDL_DestroyTexture(texture);
            if (strlen(SDL_GetError()) > 0) {
                std::clog << "Unable to destroy tile texture: " << SDL_GetError() << '\n';
                SDL_ClearError();
            }
        }
    }
}

bool Map::isObstructionHere(int x, int y) const {
    try {
        // No idea why, but the layout MUST be y-position first and x-second
        return this->collision.at(this->layout[1][y][x].id) or (Player::getPlayer().getMapX() == x and Player::getPlayer().getMapY() == y) or std::ranges::any_of(this->entities, [&x, &y](const std::unique_ptr<Entity> &entity) -> bool {
            return entity->getMapX() == x and entity->getMapY() == y;
        });
    }
    catch (const std::exception &e) {
        throw std::runtime_error(std::string("Error accessing map layout: ") + e.what() + '\n');
    }
}

std::optional<std::tuple<int, int, std::string>> Map::isExitPointHere(int x, int y) const {
    for (const ExitPoint &exit_point : this->exitPoints) {
        if (exit_point.x == x and exit_point.y == y) {
            return std::make_optional(std::make_tuple(exit_point.newX, exit_point.newY, exit_point.newMap));
        }
    }
    return std::nullopt;
}

void Map::removeEntity(Entity *entity) {
    for (int i = 0; i < this->entities.size(); ++i) {
        if (this->entities.at(i).get() == entity) {
            this->entities.erase(this->entities.begin() + i);
            return;
        }
    }
}

Entity &Map::operator[](std::size_t index) {
    try {
        return *this->entities.at(index);
    }
    catch (const std::out_of_range &e) {
        throw std::out_of_range(std::string("Error accessing entities: ") + e.what() + '\n');
    }
}

std::vector<std::unique_ptr<Entity>>::iterator Map::begin() {
    return this->entities.begin();
}

std::vector<std::unique_ptr<Entity>>::iterator Map::end() {
    return this->entities.end();
}

std::string Map::getMusic() const {
    return this->music;
}

void Map::shift(Direction direction, int n) {
    std::vector<std::thread> threads;
    threads.reserve(this->layout.size() + 1);

    for (auto &layer : this->layout) {
        threads.emplace_back([&layer, &direction, &n] -> void {
            for (auto &row : layer) {
                for (auto &col : row) {
                    switch (direction) {
                        case Direction::UP:
                            col.screenY -= n;
                            break;
                        case Direction::DOWN:
                            col.screenY += n;
                            break;
                        case Direction::LEFT:
                            col.screenX -= n;
                            break;
                        case Direction::RIGHT:
                            col.screenX += n;
                            break;
                        default:
                            return;
                    }
                }
            }
        });
    }

    threads.emplace_back([this, &direction, &n] -> void {
        for (auto &entity : this->entities) {
            entity->shift(direction, n);
        }
    });

    for (auto &thread : threads) {
        thread.join();
    }
}

void Map::shiftHorizontally(int n) {
    std::vector<std::thread> threads;
    threads.reserve(this->layout.size() + 1);

    for (auto &layer : this->layout) {
        threads.emplace_back([&layer, &n] -> void {
            for (auto &row : layer) {
                for (auto &col : row) {
                    col.screenX += n;
                }
            }
        });
    }

    threads.emplace_back([this, &n] -> void {
        for (auto &entity : this->entities) {
            entity->shiftHorizontally(n);
        }
    });

    for (auto &thread : threads) {
        thread.join();
    }
}

void Map::shiftVertically(int n) {
    std::vector<std::thread> threads;
    threads.reserve(this->layout.size() + 1);

    for (auto &layer : this->layout) {
        threads.emplace_back([&layer, &n] -> void {
            for (auto &row : layer) {
                for (auto &col : row) {
                    col.screenY += n;
                }
            }
        });
    }

    threads.emplace_back([this, &n] -> void {
        for (auto &entity : this->entities) {
            entity->shiftVertically(n);
        }
    });

    for (auto &thread : threads) {
        thread.join();
    }
}

void Map::render() const {
    SDL_Rect sdlRect(0, 0, Map::TILE_SIZE, Map::TILE_SIZE);

    for (std::size_t layer = 0; layer < this->layout.size(); ++layer) {
        for (const auto &row : this->layout[layer]) {
            for (const auto &col : row) {
                sdlRect.x = col.screenX;
                sdlRect.y = col.screenY;
                // prevents rendering tiles that aren't onscreen
                if (Camera::getInstance().isInView(sdlRect) and col.id != 0) {
                    TextureManager::getInstance().draw(Map::textures.at(col.id), sdlRect);
                }
            }
        }
        if (layer == 1) {
            for (const auto &entity : this->entities) {
                sdlRect.x = entity->getScreenX();
                sdlRect.y = entity->getScreenY();
                // prevents rendering entities that aren't onscreen
                if (Camera::getInstance().isInView(sdlRect)) {
                    entity->render();
                }
            }

            Player::getPlayer().render();
        }
    }
}

void Map::reset() {
    std::vector<std::thread> threads;
    threads.reserve(this->layout.size() + 1);

    for (auto &layer : this->layout) {
        threads.emplace_back([&layer] -> void {
            for (int i = 0; i < layer.size(); ++i) {
                for (int j = 0; j < layer[i].size(); ++j) {
                    layer[i][j].screenX = i * Map::TILE_SIZE;
                    layer[i][j].screenY = j * Map::TILE_SIZE;
                }
            }
        });
    }

    threads.emplace_back([this] -> void {
        for (auto &entity : this->entities) {
            entity->resetPos();
        }
    });

    for (auto &thread : threads) {
        thread.join();
    }
}
