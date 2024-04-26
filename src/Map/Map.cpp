//
// Created by Miles Youngblood on 7/10/2023.
//

#include "../Singleton/Game/Game.h"
#include "../Singleton/TextureManager/TextureManager.h"
#include "../Singleton/Camera/Camera.h"
#include "Map.h"

void handleError(const std::string &filename, const char *name, const char *node) {
    std::clog << "Invalid file format in file \"" << filename << "\": missing \"" << name << "\" " << node << '\n';
    Game::getInstance().terminate();
}

void Map::parseTmx() {
    tinyxml2::XMLDocument tmxFile;
    if (tmxFile.LoadFile(std::string_view("../assets/Tiled/Tilemaps/" + this->id + ".tmx").data()) !=
        tinyxml2::XMLError::XML_SUCCESS) {
        tmxFile.PrintError();
        std::terminate();
    }

    const tinyxml2::XMLElement *mapElement = tmxFile.FirstChildElement("map");
    if (mapElement == nullptr) {
        handleError(this->id + ".tmx", "map", "element");
        return;
    }

    const int width = mapElement->IntAttribute("width");
    if (width == 0) {
        handleError(this->id + ".tmx", "width", "attribute");
        return;
    }
    const int height = mapElement->IntAttribute("height");
    if (height == 0) {
        handleError(this->id + ".tmx", "height", "attribute");
        return;
    }

    const tinyxml2::XMLElement *tilesetElement = mapElement->FirstChildElement("tileset");
    if (tilesetElement == nullptr) {
        handleError(this->id + ".tmx", "tileset", "element");
        return;
    }

    // populate the maps with keys being the firstgid, and open each tsx file in the map
    while (tilesetElement != nullptr) {
        const int firstGidAttribute = tilesetElement->IntAttribute("firstgid", -1);
        if (firstGidAttribute == -1) {
            handleError(this->id + ".tmx", "firstgid", "attribute");
            return;
        }

        const std::string sourceAttribute(tilesetElement->Attribute("source"));
        if (sourceAttribute.empty()) {
            handleError(this->id + ".tmx", "source", "attribute");
            return;
        }

        this->parseTsx(firstGidAttribute, sourceAttribute);

        tilesetElement = tilesetElement->NextSiblingElement("tileset");
    }

    this->populate(mapElement, width, height);
}

void Map::parseTsx(const int firstGidAttribute, const std::string &sourceAttribute) {
    tinyxml2::XMLDocument tsxFile;
    if (tsxFile.LoadFile(std::string("../assets/Tiled/Tilesets/" + sourceAttribute).c_str()) !=
        tinyxml2::XMLError::XML_SUCCESS) {
        tsxFile.PrintError();
        std::terminate();
    }

    tinyxml2::XMLElement *tsElement = tsxFile.FirstChildElement("tileset");
    if (tsElement == nullptr) {
        handleError(sourceAttribute, "tileset", "element");
        return;
    }

    const int tileCount = tsElement->IntAttribute("tilecount", -1);
    if (tileCount == -1) {
        handleError(sourceAttribute, "tilecount", "attribute");
        return;
    }

    this->collisionSet.reserve(tileCount);
    this->tileSprites.reserve(tileCount);

    tinyxml2::XMLElement *gridElement = tsElement->FirstChildElement("grid");
    if (gridElement == nullptr) {
        handleError(sourceAttribute, "grid", "element");
        return;
    }

    for (tinyxml2::XMLElement *tileElement = gridElement->NextSiblingElement("tile");
         tileElement != nullptr; tileElement = tileElement->NextSiblingElement("tile")) {
        const int id = tileElement->IntAttribute("id", -1);
        if (id == -1) {
            handleError(sourceAttribute, "id", "attribute");
            return;
        }

        tinyxml2::XMLElement *propertyListElement = tileElement->FirstChildElement("properties");
        if (propertyListElement == nullptr) {
            handleError(sourceAttribute, "properties", "element");
            return;
        }

        const tinyxml2::XMLElement *propertyElement = propertyListElement->FirstChildElement("property");
        if (propertyElement == nullptr) {
            handleError(sourceAttribute, "property", "element");
            return;
        }

        if (propertyElement->BoolAttribute("value")) {
            this->collisionSet.insert(id + firstGidAttribute);
        }

        const tinyxml2::XMLElement *imageElement = propertyListElement->NextSiblingElement("image");
        if (imageElement == nullptr) {
            handleError(sourceAttribute, "image", "element");
            return;
        }

        std::string copy(imageElement->Attribute("source"));
        if (copy.empty()) {
            handleError(sourceAttribute, "source", "attribute");
            return;
        }

        // strip off unnecessary characters
        copy.erase(0, 21);
        copy.erase(copy.size() - 4);

        this->tileSprites.push_back(TextureManager::getInstance().loadTexture("terrain/" + copy + ".png"));
        if (this->tileSprites.end().base() == nullptr) {
            std::clog << "Error loading texture \"" << copy << "\"\n";
            Game::getInstance().terminate();
        }
    }
}

