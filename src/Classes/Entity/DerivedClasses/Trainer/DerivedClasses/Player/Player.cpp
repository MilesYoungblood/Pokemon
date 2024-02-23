//
// Created by Miles on 10/2/2023.
//

#include "../../../../../Singleton/DerivedClasses/Game/Game.h"
#include "Player.h"

Player &Player::getPlayer() {
    static Player player;
    return player;
}

void Player::init(const char *name, int x, int y, Direction direction) {
    this->setName(name);
    this->setCoordinates(x, y);
    this->setDirection(direction);
}

void Player::addToPc(std::unique_ptr<Pokemon> toAdd) {
    for (auto &box : this->pc) {
        for (auto &pokemon : box) {
            if (pokemon == nullptr) {
                pokemon = std::move(toAdd);
            }
        }
    }
}

void Player::walk() {
    this->incWalkCounter(::State::getInstance<Overworld>().getScrollSpeed());
    ::State::getInstance<Overworld>().getCurrentMap()->shift(oppositeDirection(this->getDirection()),
                                                             ::State::getInstance<Overworld>().getScrollSpeed());

    if (this->getWalkCounter() % (Map::TILE_SIZE / 2) == 0) {
        this->updateAnimation();
    }
    if (this->getWalkCounter() % Map::TILE_SIZE == 0) {
        this->setState(Entity::State::IDLE);
        this->resetWalkCounter();

        const auto map_data = ::State::getInstance<Overworld>().getCurrentMap()->isExitPointHere(this->getX(), this->getY());
        if (map_data.has_value()) {
            ::State::getInstance<Overworld>().changeMap(map_data.value());
        }
    }
}

void Player::idle() {
    if (Player::getPlayer().getState() != Entity::State::FROZEN) {
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
            Player::getPlayer().setState(Entity::State::IDLE);
        }
        else {
            GraphicsEngine::getInstance().addGraphic<SelectionBox>(
                    SDL_Rect(50, 50, 250, 300),
                    Constants::Color::WHITE,
                    5,
                    std::vector<std::string>({ "Pokemon", "Pokedex", "Bag", "Trainer", "Save", "Options" })
            );
            Player::getPlayer().setState(Entity::State::FROZEN);
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
        this->getState() == Entity::State::FROZEN) {
        momentum = false;
    }
}

bool Player::canFight() const {
    return this->getFaintCount() < this->partySize();
}
