//
// Created by Miles on 10/1/2023.
//

#include "../../../../Functions/GeneralFunctions.h"
#include "../../../Singleton/DerivedClasses/Game/Game.h"
#include "../../../Singleton/DerivedClasses/GraphicsEngine/GraphicsEngine.h"
#include "../../../Singleton/DerivedClasses/TextureManager/TextureManager.h"
#include "../../../Singleton/DerivedClasses/Mixer/Mixer.h"
#include "../../../Singleton/DerivedClasses/KeyManager/KeyManager.h"
#include "Character.h"

Character::Character(const char *id, const int x, const int y, const Direction direction, const int vision)
        : Entity(x, y), id(id), vision(vision), currentDirection(direction) {}

Character::Character(const char *id, const char *name, const int x, const int y, const Direction direction, const int vision)
        : Entity(x, y), name(name), id(id), vision(vision), currentDirection(direction) {}

void Character::setName(const char *newName) {
    this->name = newName;
}

std::string Character::getName() const {
    return this->name;
}

std::string Character::getId() const {
    return this->id;
}

void Character::setDialogue(const std::vector<std::string> &text) {
    this->dialogue = text;
}

void Character::setState(const State x) {
    this->currentState = x;
}

Character::State Character::getState() const {
    return this->currentState;
}

void Character::gainAutonomy() {
    this->intelligence = std::make_unique<Project::Intelligence>(
            [this] -> void { this->act(); },
            [this] -> bool { return this->currentState == State::IDLE; },
            [] -> int { return generateInteger(2, 4); }
    );
}

void Character::update() {
    switch (this->currentState) {
        case State::WALKING:
            this->walk();
            break;

        case State::COLLIDING:
            if (this->pixelCounter == 10 * (Game::getInstance().getFps() / 30)) {
                this->updateAnimation();
            }
            else if (this->pixelCounter == 20 * (Game::getInstance().getFps() / 30)) {
                this->currentState = State::IDLE;
                this->pixelCounter = 0;

                --entitiesUpdating;
                if (this->intelligence != nullptr) {
                    this->intelligence->alert();
                }
                Overworld::pushEvent();
            }
            if (this->currentState != State::IDLE) {
                ++this->pixelCounter;
            }
            break;

        case State::IDLE:
        case State::IMMOBILE:
            this->idle();
            break;

        default:
            std::clog << "Invalid argument in function Character::update()\n";
            Game::getInstance().terminate();
            break;
    }
}

void Character::render() const {
    TextureManager::getInstance().drawFrame(
            Scene::getInstance<Overworld>().getCurrentMap().getSpriteSheet(this->id, this->currentDirection).sprite,
            SDL_Rect(this->getScreenPosition().getX(), this->getScreenPosition().getY(), Map::TILE_SIZE, Map::TILE_SIZE),
            this->sprite.currentCol,
            this->sprite.currentRow
    );
}

std::vector<std::string> Character::getDialogue() const {
    return this->dialogue;
}

void Character::moveForward() {
    switch (this->currentDirection) {
        case Direction::UP:
            this->getMapPosition().translateY(-1);
            break;
        case Direction::RIGHT:
            this->getMapPosition().translateX(1);
            break;
        case Direction::DOWN:
            this->getMapPosition().translateY(1);
            break;
        case Direction::LEFT:
            this->getMapPosition().translateX(-1);
            break;
        default:
            std::clog << "Invalid direction " << this->currentDirection << '\n';
            Game::getInstance().terminate();
    }
}

void Character::setDirection(const Direction x) {
    this->currentDirection = x;
}

Direction Character::getDirection() const {
    return this->currentDirection;
}

// makes this face the entity
void Character::face(const Character *character) {
    switch (character->currentDirection) {
        case Direction::UP:
            this->currentDirection = Direction::DOWN;
            break;
        case Direction::DOWN:
            this->currentDirection = Direction::UP;
            break;
        case Direction::LEFT:
            this->currentDirection = Direction::RIGHT;
            break;
        case Direction::RIGHT:
            this->currentDirection = Direction::LEFT;
            break;
        default:
            std::clog << "Invalid direction " << character->currentDirection << '\n';
            Game::getInstance().terminate();
    }
}

bool Character::isFacing(const Direction direction) const {
    return this->currentDirection == direction;
}

bool Character::canMoveForward(const Map &map) const {
    switch (this->currentDirection) {
        case Direction::UP:
            return not map.isCollisionHere(this->getMapPosition().getX(), this->getMapPosition().getY() - 1) and not map.isExitPointHere(this->getMapPosition().getX(), this->getMapPosition().getY() - 1).has_value();
        case Direction::RIGHT:
            return not map.isCollisionHere(this->getMapPosition().getX() + 1, this->getMapPosition().getY()) and not map.isExitPointHere(this->getMapPosition().getX() + 1, this->getMapPosition().getY()).has_value();
        case Direction::DOWN:
            return not map.isCollisionHere(this->getMapPosition().getX(), this->getMapPosition().getY() + 1) and not map.isExitPointHere(this->getMapPosition().getX(), this->getMapPosition().getY() + 1).has_value();
        case Direction::LEFT:
            return not map.isCollisionHere(this->getMapPosition().getX() - 1, this->getMapPosition().getY()) and not map.isExitPointHere(this->getMapPosition().getX() - 1, this->getMapPosition().getY()).has_value();
        default:
            throw std::invalid_argument("Invalid direction: canMoveForward()");
    }
}

