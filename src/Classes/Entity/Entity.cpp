//
// Created by Miles on 10/1/2023.
//

#include "../Singleton/DerivedClasses/Game/Game.h"
#include "Entity.h"

Entity::Entity(int x, int y) : x(x), y(y), screenX(x * Map::TILE_SIZE), screenY(y * Map::TILE_SIZE) {}

Entity::Entity(const char *name, int x, int y)
        : name(name), x(x), y(y), screenX(x * Map::TILE_SIZE), screenY(y * Map::TILE_SIZE) {}

void Entity::setName(const char *newName) {
    this->name = newName;
}

std::string Entity::getName() const {
    return this->name;
}

void Entity::setDialogue(const char *text) {
    std::stringstream ss(text);

    const int character_limit = 30;
    std::size_t letterCounter = 0;
    std::string buffer;
    std::string dest;

    while (std::getline(ss, buffer, ' ')) {
        letterCounter += buffer.length();

        // if the next word exceeds the limit
        if (letterCounter >= character_limit) {
            this->dialogue.push_back(dest);
            letterCounter = buffer.length();
            dest.clear();
        }
        dest.append(buffer + ' ');
    }
    if (not dest.empty()) {
        this->dialogue.push_back(dest);
    }
}

void Entity::setDialogue(const std::vector<std::string> &text) {
    for (const auto &i : text) {
        this->dialogue.push_back(i);
    }
}

std::vector<std::string> Entity::getDialogue() const {
    return this->dialogue;
}

// sets the player's map coordinates and screen coordinates
void Entity::setCoordinates(const int newX, const int newY) {
    this->x = newX;
    this->y = newY;

    this->screenX = this->x * Map::TILE_SIZE;
    this->screenY = this->y * Map::TILE_SIZE;
}

int Entity::getX() const {
    return this->x;
}

int Entity::getY() const {
    return this->y;
}

void Entity::moveForward() {
    switch (this->currentDirection) {
        case Direction::UP:
            --this->y;
            break;
        case Direction::RIGHT:
            ++this->x;
            break;
        case Direction::DOWN:
            ++this->y;
            break;
        case Direction::LEFT:
            --this->x;
            break;
    }
}

void Entity::setDirection(const Direction direction) {
    this->currentDirection = direction;
}

Direction Entity::getDirection() const {
    return this->currentDirection;
}

// makes this face the entity
void Entity::face(const Entity *entity) {
    this->setDirection(oppositeDirection(entity->getDirection()));
}

bool Entity::isFacing(Direction direction) const {
    return this->currentDirection == direction;
}

void Entity::setState(Entity::State state) {
    this->currentState = state;
}

Entity::State Entity::getState() const {
    return this->currentState;
}

bool Entity::canMoveForward(const Map *map) const {
    switch (this->currentDirection) {
        case Direction::UP:
            return not map->isObstructionHere(this->x, this->y - 1);
        case Direction::RIGHT:
            return not map->isObstructionHere(this->x + 1, this->y);
        case Direction::DOWN:
            return not map->isObstructionHere(this->x, this->y + 1);
        case Direction::LEFT:
            return not map->isObstructionHere(this->x - 1, this->y);
        default:
            throw std::invalid_argument("Invalid direction: canMoveForward()");
    }
}

// returns true if this is right next to another entity, not necessarily facing
bool Entity::isNextTo(const Entity *entity) const {
    switch (this->currentDirection) {
        case Direction::UP:
            return this->y == entity->y + 1 and this->x == entity->x;
        case Direction::DOWN:
            return this->y == entity->y - 1 and this->x == entity->x;
        case Direction::LEFT:
            return this->x == entity->x + 1 and this->y == entity->y;
        case Direction::RIGHT:
            return this->x == entity->x - 1 and this->y == entity->y;
        default:
            throw std::invalid_argument("Invalid direction: canMoveForward()");
    }
}

