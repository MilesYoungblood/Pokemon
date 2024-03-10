//
// Created by Miles Youngblood on 7/10/2023.
//

#include "../Singleton/DerivedClasses/TextureManager/TextureManager.h"
#include "Map.h"

std::string errorMessage(const std::string &filename, const char *name, const char *type) {
    const bool is_tmx = filename.substr(filename.size() - 5) == ".tmx";
    return "Invalid " + std::string(is_tmx ? "TMX" : "TSX") + " file \"" + filename + "\": missing \"" + name + "\" " + type + '\n';
}

void Map::parseTmx() {
    tinyxml2::XMLDocument tmxFile;
    if (tmxFile.LoadFile(std::string_view("../assets/Tiled/Tilemaps/" + this->music + ".tmx").data()) != tinyxml2::XML_SUCCESS) {
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

    // the collision layer's dimensions MUST be the inverse of the textureMap's dimensions
    this->collision = std::vector<std::vector<bool>>(width, std::vector<bool>(height, false));

    // used when parsing the actual contents of a layer;
    // keeps track of which tile id's (on layer 2 specifically) have collision
    // an id of 0 denotes an absence of a tile, so collision is always false
    std::unordered_map<int, bool> collisionMap({ std::make_pair(0, false) });

    // used when parsing to keep track of image sources,
    // image sources are a more unique identifier than integers since
    // different maps can have the same source be of a different id
    std::unordered_map<int, const std::string> pathMap({ std::make_pair(0, "") });

    const tinyxml2::XMLElement *tilesetElement = mapElement->FirstChildElement("tileset");
    if (tilesetElement == nullptr) {
        throw std::runtime_error(errorMessage(this->music + ".tmx", "tileset", "element"));
    }

    // populate the maps with keys being the firstgid, and open each tsx file in the map
    while (tilesetElement != nullptr) {
        const int first_gid_attribute = tilesetElement->IntAttribute("firstgid");
        if (first_gid_attribute == 0) {
            throw std::runtime_error(errorMessage(this->music + ".tmx", "firstgid", "attribute"));
        }

        const std::string source_attribute(tilesetElement->Attribute("source"));
        if (source_attribute.empty()) {
            throw std::runtime_error(errorMessage(this->music + ".tmx", "source", "attribute"));
        }

        Map::parseTsx(first_gid_attribute, source_attribute, pathMap, collisionMap);

        tilesetElement = tilesetElement->NextSiblingElement("tileset");
    }

    this->populate(mapElement, pathMap, collisionMap);
}

void Map::parseTsx(int firstGidAttribute, const std::string &sourceAttribute, std::unordered_map<int, const std::string> &pathMap, std::unordered_map<int, bool> &collisionMap) {
    tinyxml2::XMLDocument tsxFile;
    if (tsxFile.LoadFile(std::string("../assets/Tiled/Tilesets/" + sourceAttribute).c_str()) != tinyxml2::XML_SUCCESS) {
        tsxFile.PrintError();
        std::terminate();
    }

    tinyxml2::XMLElement *tsElement = tsxFile.FirstChildElement("tileset");
    if (tsElement == nullptr) {
        throw std::runtime_error(errorMessage(sourceAttribute, "tileset", "element"));
    }

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

        // variable to reduce the number of expression calculations
        const int index = firstGidAttribute + id;
        if (not pathMap.contains(index)) {
            tinyxml2::XMLElement *propertyListElement = tileElement->FirstChildElement("properties");
            if (propertyListElement == nullptr) {
                throw std::runtime_error(errorMessage(sourceAttribute, "properties", "element"));
            }

            tinyxml2::XMLElement *propertyElement = propertyListElement->FirstChildElement("property");
            if (propertyElement == nullptr) {
                throw std::runtime_error(errorMessage(sourceAttribute, "property", "element"));
            }

            collisionMap.insert(std::make_pair(index, propertyElement->BoolAttribute("value")));

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

            pathMap.insert(std::make_pair(index, copy));
            Map::textureMap.insert(std::make_pair(copy, nullptr));
        }
    }
}

void Map::populate(const tinyxml2::XMLElement *mapElement, std::unordered_map<int, const std::string> &pathMap, std::unordered_map<int, bool> &collisionMap) {
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
        layer<tile> layer(this->collision[0].size(), std::vector<tile>(this->collision.size()));
        int value;
        for (int row = 0; row < this->collision[0].size(); ++row) {
            for (int col = 0; col < this->collision.size() and ss >> value; ++col) {
                layer[row][col].id = pathMap.at(value);
                layer[row][col].x = col * Map::TILE_SIZE;
                layer[row][col].y = row * Map::TILE_SIZE;
                if (ss.peek() == ',') {
                    ss.ignore();
                }

                // the only layer that affects collision is layer 2
                if (id_attribute == 2) {
                    this->collision[col][row] = collisionMap.at(value);
                }
            }
        }

        this->layout.push_back(layer);
        layerElement = layerElement->NextSiblingElement("layer");
    }
}

void Map::loadEntities() {

}

Map::Map(const char *name) : name(name), music(name) {
    this->music.erase(std::remove_if(this->music.begin(), this->music.end(), [](char c) -> bool {
        return c == ' ';
    }), this->music.end());

    this->parseTmx();
    this->loadEntities();
}

void Map::init() {
    static bool loaded = false;
    if (loaded) {
        return;
    }

    for (auto &mapping : Map::textureMap) {
        Map::textureMap.at(mapping.first) = TextureManager::getInstance().loadTexture("terrain/" + mapping.first + ".png");
        if (Map::textureMap.at(mapping.first) == nullptr) {
            throw std::runtime_error("Error loading texture at \"" + mapping.first + "\"\n");
        }
    }

    loaded = true;
}

void Map::clean() {
    for (auto &mapping : Map::textureMap) {
        if (mapping.second != nullptr) {
            SDL_DestroyTexture(mapping.second);
            if (strlen(SDL_GetError()) > 0) {
                std::clog << "Unable to destroy map texture: " << SDL_GetError() << '\n';
                SDL_ClearError();
            }
        }
    }
}

bool Map::isObstructionHere(int x, int y) const {
    try {
        return this->collision.at(x).at(y) or (Player::getPlayer().getMapX() == x and Player::getPlayer().getMapY() == y)or std::ranges::any_of(this->entities, [&x, &y](const std::unique_ptr<Entity> &entity) -> bool {
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

void Map::addEntity(std::unique_ptr<Entity> entity) {
    this->entities.push_back(std::move(entity));
}

std::size_t Map::numEntities() const {
    return this->entities.size();
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
    threads.reserve(this->layout.size() + 2);

    for (auto &layer : this->layout) {
        threads.emplace_back([&layer, &direction, &n] -> void {
            for (auto &row : layer) {
                for (auto &col : row) {
                    switch (direction) {
                        case Direction::UP:
                            col.y -= n;
                            break;
                        case Direction::DOWN:
                            col.y += n;
                            break;
                        case Direction::LEFT:
                            col.x -= n;
                            break;
                        case Direction::RIGHT:
                            col.x += n;
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
                    col.x += n;
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
                    col.y += n;
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
                sdlRect.x = col.x;
                sdlRect.y = col.y;
                // prevents rendering tiles that aren't onscreen
                if (Camera::getInstance().isInView(sdlRect) and not col.id.empty()) {
                    TextureManager::getInstance().draw(Map::textureMap.at(col.id), sdlRect);
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
                    layer[i][j].x = i * Map::TILE_SIZE;
                    layer[i][j].y = j * Map::TILE_SIZE;
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
