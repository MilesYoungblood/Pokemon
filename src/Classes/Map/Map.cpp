//
// Created by Miles Youngblood on 7/10/2023.
//

#include "Map.h"

bool Map::isTrainerHere(const int x, const int y) const {
    for (const std::unique_ptr<Trainer> &trainer : this->trainers) {
        if (trainer->getX() == x and trainer->getY() == y) {
            return true;
        }
    }
    return false;
}

Map::Map(const char *name) : name(name), music(name) {
    music.erase(std::remove_if(music.begin(), music.end(), [](char c) -> bool {
        return c == ' ';
    }), music.end());

    tinyxml2::XMLDocument tmxFile;
    tinyxml2::XMLError xmlErrorCode = tmxFile.LoadFile(std::string_view("../assets/Tiled/Tilemaps/" + music + ".tmx").data());
    if (xmlErrorCode != tinyxml2::XML_SUCCESS) {
        std::clog << "Error code " << xmlErrorCode << ": " << tmxFile.ErrorStr() << '\n';
        return;
    }

    tinyxml2::XMLElement *mapElement = tmxFile.FirstChildElement("map");
    if (mapElement == nullptr) {
        std::clog << "Invalid TMX file format: missing \"map\" element.\n";
        return;
    }

    const int width = mapElement->IntAttribute("width");
    if (width == 0) {
        std::clog << "Invalid TMX file format: missing \"width\" attribute\n";
        return;
    }
    const int height = mapElement->IntAttribute("height");
    if (height == 0) {
        std::clog << "Invalid TMX file format: missing \"height\" attribute\n";
        return;
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

    // populate the maps with keys being the firstgid, and open each tsx file in the map
    for (tinyxml2::XMLElement *tilesetElement = mapElement->FirstChildElement("tileset");
         tilesetElement != nullptr; tilesetElement = tilesetElement->NextSiblingElement("tileset")) {
        const int first_gid_attribute = tilesetElement->IntAttribute("firstgid");
        if (first_gid_attribute == 0) {
            std::clog << "Invalid TMX file format: missing \"firstgid\" attribute\n";
            return;
        }

        std::string sourceAttribute(tilesetElement->Attribute("source"));
        if (sourceAttribute.empty()) {
            std::clog << "Invalid TMX file format: missing \"source\" attribute\n";
            return;
        }

        tinyxml2::XMLDocument tsxFile;
        xmlErrorCode = tsxFile.LoadFile(std::string("../assets/Tiled/Tilesets/" + sourceAttribute).c_str());
        if (xmlErrorCode != tinyxml2::XML_SUCCESS) {
            std::clog << "Error code" << xmlErrorCode << ": " << tsxFile.ErrorStr() << '\n';
            return;
        }

        tinyxml2::XMLElement *tsElement = tsxFile.FirstChildElement("tileset");
        if (tsElement == nullptr) {
            std::clog << "Invalid TSX file format: missing \"tileset\" element\n";
            return;
        }

        tinyxml2::XMLElement *gridElement = tsElement->FirstChildElement("grid");
        if (gridElement == nullptr) {
            std::clog << "Invalid TSX file format: missing \"grid\" element\n";
            return;
        }

        for (tinyxml2::XMLElement *tileElement = gridElement->NextSiblingElement("tile");
             tileElement != nullptr; tileElement = tileElement->NextSiblingElement("tile")) {
            const int id = tileElement->IntAttribute("id", -1);
            if (id == -1) {
                std::clog << "Invalid TSX file format: missing \"id\" attribute\n";
                return;
            }

            // variable to reduce the number of expression calculations
            const int index = first_gid_attribute + id;
            if (not pathMap.contains(index)) {
                tinyxml2::XMLElement *propertyListElement = tileElement->FirstChildElement("properties");
                if (propertyListElement == nullptr) {
                    std::clog << "Invalid TSX file format: missing \"properties\" element\n";
                    return;
                }

                tinyxml2::XMLElement *propertyElement = propertyListElement->FirstChildElement("property");
                if (propertyElement == nullptr) {
                    std::clog << "Invalid TSX file format: missing \"property\" element\n";
                    return;
                }

                collisionMap.insert(std::make_pair(index, propertyElement->BoolAttribute("value")));

                tinyxml2::XMLElement *imageElement = propertyListElement->NextSiblingElement("image");
                if (imageElement == nullptr) {
                    std::clog << "Invalid TSX file format: missing \"image\" element\n";
                    return;
                }

                sourceAttribute = imageElement->Attribute("source");
                if (sourceAttribute.empty()) {
                    std::clog << "Invalid TSX file format: missing \"source\" attribute\n";
                    return;
                }

                // strip off unnecessary characters
                sourceAttribute.erase(0, 21);
                sourceAttribute.erase(sourceAttribute.size() - 4);

                pathMap.insert(std::make_pair(index, sourceAttribute));
                Map::textureMap.insert(std::make_pair(sourceAttribute, nullptr));
            }
        }
    }

    tinyxml2::XMLElement *layerElement = mapElement->FirstChildElement("layer");
    if (layerElement == nullptr) {
        std::clog << "Invalid TMX file format: missing \"layer\" element\n";
        return;
    }

    while (layerElement != nullptr) {
        const int id_attribute = layerElement->IntAttribute("id");
        if (id_attribute == 0) {
            std::clog << "Invalid TMX file format: missing \"id\" attribute\n";
            return;
        }

        tinyxml2::XMLElement *dataElement = layerElement->FirstChildElement("data");
        if (dataElement == nullptr) {
            std::clog << "Invalid TMX file format: missing \"data\" element\n";
            return;
        }

        const char *csvData = dataElement->GetText();
        if (csvData == nullptr) {
            std::clog << "Invalid TMX file format: missing csv data\n";
            return;
        }

        std::istringstream ss(csvData);
        layer layer(height, std::vector<data>(width));
        int value;
        for (int row = 0; row < height; ++row) {
            for (int col = 0; col < width and ss >> value; ++col) {
                layer[row][col].id = pathMap.at(value);
                layer[row][col].x = col * Constants::TILE_SIZE;
                layer[row][col].y = row * Constants::TILE_SIZE;
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

void Map::loadTextures() {
    static bool loaded = false;
    if (loaded) {
        return;
    }

    for (auto &mapping : Map::textureMap) {
        Map::textureMap.at(mapping.first) = std::make_shared<Texture>("terrain/" + mapping.first + ".png");
        if (Map::textureMap.at(mapping.first) == nullptr) {
            std::clog << "Error loading texture at " << mapping.first << '\n';
        }
    }

    loaded = true;
}

// returns true if an obstruction is at the passed coordinates
bool Map::isObstructionHere(int x, int y) const {
    try {
        return this->collision.at(x).at(y) or this->isTrainerHere(x, y);
    }
    catch (const std::exception &e) {
        std::clog << "Error accessing map layout: " << e.what() << '\n';
        return true;
    }
}

// returns a tuple containing the new coordinates and new map respectively if an exit point is present,
// or nothing otherwise
std::optional<std::tuple<int, int, Map::Id>> Map::isExitPointHere(const int x, const int y) const {
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
Trainer &Map::operator[](const int index) {
    try {
        return *this->trainers.at(index);
    }
    catch (const std::out_of_range &e) {
        throw std::out_of_range(std::string("Error accessing trainers: ") + e.what() + '\n');
    }
}

const Trainer &Map::operator[](const int index) const {
    try {
        return *this->trainers.at(index);
    }
    catch (const std::out_of_range &e) {
        throw std::out_of_range(std::string("Error accessing trainers: ") + e.what() + '\n');
    }
}

std::vector<std::unique_ptr<Trainer>>::iterator Map::begin() {
    return this->trainers.begin();
}

std::vector<std::unique_ptr<Trainer>>::iterator Map::end() {
    return this->trainers.end();
}

std::string Map::getMusic() const {
    return this->music;
}

// shift the map and its trainers, according to a passed in flag
void Map::shift(Direction direction, int distance) {
    std::vector<std::jthread> threads(this->layout.size() + 1);
    for (auto &layer : this->layout) {
        threads.emplace_back([&layer, &direction, &distance] -> void {
            for (auto &row : layer) {
                for (auto &col : row) {
                    switch (direction) {
                        case Direction::DOWN:
                            col.y += distance;
                            break;
                        case Direction::UP:
                            col.y -= distance;
                            break;
                        case Direction::RIGHT:
                            col.x += distance;
                            break;
                        case Direction::LEFT:
                            col.x -= distance;
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
            trainer->shift(direction, distance);
        }
    });
}

void Map::render() const {
    static SDL_Rect sdlRect(0, 0, Constants::TILE_SIZE, Constants::TILE_SIZE);
    for (std::size_t layer = 0; layer < this->layout.size(); ++layer) {
        for (const auto &row : this->layout[layer]) {
            for (const auto &col : row) {
                sdlRect.x = col.x;
                sdlRect.y = col.y;
                // prevents rendering tiles that aren't onscreen
                if (Camera::getInstance().isInView(sdlRect) and not col.id.empty()) {
                    try {
                        TextureManager::getInstance().draw(Map::textureMap.at(col.id)->getTexture(), sdlRect);
                    }
                    catch (const std::exception &e) {
                        std::clog << "Error rendering tile: " << e.what() << ' ' << col.id << '\n';
                    }
                }
            }
        }
        if (layer == 1) {
            for (const auto &trainer : this->trainers) {
                sdlRect.x = trainer->getScreenX();
                sdlRect.y = trainer->getScreenY();
                // prevents rendering trainers that aren't onscreen
                if (Camera::getInstance().isInView(sdlRect)) {
                    trainer->render();
                }
            }
            Player::getPlayer().render();
        }
    }
}

// resets the previous map's tile positions
// as well as the trainer's positions
void Map::reset() {
    std::vector<std::jthread> threads(this->layout.size() + 1);
    for (auto &layer : this->layout) {
        threads.emplace_back([&layer] -> void {
            for (int i = 0; i < layer.size(); ++i) {
                for (int j = 0; j < layer[i].size(); ++j) {
                    layer[i][j].x = i * Constants::TILE_SIZE;
                    layer[i][j].y = j * Constants::TILE_SIZE;
                }
            }
        });
    }

    threads.emplace_back([this] -> void {
        for (auto &trainer : this->trainers) {
            trainer->resetPos();
        }
    });
}
