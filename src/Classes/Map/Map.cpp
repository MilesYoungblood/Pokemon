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

Map::Map() {
    ++Map::instanceCounter;
}

Map::Map(const std::string &path, const char *music) : name(path.c_str()), music(music) {
    tinyxml2::XMLDocument tmxFile;
    tinyxml2::XMLError isOpen = tmxFile.LoadFile(std::string("../assets/Tiled/Tilemaps/" + path + ".tmx").c_str());
    if (isOpen != tinyxml2::XML_SUCCESS) {
        std::clog << "Error code" << isOpen << ": " << tmxFile.ErrorStr() << '\n';
        return;
    }

    tinyxml2::XMLElement *mapElement = tmxFile.FirstChildElement("map");
    if (mapElement == nullptr) {
        std::clog << "Invalid TMX file format: missing \"map\" element.\n";
        return;
    }

    int width = mapElement->IntAttribute("width");
    if (width == 0) {
        std::clog << "Invalid TMX file format: missing \"width\" attribute\n";
        return;
    }
    int height = mapElement->IntAttribute("height");
    if (height == 0) {
        std::clog << "Invalid TMX file format: missing \"height\" attribute\n";
        return;
    }

    this->collision = std::vector<std::vector<bool>>(width, std::vector<bool>(height, false));

    //std::unordered_map<int, std::string> pathMap;
    std::unordered_map<int, bool> collisionMap;
    collisionMap.insert(std::make_pair(0, false));

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
        isOpen = tsxFile.LoadFile(std::string("../assets/Tiled/Tilesets/" + sourceAttribute).c_str());
        if (isOpen != tinyxml2::XML_SUCCESS) {
            std::clog << "Error code" << isOpen << ": " << tsxFile.ErrorStr() << '\n';
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

            if (Map::textureMap[first_gid_attribute + id] == nullptr) {
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

                const bool collision_attribute = propertyElement->BoolAttribute("value");
                if (not collisionMap.contains(first_gid_attribute + id)) {
                    collisionMap.insert(std::make_pair(first_gid_attribute + id, collision_attribute));
                }

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

                sourceAttribute.erase(0, 13);

                Map::textureMap[first_gid_attribute + id] = TextureManager::getInstance().loadTexture(sourceAttribute);
                if (Map::textureMap[first_gid_attribute + id] == nullptr) {
                    std::clog << "Error loading texture\n";
                }
            }
        }
    }

    tinyxml2::XMLElement *layerElement = mapElement->FirstChildElement("layer");
    if (layerElement == nullptr) {
        std::clog << "Invalid TMX file format: missing \"layer\" element\n";
        return;
    }

    while (layerElement != nullptr) {
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
                layer[row][col].id = value;
                layer[row][col].x = col * Constants::TILE_SIZE;
                layer[row][col].y = row * Constants::TILE_SIZE;
                if (ss.peek() == ',') {
                    ss.ignore();
                }

                this->collision[col][row] = collisionMap.at(value);
            }
        }

        layerElement = layerElement->NextSiblingElement("layer");
        this->layout.push_back(layer);
    }
    ++Map::instanceCounter;
}

Map::Map(const char *name, const char *music, int width, int height) : name(name), music(music) {
    ++Map::instanceCounter;
    this->layout = std::vector<layer>(2, layer(height, std::vector<data>(width, { 1, 0, 0 })));
    this->collision = std::vector<std::vector<bool>>(height, std::vector<bool>(width, false));
}

Map::Map(Map &&toMove) noexcept
        : name(toMove.name), music(toMove.music), layout(std::move(toMove.layout)), collision(std::move(toMove.collision)),
          trainers(std::move(toMove.trainers)), items(std::move(toMove.items)), exitPoints(std::move(toMove.exitPoints)) {}

Map &Map::operator=(Map &&toMove) noexcept {
    this->name = toMove.name;
    this->music = toMove.music;
    this->layout = std::move(toMove.layout);
    this->collision = std::move(toMove.collision);
    this->trainers = std::move(toMove.trainers);
    this->items = std::move(toMove.items);
    this->exitPoints = std::move(toMove.exitPoints);

    return *this;
}

Map::~Map() {
    --Map::instanceCounter;
    if (Map::instanceCounter > 1) {
        return;
    }
    for (auto &texture : Map::textureMap) {
        SDL_DestroyTexture(texture.second);
    }
    Map::textureMap.clear();
}

// returns true if an obstruction is at the passed coordinates
bool Map::isObstructionHere(const int x, const int y) const {
    try {
        return this->collision.at(x).at(y) or this->isTrainerHere(x, y);
    }
    catch (const std::exception &e) {
        std::clog << "Error accessing map layout: " << e.what() << '\n';
        return true;
    }
}

void Map::addExitPoint(const ExitPoint &exitPoint) {
    this->exitPoints.push_back(exitPoint);
    try {
        this->collision.at(exitPoint.x).at(exitPoint.y) = false;
    }
    catch (const std::out_of_range &e) {
        std::clog << "Error adding exit point: " << e.what() << '\n';
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

// places an obstruction at the passed coordinates
void Map::setObstruction(const int x, const int y) {
    if (not this->isTrainerHere(x, y)) {
        try {
            this->collision.at(x).at(y) = true;
        }
        catch (const std::out_of_range &e) {
            throw std::out_of_range(std::string("Error accessing layout: ") + e.what() + '\n');
        }
    }
}

// shift the map and its trainers, according to a passed in flag
void Map::shift(Direction direction, int distance) {
    for (auto &layer : this->layout) {
        //threads.emplace_back([&layer, &direction, &distance] -> void {
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
        //});
    }

    //threads.emplace_back([this, &direction, &distance] -> void {
    for (const std::unique_ptr<Trainer> &trainer : this->trainers) {
        switch (direction) {
            case Direction::DOWN:
                trainer->shiftDownOnMap(distance);
                break;
            case Direction::UP:
                trainer->shiftUpOnMap(distance);
                break;
            case Direction::RIGHT:
                trainer->shiftRightOnMap(distance);
                break;
            case Direction::LEFT:
                trainer->shiftLeftOnMap(distance);
                break;
            default:
                return;
        }
    }
    //});
}

void Map::render() const {
    SDL_Rect sdlRect{ 0, 0, Constants::TILE_SIZE, Constants::TILE_SIZE };
    for (const auto &layer : this->layout) {
        for (const auto &row : layer) {
            for (const auto &col : row) {
                sdlRect.x = col.x;
                sdlRect.y = col.y;
                // prevents rendering tiles that aren't onscreen
                if (Camera::getInstance().isInView(sdlRect) and col.id > 0) {
                    TextureManager::getInstance().draw(Map::textureMap.at(col.id), sdlRect);
                }
            }
        }
    }

    for (const auto &trainer : this->trainers) {
        sdlRect.x = trainer->getScreenX();
        sdlRect.y = trainer->getScreenY();
        // prevents rendering trainers that aren't onscreen
        if (Camera::getInstance().isInView(sdlRect)) {
            trainer->render();
        }
    }
}

// resets the previous map's tile positions
// as well as the trainer's positions
void Map::reset() {
    for (auto &layer : this->layout) {
        for (int i = 0; i < layer.size(); ++i) {
            for (int j = 0; j < layer[i].size(); ++j) {
                layer[i][j].x = i * Constants::TILE_SIZE;
                layer[i][j].y = j * Constants::TILE_SIZE;
            }
        }
    }

    for (auto &trainer : this->trainers) {
        trainer->resetPos();
    }
}
