//
// Created by Miles on 10/2/2023.
//

#include "../../../../Singleton/Game/Game.h"
#include "../../../../Singleton/GraphicsEngine/GraphicsEngine.h"
#include "../../../../Singleton/EventHandler/EventHandler.h"
#include "../../../../Singleton/KeyManager/KeyManager.h"
#include "../../../../Singleton/Mixer/Mixer.h"
#include "../../../Item/BattleItem/BattleItem.h"
#include "../../../Item/PokeBall/PokeBall.h"
#include "../../../Item/RestoreItem/RestoreItem.h"
#include "../../../Item/StatusItem/StatusItem.h"
#include "Player.h"

Player &Player::getPlayer() {
    static Player player;
    return player;
}

[[maybe_unused]] void Player::addToPc(std::unique_ptr<Pokemon> toAdd) {
    for (auto &box : this->pc) {
        for (auto &row : box) {
            for (auto &pokemon : row) {
                if (pokemon == nullptr) {
                    pokemon = std::move(toAdd);
                }
            }
        }
    }
}

void Player::addItem(const std::string &id, const int n) {
    this->addItem(std::move(itemMap.at(id)(n)));
}

void Player::addItem(std::unique_ptr<Item> item) {
    try {
        // if item already exists within our inventory,
        // add the amount of the item to our item in the inventory
        if (this->inventory.at(item->getClass()).contains(item->getId())) {
            this->inventory.at(item->getClass()).at(item->getId())->add(item->getQuantity());
            return;
        }

        this->inventory.at(item->getClass())[item->getId()] = std::move(item);
    }
    catch (const std::exception &e) {
        throw std::runtime_error(std::string("Error adding item: ") + e.what() + '\n');
    }
}

bool Player::canMoveForward(const Map &map) const {
    switch (this->getDirection()) {
        case Direction::UP:
            return not map.isCollisionHere(this->getMapPosition().getX(), this->getMapPosition().getY() - 1);
        case Direction::RIGHT:
            return not map.isCollisionHere(this->getMapPosition().getX() + 1, this->getMapPosition().getY());
        case Direction::DOWN:
            return not map.isCollisionHere(this->getMapPosition().getX(), this->getMapPosition().getY() + 1);
        case Direction::LEFT:
            return not map.isCollisionHere(this->getMapPosition().getX() - 1, this->getMapPosition().getY());
        default:
            throw std::invalid_argument("Invalid direction: canMoveForward()");
    }
}

void Player::handleFaint() {
    ++this->numFainted;
}

void Player::handleSwitchOut(bool &renderFlag) {
    Scene::getInstance<Battle>().openSelectionBox([&renderFlag] -> void {
        renderFlag = true;
        GraphicsEngine::getInstance().getGraphic<TextBox>().pop();
    });
}

void Player::handleVictory() {
    Mixer::getInstance().playMusic("TrainerVictory");
}

std::vector<std::string> Player::getDefeatMessage() const {
    return std::vector<std::string>({ "You've run out of usable Pokemon!", "You blacked out!" });
}

bool Player::canFight() const {
    return this->numFainted < this->partySize();
}

void handleError(const char *name, const char *node) {
    std::clog << R"(Invalid file format in file "Player.xml": missing ")" << name << "\" " << node << '\n';
    Game::getInstance().terminate();
}

Player::Player() : Trainer("Player", 7, 17, Direction::DOWN, 1) {
    this->inventory[typeid(RestoreItem).hash_code()];
    this->inventory[typeid(StatusItem).hash_code()];
    this->inventory[typeid(PokeBall).hash_code()];
    this->inventory[typeid(BattleItem).hash_code()];

    for (auto &box : this->pc) {
        box.resize(ROWS_PER_BOX, COLS_PER_BOX);
    }

    if (tinyxml2::XMLDocument xmlFile; xmlFile.LoadFile("../assets/data/Player/Player.xml") == tinyxml2::XMLError::XML_SUCCESS) {
        tinyxml2::XMLElement *xmlElement = xmlFile.FirstChildElement("xml");
        if (xmlElement == nullptr) {
            handleError("xml", "element");
            return;
        }

        tinyxml2::XMLElement *dataElement = xmlElement->FirstChildElement("data");
        if (dataElement == nullptr) {
            handleError("data", "element");
            return;
        }

        const tinyxml2::XMLElement *nameElement = dataElement->FirstChildElement("name");
        {
            if (nameElement == nullptr) {
                handleError("name", "element");
                return;
            }

            const char *name = nameElement->GetText();
            if (name == nullptr) {
                handleError("name", "text");
                return;
            }

            this->setName(name);
        }

        const tinyxml2::XMLElement *positionElement = nameElement->NextSiblingElement("position");
        {
            if (positionElement == nullptr) {
                handleError("position", "element");
                return;
            }

            const int x = positionElement->IntAttribute("x", -1);
            if (x == -1) {
                handleError("x", "attribute");
                return;
            }

            const int y = positionElement->IntAttribute("y", -1);
            if (y == -1) {
                handleError("y", "attribute");
                return;
            }

            this->getMapPosition().setPosition(x, y);
        }

        const tinyxml2::XMLElement *directionElement = positionElement->NextSiblingElement("direction");
        {
            if (directionElement == nullptr) {
                handleError("direction", "element");
                return;
            }

            int direction = directionElement->IntText(-1);
            if (direction == -1) {
                handleError("direction", "text");
                return;
            }

            this->setDirection(static_cast<Direction>(direction));
        }

        const tinyxml2::XMLElement *partyElement = directionElement->NextSiblingElement("party");
        {
            int i = 0;
            for (const tinyxml2::XMLElement *pokemonElement = partyElement->FirstChildElement("pokemon");
                 pokemonElement != nullptr; pokemonElement = pokemonElement->NextSiblingElement("pokemon")) {
                const char *pokemonId = pokemonElement->Attribute("id");
                if (pokemonId == nullptr) {
                    handleError("id", "attribute");
                    return;
                }
                this->addPokemon(pokemonId);

                const tinyxml2::XMLElement *movesetElement = pokemonElement->FirstChildElement("move_set");
                if (movesetElement == nullptr) {
                    handleError("move_set", "element");
                    return;
                }

                for (const tinyxml2::XMLElement *moveElement = movesetElement->FirstChildElement("move");
                     moveElement != nullptr; moveElement = moveElement->NextSiblingElement("move")) {
                    const char *moveId = moveElement->Attribute("id");
                    if (moveId == nullptr) {
                        handleError("id", "attribute");
                        return;
                    }

                    this->operator[](i).learnMove(moveId);
                }
                ++i;
            }
        }

        const tinyxml2::XMLElement *inventoryElement = partyElement->NextSiblingElement("inventory");
        if (inventoryElement == nullptr) {
            handleError("inventory", "element");
            return;
        }

        for (int i = 0; i < inventoryElement->ChildElementCount(); ++i) {
        }
    }
}

