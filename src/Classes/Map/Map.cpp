//
// Created by Miles Youngblood on 7/10/2023.
//

#include "Map.h"

namespace {
    bool called = false;
}

Map::Map(const char *name) : name(name), music(name) {
    music.erase(std::remove_if(music.begin(), music.end(), [](char c) -> bool {
        return c == ' ';
    }), music.end());

    tinyxml2::XMLDocument tmxFile;
    tinyxml2::XMLError xmlErrorCode = tmxFile.LoadFile(std::string_view("../assets/Tiled/Tilemaps/" + music + ".tmx").data());
    if (xmlErrorCode != tinyxml2::XML_SUCCESS) {
        throw std::runtime_error("Error code " + std::to_string(xmlErrorCode) + ": " + tmxFile.ErrorStr() + '\n');
    }

    const tinyxml2::XMLElement *mapElement = tmxFile.FirstChildElement("map");
    if (mapElement == nullptr) {
        throw std::runtime_error("Invalid TMX file format in file \"" + music + "\": missing \"map\" element\n");
    }

    const int width = mapElement->IntAttribute("width");
    if (width == 0) {
        throw std::runtime_error("Invalid TMX file format in file \"" + music + "\": missing \"width\" attribute\n");
    }
    const int height = mapElement->IntAttribute("height");
    if (height == 0) {
        throw std::runtime_error("Invalid TMX file format in file \"" + music + "\": missing \"height\" attribute\n");
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
        throw std::runtime_error("Invalid TMX file format in file \"" + music + "\": missing \"tileset\" element\n");
    }

    // populate the maps with keys being the firstgid, and open each tsx file in the map
    while (tilesetElement != nullptr) {
        const int first_gid_attribute = tilesetElement->IntAttribute("firstgid");
        if (first_gid_attribute == 0) {
            throw std::runtime_error("Invalid TMX file format in file \"" + music + "\": missing \"firstgid\" attribute\n");
        }

        std::string sourceAttribute(tilesetElement->Attribute("source"));
        if (sourceAttribute.empty()) {
            throw std::runtime_error("Invalid TMX file format in file \"" + music + "\": missing \"source\" attribute\n");
        }

        tinyxml2::XMLDocument tsxFile;
        xmlErrorCode = tsxFile.LoadFile(std::string("../assets/Tiled/Tilesets/" + sourceAttribute).c_str());
        if (xmlErrorCode != tinyxml2::XML_SUCCESS) {
            throw std::runtime_error("Error code " + std::to_string(xmlErrorCode) + ": " + tsxFile.ErrorStr() + '\n');
        }

        tinyxml2::XMLElement *tsElement = tsxFile.FirstChildElement("tileset");
        if (tsElement == nullptr) {
            throw std::runtime_error("Invalid TSX file format in file \"" + sourceAttribute + "\": missing \"tileset\" element\n");
        }

        tinyxml2::XMLElement *gridElement = tsElement->FirstChildElement("grid");
        if (gridElement == nullptr) {
            throw std::runtime_error("Invalid TSX file format in file \"" + sourceAttribute + "\": missing \"grid\" element\n");
        }

        for (tinyxml2::XMLElement *tileElement = gridElement->NextSiblingElement("tile");
             tileElement != nullptr; tileElement = tileElement->NextSiblingElement("tile")) {
            const int id = tileElement->IntAttribute("id", -1);
            if (id == -1) {
                throw std::runtime_error("Invalid TSX file format in file \"" + sourceAttribute + "\": missing \"id\" attribute\n");
            }

            // variable to reduce the number of expression calculations
            const int index = first_gid_attribute + id;
            if (not pathMap.contains(index)) {
                tinyxml2::XMLElement *propertyListElement = tileElement->FirstChildElement("properties");
                if (propertyListElement == nullptr) {
                    throw std::runtime_error("Invalid TSX file format in file \"" + sourceAttribute + "\": missing \"properties\" element\n");
                }

                tinyxml2::XMLElement *propertyElement = propertyListElement->FirstChildElement("property");
                if (propertyElement == nullptr) {
                    throw std::runtime_error("Invalid TSX file format in file \"" + sourceAttribute + "\": missing \"property\" element\n");
                }

                collisionMap.insert(std::make_pair(index, propertyElement->BoolAttribute("value")));

                tinyxml2::XMLElement *imageElement = propertyListElement->NextSiblingElement("image");
                if (imageElement == nullptr) {
                    throw std::runtime_error("Invalid TSX file format in file \"" + sourceAttribute + "\": missing \"image\" element\n");
                }

                const std::string copy(sourceAttribute);
                sourceAttribute = imageElement->Attribute("source");
                if (sourceAttribute.empty()) {
                    throw std::runtime_error("Invalid TSX file format in file \"" + copy + "\": missing \"source\" attribute\n");
                }

                // strip off unnecessary characters
                sourceAttribute.erase(0, 21);
                sourceAttribute.erase(sourceAttribute.size() - 4);

                pathMap.insert(std::make_pair(index, sourceAttribute));
                Map::textureMap.insert(std::make_pair(sourceAttribute, nullptr));
            }
        }

        tilesetElement = tilesetElement->NextSiblingElement("tileset");
    }

    const tinyxml2::XMLElement *layerElement = mapElement->FirstChildElement("layer");
    if (layerElement == nullptr) {
        throw std::runtime_error("Invalid TMX file format in file \"" + music + "\": missing \"layer\" element\n");
    }

    while (layerElement != nullptr) {
        const int id_attribute = layerElement->IntAttribute("id");
        if (id_attribute == 0) {
            throw std::runtime_error("Invalid TMX file format in file \"" + music + "\": missing \"id\" attribute\n");
        }

        const tinyxml2::XMLElement *dataElement = layerElement->FirstChildElement("data");
        if (dataElement == nullptr) {
            throw std::runtime_error("Invalid TMX file format in file \"" + music + "\": missing \"data\" element\n");
        }

        const char *csvData = dataElement->GetText();
        if (csvData == nullptr) {
            throw std::runtime_error("Invalid TMX file format in file \"" + music + "\": missing csv data\n");
        }

        std::istringstream ss(csvData);
        layer<tile> layer(height, std::vector<tile>(width));
        int value;
        for (int row = 0; row < height; ++row) {
            for (int col = 0; col < width and ss >> value; ++col) {
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

Map::~Map() {
    if (not called) {
        std::clog << "Map::clean() not called\n";
    }
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
    called = true;
}

// returns true if an obstruction is at the passed coordinates
bool Map::isObstructionHere(int x, int y) const {
    try {
        return this->collision.at(x).at(y) or (Player::getPlayer().getX() == x and Player::getPlayer().getY() == y) or std::ranges::any_of(this->trainers, [&x, &y](const Trainer &trainer) -> bool {
            return trainer.getX() == x and trainer.getY() == y;
        }) or std::ranges::any_of(this->items, [&x, &y](const auto &item) -> bool {
            return item.first.x == x and item.first.y == y;
        });
    }
    catch (const std::exception &e) {
        throw std::runtime_error(std::string("Error accessing map layout: ") + e.what() + '\n');
    }
}

// returns a tuple containing the new coordinates and new map respectively if an exit point is present,
// or nothing otherwise
std::optional<std::tuple<int, int, Map::Id>> Map::isExitPointHere(int x, int y) const {
    for (const ExitPoint &exit_point : this->exitPoints) {
        if (exit_point.x == x and exit_point.y == y) {
            return std::make_optional(std::make_tuple(exit_point.newX, exit_point.newY, exit_point.newMap));
        }
    }
    return std::nullopt;
}

int Map::numTrainers() const {
    return static_cast<int>(this->trainers.size());
}

// returns the trainer at the passed index
Trainer &Map::operator[](std::size_t index) {
    try {
        return this->trainers.at(index);
    }
    catch (const std::out_of_range &e) {
        throw std::out_of_range(std::string("Error accessing trainers: ") + e.what() + '\n');
    }
}

const Trainer &Map::operator[](std::size_t index) const {
    try {
        return this->trainers.at(index);
    }
    catch (const std::out_of_range &e) {
        throw std::out_of_range(std::string("Error accessing trainers: ") + e.what() + '\n');
    }
}

std::vector<Trainer>::iterator Map::begin() {
    return this->trainers.begin();
}

std::vector<Trainer>::iterator Map::end() {
    return this->trainers.end();
}

std::string Map::getMusic() const {
    return this->music;
}

// shift the map and its trainers, according to a passed in flag
void Map::shift(Direction direction, int distance) {
    std::vector<std::thread> threads;
    threads.reserve(this->layout.size() + 2);

    for (auto &layer : this->layout) {
        threads.emplace_back([&layer, &direction, &distance] -> void {
            for (auto &row : layer) {
                for (auto &col : row) {
                    switch (direction) {
                        case Direction::UP:
                            col.y -= distance;
                            break;
                        case Direction::DOWN:
                            col.y += distance;
                            break;
                        case Direction::LEFT:
                            col.x -= distance;
                            break;
                        case Direction::RIGHT:
                            col.x += distance;
                            break;
                        default:
                            return;
                    }
                }
            }
        });
    }

    threads.emplace_back([this, &direction, &distance] -> void {
        for (auto &trainer : this->trainers) {
            trainer.shift(direction, distance);
        }
    });

    threads.emplace_back([this, &direction, &distance] -> void {
        for (auto &item : this->items) {
            switch (direction) {
                case Direction::UP:
                    item.first.screenY -= distance;
                    break;
                case Direction::DOWN:
                    item.first.screenY += distance;
                    break;
                case Direction::LEFT:
                    item.first.screenX -= distance;
                    break;
                case Direction::RIGHT:
                    item.first.screenX += distance;
                    break;
                default:
                    return;
            }
        }
    });

    for (auto &thread : threads) {
        thread.join();
    }
}

void Map::shiftHorizontally(int n) {
    std::vector<std::thread> threads;
    threads.reserve(this->layout.size() + 2);

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
        for (auto &trainer : this->trainers) {
            trainer.shiftHorizontally(n);
        }
    });

    threads.emplace_back([this, &n] -> void {
        for (auto &item : this->items) {
            item.first.screenX += n;
        }
    });

    for (auto &thread : threads) {
        thread.join();
    }
}

void Map::shiftVertically(int n) {
    std::vector<std::thread> threads;
    threads.reserve(this->layout.size() + 2);

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
        for (auto &trainer : this->trainers) {
            trainer.shiftVertically(n);
        }
    });

    threads.emplace_back([this, &n] -> void {
        for (auto &item : this->items) {
            item.first.screenY += n;
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
            for (const auto &trainer : this->trainers) {
                sdlRect.x = trainer.getScreenX();
                sdlRect.y = trainer.getScreenY();
                // prevents rendering trainers that aren't onscreen
                if (Camera::getInstance().isInView(sdlRect)) {
                    trainer.render();
                }
            }

            static Texture texture("Item_Overworld_Sprite.png", SDL_Rect(0, 0, 0, 0));
            for (const auto &item : this->items) {
                texture.setDest(SDL_Rect(
                        item.first.screenX + 28,
                        item.first.screenY + 28,
                        24,
                        24
                ));
                if (Camera::getInstance().isInView(texture.getDest())) {
                    texture.render();
                }
            }
            Player::getPlayer().render();
        }
    }
}

// resets the previous map's tile positions
// as well as the trainer's and item's positions
void Map::reset() {
    std::vector<std::thread> threads;
    threads.reserve(this->layout.size() + 2);

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
        for (auto &trainer : this->trainers) {
            trainer.resetPos();
        }
    });

    threads.emplace_back([this] -> void {
        for (auto &item : this->items) {
            item.first.screenX = item.first.x * Map::TILE_SIZE;
            item.first.screenY = item.first.y * Map::TILE_SIZE;
        }
    });

    for (auto &thread : threads) {
        thread.join();
    }
}
