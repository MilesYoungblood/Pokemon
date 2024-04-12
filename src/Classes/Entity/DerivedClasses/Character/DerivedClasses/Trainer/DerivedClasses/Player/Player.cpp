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

bool Player::canMoveForward(const Map &map) const {
    switch (this->getDirection()) {
        case Direction::UP:
            return not map.isCollisionHere(this->getMapX(), this->getMapY() - 1);
        case Direction::RIGHT:
            return not map.isCollisionHere(this->getMapX() + 1, this->getMapY());
        case Direction::DOWN:
            return not map.isCollisionHere(this->getMapX(), this->getMapY() + 1);
        case Direction::LEFT:
            return not map.isCollisionHere(this->getMapX() - 1, this->getMapY());
        default:
            throw std::invalid_argument("Invalid direction: canMoveForward()");
    }
}

void Player::handleFaint() {
    ++this->numFainted;
}

void Player::walk() {
    this->incPixelCounter(Character::WALK_SPEED);
    Scene::getInstance<Overworld>().getCurrentMap().shift(this->getDirection(), -Character::WALK_SPEED);
    if (this->getPixelCounter() % (Map::TILE_SIZE / 2) == 0) {
        this->updateAnimation();
    }
    if (this->getPixelCounter() % Map::TILE_SIZE == 0) {
        --entitiesUpdating;
        this->setState(Character::State::IDLE);
        this->resetPixelCounter();

        const auto map_data = Scene::getInstance<Overworld>().getCurrentMap().isExitPointHere(this->getMapX(),
                                                                                              this->getMapY());
        if (map_data.has_value()) {
            Scene::getInstance<Overworld>().changeMap(map_data.value());
        }
    }
}

void Player::idle() {
    static std::unordered_map<Character *, Character::State> characterStates;

    KeyManager::getInstance().update();

    if (this->getState() != Character::State::IMMOBILE) {
        if (KeyManager::getInstance().getKey(SDL_Scancode::SDL_SCANCODE_W)) {
            Scene::getInstance<Overworld>().handleMove(SDL_Scancode::SDL_SCANCODE_W);
        }
        else if (KeyManager::getInstance().getKey(SDL_Scancode::SDL_SCANCODE_A)) {
            Scene::getInstance<Overworld>().handleMove(SDL_Scancode::SDL_SCANCODE_A);
        }
        else if (KeyManager::getInstance().getKey(SDL_Scancode::SDL_SCANCODE_S)) {
            Scene::getInstance<Overworld>().handleMove(SDL_Scancode::SDL_SCANCODE_S);
        }
        else if (KeyManager::getInstance().getKey(SDL_Scancode::SDL_SCANCODE_D)) {
            Scene::getInstance<Overworld>().handleMove(SDL_Scancode::SDL_SCANCODE_D);
        }
    }
    if (KeyManager::getInstance().getKey(SDL_Scancode::SDL_SCANCODE_ESCAPE) and
        ((this->getState() == Character::State::IMMOBILE and GraphicsEngine::getInstance().hasAny<SelectionBox>()) or
         this->getState() == Character::State::IDLE)) {
        if (GraphicsEngine::getInstance().hasAny<SelectionBox>()) {
            GraphicsEngine::getInstance().removeGraphic<SelectionBox>();
            this->setState(Character::State::IDLE);
            for (auto &entity : Scene::getInstance<Overworld>().getCurrentMap()) {
                auto *character = dynamic_cast<Character *>(entity.get());
                if (character != nullptr) {
                    character->setState(characterStates.at(character));
                    characterStates.erase(character);
                }
            }
        }
        else {
            GraphicsEngine::getInstance().addGraphic<SelectionBox>(
                    SDL_Rect(50, 50, 250, 300),
                    5,
                    std::vector<std::pair<std::string, std::function<void()>>>(
                    {
                        std::make_pair("Pokemon", nullptr),
                                std::make_pair("Pokedex", nullptr),
                                std::make_pair("Bag", nullptr),
                                std::make_pair("Trainer", nullptr),
                                std::make_pair("Save", nullptr),
                                std::make_pair("Options", nullptr)
                    }
            )
            );
            this->setState(Character::State::IMMOBILE);
            for (auto &entity : Scene::getInstance<Overworld>().getCurrentMap()) {
                auto *character = dynamic_cast<Character *>(entity.get());
                if (character != nullptr) {
                    characterStates[character] = character->getState();
                    character->setState(Character::State::IMMOBILE);
                }
            }
        }
        // re-lock the Enter key
        KeyManager::getInstance().lock(SDL_Scancode::SDL_SCANCODE_ESCAPE);

        // sets a cool-down period before the Enter key can be registered again;
        // this is needed because the program will register a button as
        // being pressed faster than the user can lift their finger
        std::thread coolDown([] -> void {
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            KeyManager::getInstance().unlock(SDL_Scancode::SDL_SCANCODE_ESCAPE);
        });
        coolDown.detach();
    }
    else if (KeyManager::getInstance().getKey(SDL_Scancode::SDL_SCANCODE_RETURN)) {
        Scene::getInstance<Overworld>().handleReturn();
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

std::vector<std::string> Player::winMessage() const {
    return std::vector<std::string>({ "You're opponent has run out of usable Pokemon!", "You won!" });
}

bool Player::canFight() const {
    return this->numFainted < this->partySize();
}