/// \brief converts a SDL_Scancode to a Direction
/// \param scancode the scancode to convert
/// \return the corresponding Direction
Direction scancodeToDirection(const SDL_Scancode scancode) {
    switch (scancode) {
        case SDL_SCANCODE_W:
            return Direction::UP;
        case SDL_SCANCODE_A:
            return Direction::LEFT;
        case SDL_SCANCODE_S:
            return Direction::DOWN;
        case SDL_SCANCODE_D:
            return Direction::RIGHT;
        default:
            throw std::invalid_argument("Invalid argument passed into scancodeToDirection");
    }
}

void Player::handleMove(const Map &map, const SDL_Scancode scancode) {
    if (not GraphicsEngine::getInstance().hasAny<SelectionBox>()) {
        // turns the player
        if (not this->isFacing(scancodeToDirection(scancode))) {
            this->setDirection(scancodeToDirection(scancode));
        }

        // TODO fix: rapidly tapping to just turn does not work right now
        if (KeyManager::getInstance().getKey(scancode)) {
            keyDelay.stop();
            keyDelay.reset();

            if (this->canMoveForward(map)) {
                this->moveForward();
                this->setState(State::WALKING);
            }
            else {
                this->setState(State::COLLIDING);
                this->updateSprite();

                Mixer::getInstance().playSound("bump");
            }

            ++entitiesUpdating;
        }
    }
}

void Player::handleReturn(Map &map) const {
    for (auto &entity : map) {
        if (this->hasVisionOf(entity.get())) {
            entity->interact(map);
            return;
        }
    }
}

void Player::interact(Map &map) {}

void Player::walk(Map &map) {
    this->incPixelCounter();
    map.shift(this->getDirection(), -WALK_SPEED);
    if (this->getPixelCounter() % 10 == 0) {
        this->updateSprite();
    }
    if (this->getPixelCounter() == 20) {
        this->setState(State::IDLE);
        this->resetPixelCounter();

        if (const auto mapData = map.isExitPointHere(
            this->getMapPosition().getX(),
            this->getMapPosition().getY()
        ); mapData.has_value()) {
            Scene::getInstance<Overworld>().changeMap(mapData.value());
        }

        --entitiesUpdating;
        EventHandler::pushEvent();
    }
}

void Player::idle(Map &map) {
    KeyManager::getInstance().update();

    if (this->getState() != State::IMMOBILE) {
        if (KeyManager::getInstance().getKey(SDL_SCANCODE_W)) {
            this->handleMove(map, SDL_SCANCODE_W);
        }
        else if (KeyManager::getInstance().getKey(SDL_SCANCODE_A)) {
            this->handleMove(map, SDL_SCANCODE_A);
        }
        else if (KeyManager::getInstance().getKey(SDL_SCANCODE_S)) {
            this->handleMove(map, SDL_SCANCODE_S);
        }
        else if (KeyManager::getInstance().getKey(SDL_SCANCODE_D)) {
            this->handleMove(map, SDL_SCANCODE_D);
        }
    }
    if (KeyManager::getInstance().getKey(SDL_SCANCODE_ESCAPE) and
        ((this->getState() == State::IMMOBILE and GraphicsEngine::getInstance().hasAny<SelectionBox>()) or
         this->getState() == State::IDLE)) {
        Scene::getInstance<Overworld>().handleEscape();
    }
    else if (KeyManager::getInstance().getKey(SDL_SCANCODE_RETURN)) {
        this->handleReturn(map);
    }
}
