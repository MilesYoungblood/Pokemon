#include "Classes/Singleton/DerivedClasses/Game/Game.h"

void loadMap(const std::string &path) {
    tinyxml2::XMLDocument doc;
    if (doc.LoadFile(std::string("../assets/Tiled/Tilemaps/" + path + ".tmx").c_str()) != tinyxml2::XML_SUCCESS) {
        std::clog << "Error loading TMX file \"" << path << "\": " << doc.ErrorStr() << '\n';
        return;
    }

    /*
    tinyxml2::XMLElement *xmlElement = doc.FirstChildElement("xml");
    if (xmlElement == nullptr) {
        std::clog << "Invalid TMX file format: missing 'xml' element.\n";
        return;
    }

    tinyxml2::XMLElement *mapElement = xmlElement->FirstChildElement("map");
     */

    tinyxml2::XMLElement *mapElement = doc.FirstChildElement("map");
    if (mapElement == nullptr) {
        std::clog << "Invalid TMX file format: missing 'map' element.\n";
        return;
    }

    int width;
    int height;
    mapElement->QueryAttribute("width", &width);
    mapElement->QueryAttribute("height", &height);

    using layer = std::vector<std::vector<int>>;
    std::vector<layer> map;

    using firstgid = int;               // denotes which tileset a map object belongs to
    using tile = int;                   // denotes which specific tile of the tileset is in question

    using sources = std::unordered_map<tile, const char *>;
    using textures = std::unordered_map<tile, SDL_Texture *>;

    std::unordered_map<firstgid, textures> textureMap;              // container for textures
    std::unordered_map<firstgid, sources> sourceMap;                // container for image sources
    std::unordered_map<firstgid, tinyxml2::XMLDocument> documents;  // container for tsx files

    // populate the maps with keys being the firstgid, and open each tsx file in the map
    for (tinyxml2::XMLElement *tilesetElement = mapElement->FirstChildElement("tileset");
         tilesetElement != nullptr; tilesetElement = tilesetElement->NextSiblingElement("tileset")) {
        const char *firstGidAttribute = tilesetElement->Attribute("firstgid");
        if (firstGidAttribute != nullptr) {
            const std::string src = tilesetElement->Attribute("source");
            if (not src.empty()) {
                int key = std::stoi(firstGidAttribute);
                textureMap[key];
                sourceMap[key];
                documents[key];
                if (documents[key].LoadFile(std::string("../assets/Tiled/Tilemaps/" + src).c_str()) !=
                    tinyxml2::XML_SUCCESS) {
                    std::clog << "Error loading TMX file \"" << src << "\": " << documents[key].ErrorStr() << '\n';
                }
            }
            else {
                std::clog << "Invalid TMX file format: missing \"source\" attribute\n";
                return;
            }
        }
        else {
            std::clog << "Invalid TMX file format: missing \"firstgid\" attribute\n";
            return;
        }
    }

    tinyxml2::XMLElement *layerElement = mapElement->FirstChildElement("layer");
    if (layerElement == nullptr) {
        std::clog << "Invalid TMX file format: missing \"layer\" element\n";
        return;
    }

    while (layerElement != nullptr) {
        tinyxml2::XMLElement *dataElement = layerElement->FirstChildElement("data");
        layer layer(height, std::vector<int>(width));
        if (dataElement != nullptr) {
            const char *csvData = dataElement->GetText();
            if (csvData != nullptr) {
                std::istringstream ss(csvData);
                int value;
                for (int row = 0; row < height; ++row) {
                    for (int col = 0; col < width and ss >> value; ++col) {
                        layer[row][col] = value;
                        if (ss.peek() == ',') {
                            ss.ignore();
                        }

                        if (value == 0) {
                            continue;
                        }
                        bool loop = true;
                        // iterate through the sourceMap, and attempt to find where the value should be in between
                        for (auto it = sourceMap.begin(); it != sourceMap.end(); ++it) {
                            if (not loop) {
                                break;
                            }
                            // if the map value is in between firstgid and the firstgid after, add
                            // the data into the corresponding slot in the map
                            if (it->first <= value) {
                                // if the sourceMap does not contain the value,
                                // begin reading from the document,
                                // and add the source to the map
                                if (not sourceMap[it->first].contains(value)) {
                                    sourceMap[it->first][value];
                                    tinyxml2::XMLElement *tilesetElement = documents[it->first].FirstChildElement(
                                            "tileset");
                                    if (tilesetElement == nullptr) {
                                        std::clog << "Invalid TMX file format: missing \"tileset\" element\n";
                                        return;
                                    }
                                    tinyxml2::XMLElement *gridElement = tilesetElement->FirstChildElement("grid");
                                    // FIXME make this not necessary for Grass.tsx
                                    if (gridElement == nullptr) {
                                        tinyxml2::XMLElement *imageElement = tilesetElement->FirstChildElement("image");
                                        if (imageElement == nullptr) {
                                            std::clog << "Invalid TMX file format: missing \"image\" element\n";
                                            return;
                                        }
                                        const char *sourceAttribute = imageElement->Attribute("source");
                                        if (sourceAttribute == nullptr) {
                                            std::clog << "Invalid TMX file format: missing \"source\" attribute\n";
                                            return;
                                        }
                                        sourceMap[it->first][value] = sourceAttribute;
                                    }
                                    else {
                                        for (tinyxml2::XMLElement *tileElement = gridElement->NextSiblingElement(
                                                "tile");
                                             tileElement != nullptr; tileElement = tileElement->NextSiblingElement(
                                                "tile")) {
                                            const char *id = tileElement->Attribute("id");
                                            if (id == nullptr) {
                                                std::clog << "Invalid TMX file format: missing \"id\""
                                                          << "attribute\n";
                                                return;
                                            }
                                            // if true, we've found the tile
                                            // subtracting by it->first is
                                            if (std::stoi(id) == value - it->first) {
                                                tinyxml2::XMLElement *imageElement = tileElement->FirstChildElement(
                                                        "image");
                                                if (imageElement != nullptr) {
                                                    const char *sourceAttribute = imageElement->Attribute("source");
                                                    if (sourceAttribute == nullptr) {
                                                        std::clog << "Invalid TMX file format: missing \"source\""
                                                                  << "attribute\n";
                                                        return;
                                                    }
                                                    sourceMap[it->first][value] = sourceAttribute;
                                                }
                                                else {
                                                    std::clog << "Invalid TMX file format: missing \"image\" element\n";
                                                    return;
                                                }
                                            }
                                        }
                                    }
                                }

                                if (not textureMap[it->first].contains(value)) {
                                    std::string temp = sourceMap[it->first][value];
                                    const std::string substr = "../../images/";

                                    std::size_t pos = temp.find(substr);
                                    if (pos != std::string::npos) {
                                        temp.erase(pos, substr.length());
                                    }

                                    textureMap[it->first][value] = TextureManager::getInstance().loadTexture(temp);
                                }

                                loop = false;
                            }
                        }
                    }
                }
            }
            else {
                std::clog << "Invalid TMX file format: missing csv data\n";
                return;
            }
        }
        else {
            std::clog << "Invalid TMX file format: missing \"data\" element\n";
            return;
        }

        layerElement = layerElement->NextSiblingElement("layer");
        map.push_back(layer);
    }

    for (std::size_t i = 0; i < map.size(); ++i) {
        std::cout << "Map " << i + 1 << ":\n";
        for (auto &j : map[i]) {
            for (int k : j) {
                std::cout << std::string(2 - std::to_string(k).length(), ' ') << k << ' ';
            }
            std::cout << '\n';
        }
        std::cout << "\n\n";
    }

    int i = 1;
    for (auto &mapping : sourceMap) {
        std::cout << "Map " << i++ << '\n';
        for (auto &source : mapping.second) {
            try {
                std::cout << '\t' << source.second << '\n';
            }
            catch (const std::exception &e) {
                std::clog << "Error: " << e.what() << '\n';
            }
        }
        std::cout << '\n';
    }
    for (auto &mapping : textureMap) {
        for (auto &texture : mapping.second) {
            SDL_DestroyTexture(texture.second);
        }
    }
}

int main() {
    SDL_SetMainReady();

    Uint32 frameStart;
    Uint32 frameTime;
    Uint32 frameDelay;

    while (Game::getInstance().isRunning()) {
        frameStart = SDL_GetTicks64();

        Game::getInstance().handleEvents();
        Game::getInstance().update();
        Game::getInstance().render();

        frameTime = SDL_GetTicks64() - frameStart;
        frameDelay = 1000 / Game::getInstance().getFps();

        if (frameDelay > frameTime) {
            SDL_Delay(frameDelay - frameTime);
        }
    }

    return 0;
}