bool Entity::hasVisionOf(const Entity *entity) const {
    // cannot see oneself
    if (this == entity) {
        return false;
    }
    switch (this->currentDirection) {
        case Direction::UP:
            return entity->getX() == this->x and entity->getY() < this->y and entity->getY() >= this->y - this->vision;
        case Direction::DOWN:
            return entity->getX() == this->x and entity->getY() > this->y and entity->getY() <= this->y + this->vision;
        case Direction::LEFT:
            return entity->getY() == this->y and entity->getX() < this->x and entity->getX() >= this->x - this->vision;
        case Direction::RIGHT:
            return entity->getY() == this->y and entity->getX() > this->x and entity->getX() <= this->x + this->vision;
        default:
            throw std::invalid_argument("Invalid direction: canMoveForward()");
    }
}

void Entity::shiftHorizontally(int distance) {
    this->screenX += distance;
}

void Entity::shiftVertically(int distance) {
    this->screenY += distance;
}

void Entity::shift(Direction direction, int distance) {
    switch (direction) {
        case Direction::UP:
            this->screenY -= distance;
            break;
        case Direction::DOWN:
            this->screenY += distance;
            break;
        case Direction::LEFT:
            this->screenX -= distance;
            break;
        case Direction::RIGHT:
            this->screenX += distance;
            break;
    }
}

int Entity::getScreenX() const {
    return this->screenX;
}

int Entity::getScreenY() const {
    return this->screenY;
}

void Entity::setAction(void (*function)(Entity *)) {
    this->action = function;
}

void Entity::updateAnimation() {
    this->animations.at(this->currentDirection).update();
}

void Entity::update() {
    switch (this->currentState) {
        case State::WALKING:
            this->walk();
            break;

        case State::COLLIDING:
            // FIXME Entities and Trainers don't collide with exit points (they should)
            this->collide();
            break;

        case State::IDLE:
        case State::FROZEN:
            this->idle();
            break;
    }
}

void Entity::render() const {
    try {
        this->animations.at(this->currentDirection).render(SDL_Rect(this->screenX, this->screenY, Map::TILE_SIZE, Map::TILE_SIZE));
    }
    catch (const std::exception &e) {
        std::clog << "Error rendering animation: " << e.what() << '\n';
    }
}

void Entity::resetPos() {
    this->screenX = this->x * Map::TILE_SIZE;
    this->screenY = this->y * Map::TILE_SIZE;
}

bool Entity::canFight() const {
    return false;
}

void Entity::setVision(unsigned int newVision) {
    this->vision = newVision;
}

void Entity::setAnimation(Direction direction, const std::string &path) {
    this->animations[direction] = Animation(path);
}

void Entity::moveBackward() {
    switch (this->currentDirection) {
        case Direction::UP:
            ++this->y;
            break;
        case Direction::RIGHT:
            --this->x;
            break;
        case Direction::DOWN:
            --this->y;
            break;
        case Direction::LEFT:
            ++this->x;
            break;
    }
}

void Entity::walk() {
    this->walkCounter += Overworld::getInstance().getScrollSpeed();
    this->shift(this->currentDirection, Overworld::getInstance().getScrollSpeed());

    if (this->walkCounter % (Map::TILE_SIZE / 2) == 0) {
        this->animations.at(this->currentDirection).update();
    }
    if (this->walkCounter % Map::TILE_SIZE == 0) {
        this->currentState = Entity::State::IDLE;
        this->walkCounter = 0;
    }
}

void Entity::collide() {
    if (this->bumpCounter == 10 * (Game::getInstance().getFps() / 30)) {
        this->animations.at(this->currentDirection).update();
    }
    else if (this->bumpCounter == 20 * (Game::getInstance().getFps() / 30)) {
        this->currentState = Entity::State::IDLE;
        this->bumpCounter = 0;
    }
    if (this->currentState != Entity::State::IDLE) {
        ++this->bumpCounter;
    }
}

void Entity::idle() {
    this->act();
}

void Entity::act() {
    if (this->currentState == Entity::State::IDLE and this->action != nullptr) {
        this->action(this);
    }
}

void Entity::incWalkCounter(int count) {
    this->walkCounter += count;
}

void Entity::resetWalkCounter() {
    this->walkCounter = 0;
}

int Entity::getWalkCounter() const {
    return this->walkCounter;
}
