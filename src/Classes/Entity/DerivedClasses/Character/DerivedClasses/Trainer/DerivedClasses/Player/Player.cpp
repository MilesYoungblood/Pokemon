//
// Created by Miles on 10/2/2023.
//

#include "../../../../../../../Singleton/DerivedClasses/Game/Game.h"
#include "../../../../../../../Singleton/DerivedClasses/GraphicsEngine/GraphicsEngine.h"
#include "../../../../../../../Singleton/DerivedClasses/KeyManager/KeyManager.h"
#include "../../../../../../../Singleton/DerivedClasses/Mixer/Mixer.h"
#include "Player.h"

Player::Player() : Trainer("Player", 7, 17, Direction::DOWN, 1) {}

/// \brief converts a SDL_Scancode to a Direction
/// \param scancode the scancode to convert
/// \return the corresponding Direction
Direction scancodeToDirection(SDL_Scancode scancode) {
    switch (scancode) {
        case SDL_Scancode::SDL_SCANCODE_W:
            return Direction::UP;
        case SDL_Scancode::SDL_SCANCODE_A:
            return Direction::LEFT;
        case SDL_Scancode::SDL_SCANCODE_S:
            return Direction::DOWN;
        case SDL_Scancode::SDL_SCANCODE_D:
            return Direction::RIGHT;
        default:
            throw std::invalid_argument("Invalid argument passed into scancodeToDirection");
    }
}

void Player::handleMove(SDL_Scancode scancode) {
    if (not GraphicsEngine::getInstance().hasAny<SelectionBox>()) {
        // turns the player
        if (not this->isFacing(scancodeToDirection(scancode))) {
            this->setDirection(scancodeToDirection(scancode));
        }
        // refresh the KeyManager to check if the player is still holding down
        KeyManager::getInstance().update();

        // if the user is still holding down the key after 10ms, begin movement
        if (KeyManager::getInstance().getKey(scancode)) {
            momentum = true;
            keyDelay.stop();
            keyDelay.reset();

            if (this->canMoveForward(Scene::getInstance<Overworld>().getCurrentMap())) {
                this->moveForward();
                this->setState(Character::State::WALKING);
            }
            else {
                this->setState(Character::State::COLLIDING);
                this->updateAnimation();

                Mixer::getInstance().playSound("bump");
            }

            ++entitiesUpdating;
        }
    }
}

void Player::handleReturn() {
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
    Scene::getInstance<Overworld>().getCurrentMap().shift(this->getDirection(), -Character::WALK_SPEED);
    if (this->getPixelCounter() % 10 == 0) {
        this->updateAnimation();
    }
    if (this->getPixelCounter() == 20) {
        this->setState(Character::State::IDLE);
        this->resetPixelCounter();

        const auto map_data = Scene::getInstance<Overworld>().getCurrentMap().isExitPointHere(
                this->getMapPosition().getX(),
                this->getMapPosition().getY()
        );
        if (map_data.has_value()) {
            Scene::getInstance<Overworld>().changeMap(map_data.value());
        }

        --entitiesUpdating;
        Overworld::pushEvent();
    }
}

void Player::idle() {
    KeyManager::getInstance().update();

    if (this->getState() != Character::State::IMMOBILE) {
        if (KeyManager::getInstance().getKey(SDL_Scancode::SDL_SCANCODE_W)) {
            this->handleMove(SDL_Scancode::SDL_SCANCODE_W);
        }
        else if (KeyManager::getInstance().getKey(SDL_Scancode::SDL_SCANCODE_A)) {
            this->handleMove(SDL_Scancode::SDL_SCANCODE_A);
        }
        else if (KeyManager::getInstance().getKey(SDL_Scancode::SDL_SCANCODE_S)) {
            this->handleMove(SDL_Scancode::SDL_SCANCODE_S);
        }
        else if (KeyManager::getInstance().getKey(SDL_Scancode::SDL_SCANCODE_D)) {
            this->handleMove(SDL_Scancode::SDL_SCANCODE_D);
        }
    }
    if (KeyManager::getInstance().getKey(SDL_Scancode::SDL_SCANCODE_ESCAPE) and
        ((this->getState() == Character::State::IMMOBILE and GraphicsEngine::getInstance().hasAny<SelectionBox>()) or
         this->getState() == Character::State::IDLE)) {
        Scene::getInstance<Overworld>().handleEscape();
    }
    else if (KeyManager::getInstance().getKey(SDL_Scancode::SDL_SCANCODE_RETURN)) {
        this->handleReturn();
    }

    // resets movement variables if you are not inputting any directions
    if (not(KeyManager::getInstance().getKey(SDL_Scancode::SDL_SCANCODE_W) or
            KeyManager::getInstance().getKey(SDL_Scancode::SDL_SCANCODE_A) or
            KeyManager::getInstance().getKey(SDL_Scancode::SDL_SCANCODE_S) or
            KeyManager::getInstance().getKey(SDL_Scancode::SDL_SCANCODE_D)) or
        this->getState() == Character::State::IMMOBILE) {
        momentum = false;
    }
}

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

void Player::handleVictory() {
    Mixer::getInstance().playMusic("TrainerVictory");
}

std::vector<std::string> Player::winMessage(const Trainer *trainer) const {
    return std::vector<std::string>({ "You defeated " + trainer->getId() + ' ' + trainer->getName() + '!' });
}

bool Player::canFight() const {
    return this->numFainted < this->partySize();
}
