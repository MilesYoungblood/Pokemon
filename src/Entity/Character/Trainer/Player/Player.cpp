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

Player::Player() : Trainer("Player", 7, 17, Direction::DOWN, 1) {
    this->inventory[typeid(RestoreItem).hash_code()];
    this->inventory[typeid(StatusItem).hash_code()];
    this->inventory[typeid(PokeBall).hash_code()];
    this->inventory[typeid(BattleItem).hash_code()];

    for (auto &box : this->pc) {
        box.resize(ROWS_PER_BOX, COLS_PER_BOX);
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

void Player::handleMove(const SDL_Scancode scancode) {
    if (not GraphicsEngine::getInstance().hasAny<SelectionBox>()) {
        // turns the player
        if (not this->isFacing(scancodeToDirection(scancode))) {
            this->setDirection(scancodeToDirection(scancode));
        }
        // refresh the KeyManager to check if the player is still holding down
        KeyManager::getInstance().update();

        // TODO fix: rapidly tapping to just turn does not work right now
        // if the user is still holding down the key after 10ms, begin movement
        if (KeyManager::getInstance().getKey(scancode)) {
            momentum = true;
            keyDelay.stop();
            keyDelay.reset();

            if (this->canMoveForward(Scene::getInstance<Overworld>().getCurrentMap())) {
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

void Player::handleReturn() const {
    for (auto &entity : Scene::getInstance<Overworld>().getCurrentMap()) {
        if (this->hasVisionOf(entity.get())) {
            entity->interact();
            return;
        }
    }
}

void Player::interact() {}

void Player::walk() {
    this->incPixelCounter();
    Scene::getInstance<Overworld>().getCurrentMap().shift(this->getDirection(), -WALK_SPEED);
    if (this->getPixelCounter() % 10 == 0) {
        this->updateSprite();
    }
    if (this->getPixelCounter() == 20) {
        this->setState(State::IDLE);
        this->resetPixelCounter();

        if (const auto mapData = Scene::getInstance<Overworld>().getCurrentMap().isExitPointHere(
            this->getMapPosition().getX(),
            this->getMapPosition().getY()
        ); mapData.has_value()) {
            Scene::getInstance<Overworld>().changeMap(mapData.value());
        }

        --entitiesUpdating;
        EventHandler::pushEvent();
    }
}

void Player::idle() {
    KeyManager::getInstance().update();

    if (this->getState() != State::IMMOBILE) {
        if (KeyManager::getInstance().getKey(SDL_SCANCODE_W)) {
            this->handleMove(SDL_SCANCODE_W);
        }
        else if (KeyManager::getInstance().getKey(SDL_SCANCODE_A)) {
            this->handleMove(SDL_SCANCODE_A);
        }
        else if (KeyManager::getInstance().getKey(SDL_SCANCODE_S)) {
            this->handleMove(SDL_SCANCODE_S);
        }
        else if (KeyManager::getInstance().getKey(SDL_SCANCODE_D)) {
            this->handleMove(SDL_SCANCODE_D);
        }
    }
    if (KeyManager::getInstance().getKey(SDL_SCANCODE_ESCAPE) and
        ((this->getState() == State::IMMOBILE and GraphicsEngine::getInstance().hasAny<SelectionBox>()) or
         this->getState() == State::IDLE)) {
        Scene::getInstance<Overworld>().handleEscape();
    }
    else if (KeyManager::getInstance().getKey(SDL_SCANCODE_RETURN)) {
        this->handleReturn();
    }

    // resets movement variables if you are not inputting any directions
    if (not(KeyManager::getInstance().getKey(SDL_SCANCODE_W) or
            KeyManager::getInstance().getKey(SDL_SCANCODE_A) or
            KeyManager::getInstance().getKey(SDL_SCANCODE_S) or
            KeyManager::getInstance().getKey(SDL_SCANCODE_D)) or
        this->getState() == State::IMMOBILE) {
        momentum = false;
    }
}