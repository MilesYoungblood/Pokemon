//
// Created by Miles on 10/2/2023.
//

#include "../../../../../../../Singleton/DerivedClasses/Game/Game.h"
#include "../../../../../../../Singleton/DerivedClasses/GraphicsEngine/GraphicsEngine.h"
#include "../../../../../../../Singleton/DerivedClasses/KeyManager/KeyManager.h"
#include "Player.h"

Player::Player() : Trainer("Player", 7, 17, Direction::DOWN) {}

Player &Player::getPlayer() {
    static Player player;
    return player;
}

void Player::addToPc(std::unique_ptr<Pokemon> toAdd) {
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

bool Player::canMoveForward(gsl::owner<Map *> map) const {
    switch (this->getDirection()) {
        case Direction::UP:
            return not map->isObstructionHere(this->getMapX(), this->getMapY() - 1);
        case Direction::RIGHT:
            return not map->isObstructionHere(this->getMapX() + 1, this->getMapY());
        case Direction::DOWN:
            return not map->isObstructionHere(this->getMapX(), this->getMapY() + 1);
        case Direction::LEFT:
            return not map->isObstructionHere(this->getMapX() - 1, this->getMapY());
        default:
            throw std::invalid_argument("Invalid direction: canMoveForward()");
    }
}

void Player::handleFaint() {
    ++this->numFainted;
}

void Player::walk() {
    this->incPixelCounter(::State::getInstance<Overworld>().getScrollSpeed());
    ::State::getInstance<Overworld>().getCurrentMap()->shift(oppositeDirection(this->getDirection()),
                                                             ::State::getInstance<Overworld>().getScrollSpeed());

    if (this->getWalkCounter() % (Map::TILE_SIZE / 2) == 0) {
        this->updateAnimation();
    }
    if (this->getWalkCounter() % Map::TILE_SIZE == 0) {
        this->setState(Character::State::IDLE);
        this->resetPixelCounter();

        const auto map_data = ::State::getInstance<Overworld>().getCurrentMap()->isExitPointHere(this->getMapX(),
                                                                                                 this->getMapY());
        if (map_data.has_value()) {
            ::State::getInstance<Overworld>().changeMap(map_data.value());
        }
    }
}

void Player::idle() {
    if (this->getState() != Character::State::IMMOBILE) {
        if (KeyManager::getInstance().getKey(SDL_Scancode::SDL_SCANCODE_W)) {
            ::State::getInstance<Overworld>().handleMove(SDL_Scancode::SDL_SCANCODE_W);
        }
        else if (KeyManager::getInstance().getKey(SDL_Scancode::SDL_SCANCODE_A)) {
            ::State::getInstance<Overworld>().handleMove(SDL_Scancode::SDL_SCANCODE_A);
        }
        else if (KeyManager::getInstance().getKey(SDL_Scancode::SDL_SCANCODE_S)) {
            ::State::getInstance<Overworld>().handleMove(SDL_Scancode::SDL_SCANCODE_S);
        }
        else if (KeyManager::getInstance().getKey(SDL_Scancode::SDL_SCANCODE_D)) {
            ::State::getInstance<Overworld>().handleMove(SDL_Scancode::SDL_SCANCODE_D);
        }
    }
    if (KeyManager::getInstance().getKey(SDL_Scancode::SDL_SCANCODE_ESCAPE) and
        not GraphicsEngine::getInstance().hasAny<TextBox>()) {
        if (GraphicsEngine::getInstance().hasAny<SelectionBox>()) {
            GraphicsEngine::getInstance().removeGraphic<SelectionBox>();
            this->setState(Character::State::IDLE);
        }
        else {
            GraphicsEngine::getInstance().addGraphic<SelectionBox>(
                    SDL_Rect(50, 50, 250, 300),
                    5,
                    std::vector<std::string>({ "Pokemon", "Pokedex", "Bag", "Trainer", "Save", "Options" })
            );
            this->setState(Character::State::IMMOBILE);
        }
        // re-lock the Enter key
        KeyManager::getInstance().lockKey(SDL_Scancode::SDL_SCANCODE_ESCAPE);

        // sets a cool-down period before the Enter key can be registered again;
        // this is needed because the program will register a button as
        // being pressed faster than the user can lift their finger
        std::thread coolDown([] -> void {
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            KeyManager::getInstance().unlockKey(SDL_Scancode::SDL_SCANCODE_ESCAPE);
        });
        coolDown.detach();
    }
    else if (KeyManager::getInstance().getKey(SDL_Scancode::SDL_SCANCODE_RETURN)) {
        ::State::getInstance<Overworld>().handleReturn();
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

bool Player::canFight() const {
    return this->numFainted < this->partySize();
}