bool Character::hasVisionOf(const Entity *entity) const {
    // cannot see oneself
    if (this == entity) {
        return false;
    }
    switch (this->currentDirection) {
        case Direction::UP:
            return entity->getMapPosition().getX() == this->getMapPosition().getX() and entity->getMapPosition().getY() < this->getMapPosition().getY() and entity->getMapPosition().getY() >= this->getMapPosition().getY() - this->vision;
        case Direction::DOWN:
            return entity->getMapPosition().getX() == this->getMapPosition().getX() and entity->getMapPosition().getY() > this->getMapPosition().getY() and entity->getMapPosition().getY() <= this->getMapPosition().getY() + this->vision;
        case Direction::LEFT:
            return entity->getMapPosition().getY() == this->getMapPosition().getY() and entity->getMapPosition().getX() < this->getMapPosition().getX() and entity->getMapPosition().getX() >= this->getMapPosition().getX() - this->vision;
        case Direction::RIGHT:
            return entity->getMapPosition().getY() == this->getMapPosition().getY() and entity->getMapPosition().getX() > this->getMapPosition().getX() and entity->getMapPosition().getX() <= this->getMapPosition().getX() + this->vision;
        default:
            throw std::invalid_argument("Invalid direction: canMoveForward()");
    }
}

void Character::act() {
    switch (generateInteger(1, 4)) {
        case 1:
            this->face(this);
            std::cout << this->name << " made decision 1\n";
            break;

        case 2:
            if (this->isFacing(Direction::UP) or this->isFacing(Direction::DOWN)) {
                binomial() ? this->setDirection(Direction::LEFT) : this->setDirection(Direction::RIGHT);
            }
            else {
                binomial() ? this->setDirection(Direction::UP) : this->setDirection(Direction::DOWN);
            }
            std::cout << this->name << " made decision 2\n";
            break;

        default:
            if (this->canMoveForward(Scene::getInstance<Overworld>().getCurrentMap())) {
                this->moveForward();
                this->setState(State::WALKING);

                if (this->hasVisionOf(&Player::getPlayer()) and
                    (Player::getPlayer().getState() == State::IDLE)) {
                    Player::getPlayer().setState(State::IMMOBILE);
                }
            }
            else {
                this->setState(State::COLLIDING);
                this->updateAnimation();
            }
            ++entitiesUpdating;
            std::cout << this->name << " made decision 3\n";
            break;
    }
}

void Character::loseAutonomy() {
    this->intelligence.reset(nullptr);
}

void Character::interact() {
    // if the player manually clicked Enter
    // (the trainer will have opened the TextBox if it has contacted the player already)
    if (not GraphicsEngine::getInstance().hasAny<TextBox>()) {
        KeyManager::getInstance().lock(SDL_SCANCODE_RETURN);

        Player::getPlayer().setState(State::IMMOBILE);
        this->currentState = State::IMMOBILE;
        this->face(&Player::getPlayer());

        if (this->intelligence == nullptr) {
            Overworld::createTextBox(this->dialogue);
        }
    }
    else if (not GraphicsEngine::getInstance().getGraphic<TextBox>().isPrinting()) {
        // if the textbox still has messages to print
        if (not GraphicsEngine::getInstance().getGraphic<TextBox>().empty()) {
            GraphicsEngine::getInstance().getGraphic<TextBox>().pop();

            // the 'accept' sound effect will play for every pop except the last
            if (not GraphicsEngine::getInstance().getGraphic<TextBox>().empty()) {
                Mixer::getInstance().playSound("accept");
            }
            else {
                GraphicsEngine::getInstance().removeGraphic<TextBox>();

                if (Player::getPlayer().canFight() and this->canFight()) {
                    Game::getInstance().changeScene(Scene::Id::BATTLE);
                    Game::getInstance().setRenderColor(Constants::Color::WHITE);

                    Scene::getInstance<Battle>().init(dynamic_cast<Trainer *>(this));

                    Mixer::getInstance().playMusic("TrainerBattle");
                    --entitiesUpdating;
                }
                else {
                    Player::getPlayer().setState(State::IDLE);
                    this->currentState = State::IDLE;
                }
            }
        }
        // re-lock the Enter key
        KeyManager::getInstance().lock(SDL_SCANCODE_RETURN);

        // sets a cool-down period before the Enter key can be registered again;
        // this is needed because the program will register a button as
        // being pressed faster than the user can lift their finger
        std::thread coolDown([] -> void {
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            KeyManager::getInstance().unlock(SDL_SCANCODE_RETURN);
        });
        coolDown.detach();

        keyDelay.reset();
    }
}

void Character::walk() {
    ++this->pixelCounter;

    this->getScreenPosition().translate(this->currentDirection, WALK_SPEED);

    if (this->pixelCounter % 10 == 0) {
        this->updateAnimation();
    }
    if (this->pixelCounter == 20) {
        this->currentState = State::IDLE;
        this->pixelCounter = 0;

        --entitiesUpdating;
        if (this->intelligence != nullptr) {
            this->intelligence->alert();
        }
        Overworld::pushEvent();
    }
}

void Character::idle() {
    if (this->intelligence != nullptr) {
        this->intelligence->tryActing();
    }
}

void Character::updateAnimation() {
    ++this->sprite.currentCol;

    if (this->sprite.currentCol == Scene::getInstance<Overworld>().getCurrentMap().getSpriteSheet(this->id, this->currentDirection).numCols) {
        this->sprite.currentCol = 0;

        ++this->sprite.currentRow;
        if (this->sprite.currentRow == Scene::getInstance<Overworld>().getCurrentMap().getSpriteSheet(this->id, this->currentDirection).numRows) {
            this->sprite.currentRow = 0;
        }
    }
}

bool Character::canFight() const {
    return false;
}

bool Character::isTrainer() const {
    return false;
}

void Character::incPixelCounter() {
    ++this->pixelCounter;
}

void Character::resetPixelCounter() {
    this->pixelCounter = 0;
}

int Character::getPixelCounter() const {
    return this->pixelCounter;
}