void Map::populate(const tinyxml2::XMLElement *mapElement, const int width, const int height) {
    for (const tinyxml2::XMLElement *layerElement = mapElement->FirstChildElement("layer");
         layerElement != nullptr; layerElement = layerElement->NextSiblingElement("layer")) {
        if (const int idAttribute = layerElement->IntAttribute("id"); idAttribute == 0) {
            handleError(this->id + ".tmx", "id", "attribute");
            return;
        }
        const tinyxml2::XMLElement *dataElement = layerElement->FirstChildElement("data");
        if (dataElement == nullptr) {
            handleError(this->id + ".tmx", "data", "element");
            return;
        }

        const char *csvData = dataElement->GetText();
        if (csvData == nullptr) {
            handleError(this->id + ".tmx", "data", "text");
            return;
        }

        std::istringstream ss(csvData);
        Matrix<Tile> layer(height, width);
        int value;
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width and ss >> value; ++j) {
                layer(i, j).id = value;
                layer(i, j).screen.setPosition(j * TILE_SIZE, i * TILE_SIZE);
                if (ss.peek() == ',') {
                    ss.ignore();
                }
            }
        }

        this->layers.push_back(layer);
    }
}

void Map::loadEntities() {
    tinyxml2::XMLDocument xmlFile;
    // first try to load from temp files
    // this means that the Player has been to this switched from this map this session
    if (xmlFile.LoadFile(std::string("../assets/data/Map/temp/" + this->id + ".xml").data()) !=
        tinyxml2::XMLError::XML_SUCCESS) {
        // then try to load from backup files;
        // this is the first time the Player has been to this map this session
        if (xmlFile.LoadFile(std::string_view("../assets/data/Map/backup/" + this->id + ".xml").data()) !=
            tinyxml2::XMLError::XML_SUCCESS) {
            // this will only be reached if there is no new save data for this map
            if (xmlFile.LoadFile(std::string_view("../assets/data/Map/initial/" + this->id + ".xml").data()) !=
                tinyxml2::XMLError::XML_SUCCESS) {
                xmlFile.PrintError();
                Game::getInstance().terminate();
                return;
            }
        }
    }

    tinyxml2::XMLElement *xmlElement = xmlFile.FirstChildElement("xml");
    if (xmlElement == nullptr) {
        handleError(this->id + ".xml", "xml", "element");
        return;
    }

    tinyxml2::XMLElement *entityListElement = xmlElement->FirstChildElement("entities");
    if (entityListElement == nullptr) {
        handleError(this->id + ".xml", "entities", "element");
        return;
    }

    for (tinyxml2::XMLElement *entityElement = entityListElement->FirstChildElement("entity"); entityElement != nullptr;
         entityElement = entityElement->NextSiblingElement("entity")) {
        const char *classAttribute = entityElement->Attribute("class");
        if (classAttribute == nullptr) {
            handleError(this->id + ".xml", "class", "attribute");
            return;
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
    const std::string idAttribute(entityElement->Attribute("id"));
    if (idAttribute.empty()) {
        handleError(this->id + ".xml", "id", "attribute");
        return;
    }

    if (not this->entitySprites.contains(idAttribute)) {
        this->entitySprites[idAttribute] = TextureManager::getInstance().loadTexture("sprites/" + idAttribute += idAttribute + "SpriteSheet.png");
        if (entitySprites.at(idAttribute) == nullptr) {
            std::clog << "Unable to load sprite to map\n";
            Game::getInstance().terminate();
            return;
        }
    }

    tinyxml2::XMLElement *nameElement = entityElement->FirstChildElement("name");
    if (nameElement == nullptr) {
        handleError(this->id + ".xml", "name", "element");
        return;
    }

    const char *trainerName = nameElement->GetText();
    if (trainerName == nullptr) {
        handleError(this->id + ".xml", "name", "text");
        return;
    }

    tinyxml2::XMLElement *positionElement = nameElement->NextSiblingElement("position");
    if (positionElement == nullptr) {
        handleError(this->id + ".xml", "position", "element");
        return;
    }

    const int xPos = positionElement->IntAttribute("x", -1);
    if (xPos == -1) {
        handleError(this->id + ".xml", "x", "attribute");
        return;
    }

    const int yPos = positionElement->IntAttribute("y", -1);
    if (yPos == -1) {
        handleError(this->id + ".xml", "y", "attribute");
        return;
    }

    tinyxml2::XMLElement *directionElement = positionElement->NextSiblingElement("direction");
    if (directionElement == nullptr) {
        handleError(this->id + ".xml", "direction", "element");
        return;
    }

    const int trainerDirection = directionElement->IntText(-1);
    if (trainerDirection == -1) {
        handleError(this->id + ".xml", "direction", "text");
        return;
    }

    tinyxml2::XMLElement *visionElement = directionElement->NextSiblingElement("vision");
    if (visionElement == nullptr) {
        handleError(this->id + ".xml", "vision", "element");
        return;
    }

    const int trainerVision = visionElement->IntText(-1);
    if (trainerVision == -1) {
        handleError(this->id + ".xml", "vision", "text");
        return;
    }

    auto trainer(std::make_unique<Trainer>(idAttribute.c_str(), trainerName, xPos, yPos, static_cast<Direction>(trainerDirection), trainerVision));
    this->loadTrainer2(trainer, visionElement);
}

void Map::loadTrainer2(std::unique_ptr<Trainer> &trainer, tinyxml2::XMLElement *visionElement) {
    tinyxml2::XMLElement *dialogueListElement = visionElement->NextSiblingElement("dialogue");
    if (dialogueListElement == nullptr) {
        handleError(this->id + ".xml", "dialogue", "element");
        return;
    }

    std::vector<std::string> messages;
    messages.reserve(dialogueListElement->ChildElementCount());

    for (tinyxml2::XMLElement *messageElement = dialogueListElement->FirstChildElement("message");
         messageElement != nullptr;
         messageElement = messageElement->NextSiblingElement("message")) {
        if (const char *message = messageElement->GetText(); message != nullptr) {
            messages.emplace_back(message);
        }
    }

    trainer->setDialogue(messages);

    tinyxml2::XMLElement *partyElement = dialogueListElement->NextSiblingElement("party");
    if (partyElement == nullptr) {
        handleError(this->id + ".xml", "party", "element");
        return;
    }
    if (partyElement->ChildElementCount() == 0) {
        std::clog << "Invalid file format in file " << this->id << ".xml" << ": Trainer \"" << trainer->getName()
                  << " must have at least 1 Pokemon\n";
        std::terminate();
    }

    for (tinyxml2::XMLElement *pokemonElement = partyElement->FirstChildElement("pokemon"); pokemonElement != nullptr;
         pokemonElement = pokemonElement->NextSiblingElement("pokemon")) {
        const char *idAttribute = pokemonElement->Attribute("id");
        if (idAttribute == nullptr) {
            handleError(this->id + ".xml", "id", "attribute");
            return;
        }

        tinyxml2::XMLElement *moveSetElement = pokemonElement->FirstChildElement("move_set");
        if (moveSetElement == nullptr) {
            handleError(this->id + ".xml", "move_set", "element");
            return;
        }

        if (moveSetElement->ChildElementCount() == 0) {
            std::clog << "Invalid file format in file " << this->id << ".xml" << ": Pokemon \"" << idAttribute
                      << " must have at least 1 Move\n";
            std::terminate();
        }

        auto pokemon = std::make_unique<Pokemon>(idAttribute);

        for (tinyxml2::XMLElement *moveElement = moveSetElement->FirstChildElement("move"); moveElement != nullptr;
             moveElement = moveElement->NextSiblingElement("move")) {
            const char *moveIdAttribute = moveElement->Attribute("id");
            if (moveIdAttribute == nullptr) {
                handleError(this->id + ".xml", "id", "attribute");
                return;
            }

            pokemon->learnMove(moveIdAttribute);
        }

        trainer->addPokemon(std::move(pokemon));
    }

    this->entities.push_back(std::move(trainer));
}

void Map::loadItem(tinyxml2::XMLElement *entityElement) {
    if (not this->entitySprites.contains("Item")) {
        this->entitySprites["Item"] = TextureManager::getInstance().loadTexture("sprites/Items/Item.png");
        if (entitySprites.at("Item") == nullptr) {
            std::clog << "Unable to load item sprite\n";
            Game::getInstance().terminate();
            return;
        }
    }
    const char *idAttribute = entityElement->Attribute("id");
    if (idAttribute == nullptr) {
        handleError(this->id + ".xml", "id", "attribute");
        return;
    }

    tinyxml2::XMLElement *quantityElement = entityElement->FirstChildElement("quantity");
    if (quantityElement == nullptr) {
        handleError(this->id + ".xml", "quantity", "element");
        return;
    }

    const int quantity = quantityElement->IntText(-1);
    if (quantity == -1) {
        handleError(this->id + ".xml", "quantity", "text");
        return;
    }

    const tinyxml2::XMLElement *positionElement = quantityElement->NextSiblingElement("position");
    if (positionElement == nullptr) {
        handleError(this->id + ".xml", "position", "element");
        return;
    }

    const int xPos = positionElement->IntAttribute("x", -1);
    if (xPos == -1) {
        handleError(this->id + ".xml", "x", "attribute");
        return;
    }

    const int yPos = positionElement->IntAttribute("y", -1);
    if (yPos == -1) {
        handleError(this->id + ".xml", "y", "attribute");
        return;
    }

    std::unique_ptr item(itemMap.at(idAttribute)(quantity));
    item->getMapPosition().setPosition(xPos, yPos);
    item->getScreenPosition().setPosition(xPos * TILE_SIZE, yPos * TILE_SIZE);

    this->entities.push_back(std::move(item));
}

Map::Map(const char *name, const char *id) : name(name), id(id) {
    std::erase_if(this->id, [](const char c) -> bool {
        return c == ' ';
    });

    this->entitySprites["Player"] = TextureManager::getInstance().loadTexture("sprites/Hilbert/HilbertSpriteSheet.png");

    this->parseTmx();
    this->loadEntities();

    this->threadPool.init(this->layers.size() + 1);

    for (auto &entity : this->entities) {
        if (auto *trainer = dynamic_cast<Trainer *>(entity.get()); trainer != nullptr) {
            trainer->gainAutonomy(*this);
        }
    }
}

Map::~Map() {
    for (const auto sprite : this->tileSprites) {
        if (sprite != nullptr) {
            SDL_DestroyTexture(sprite);
            if (strlen(SDL_GetError()) > 0) {
                std::clog << "Unable to destroy tile sprite: " << SDL_GetError() << '\n';
                SDL_ClearError();
            }
        }
    }
    for (const auto sprite : this->entitySprites | std::views::values) {
        if (sprite != nullptr) {
            SDL_DestroyTexture(sprite);
            if (strlen(SDL_GetError()) > 0) {
                std::clog << "Unable to destroy entity sprite: " << SDL_GetError() << '\n';
                SDL_ClearError();
            }
        }
    }
}

bool Map::isCollisionHere(int x, int y) const {
    const bool collision = this->collisionSet.contains(this->layers[1](y, x).id);

    const bool playerHere = Player::getPlayer().getMapPosition().isHere(x, y);

    const bool entityHere = std::ranges::any_of(
            this->entities,
            [&x, &y](const std::unique_ptr <Entity> &entity) -> bool {
                return entity->getMapPosition().isHere(x, y);
            }
    );

    return collision or playerHere or entityHere;
}

std::optional<std::pair<Component::Position, std::string>> Map::isExitPointHere(const int x, const int y) const {
    for (const auto &[map, dest, newMap] : this->exitPoints) {
        if (map.isHere(x, y)) {
            return std::make_optional(std::make_pair(dest, newMap));
        }
    }
    return std::nullopt;
}

void Map::removeEntity(const Entity *entity) {
    for (long long int i = 0; i < this->entities.size(); ++i) {
        if (this->entities.at(i).get() == entity) {
            this->entities.erase(this->entities.begin() + i);
            return;
        }
    }
}

std::vector<std::unique_ptr<Entity>>::iterator Map::begin() {
    return this->entities.begin();
}

std::vector<std::unique_ptr<Entity>>::const_iterator Map::begin() const {
    return this->entities.cbegin();
}

std::vector<std::unique_ptr<Entity>>::iterator Map::end() {
    return this->entities.end();
}

std::vector<std::unique_ptr<Entity>>::const_iterator Map::end() const {
    return this->entities.cend();
}

std::string Map::getId() const {
    return this->id;
}

void Map::shift(Direction direction, int n) {
    for (auto &layer : this->layers) {
        this->threadPool.add([direction, n, &layer] -> void {
            for (auto &row : layer) {
                for (auto &[id, screen] : row) {
                    screen.translate(direction, n);
                }
            }
        });
    }

    this->threadPool.add([this, direction, n] -> void {
        for (const auto &entity : this->entities) {
            entity->getScreenPosition().translate(direction, n);
        }
    });

    this->threadPool.block();
}

void Map::shiftHorizontally(int n) {
    for (auto &layer : this->layers) {
        this->threadPool.add([n, &layer] -> void {
            for (auto &row : layer) {
                for (auto &[id, screen] : row) {
                    screen.translateX(n);
                }
            }
        });
    }

    this->threadPool.add([this, n] -> void {
        for (const auto &entity : this->entities) {
            entity->getScreenPosition().translateX(n);
        }
    });

    this->threadPool.block();
}

void Map::shiftVertically(int n) {
    for (auto &layer : this->layers) {
        this->threadPool.add([n, &layer] -> void {
            for (auto &row : layer) {
                for (auto &[id, screen] : row) {
                    screen.translateY(n);
                }
            }
        });
    }

    this->threadPool.add([this, n] -> void {
        for (const auto &entity : this->entities) {
            entity->getScreenPosition().translateY(n);
        }
    });

    this->threadPool.block();
}

void Map::render() const {
    SDL_Rect sdlRect(0, 0, TILE_SIZE, TILE_SIZE);

    for (std::size_t layer = 0; layer < this->layers.size(); ++layer) {
        for (const auto &row : this->layers[layer]) {
            for (const auto &[id, screen] : row) {
                sdlRect.x = screen.getX();
                sdlRect.y = screen.getY();
                // prevents rendering tiles that aren't onscreen
                if (Camera::getInstance().isInView(sdlRect) and id != 0) {
                    TextureManager::getInstance().draw(this->tileSprites.at(id), sdlRect);
                }
            }
        }
        if (layer == 1) {
            for (const auto &entity : this->entities) {
                sdlRect.x = entity->getScreenPosition().getX();
                sdlRect.y = entity->getScreenPosition().getY();
                // prevents rendering entities that aren't onscreen
                if (Camera::getInstance().isInView(sdlRect)) {
                    entity->render(this->entitySprites.at(entity->getSpriteKey()));
                }
            }

            Player::getPlayer().render(this->entitySprites.at("Player"));
        }
    }
}
