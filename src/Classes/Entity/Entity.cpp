//
// Created by Miles on 10/1/2023.
//

#include "../Singleton/DerivedClasses/Game/Game.h"
#include "Entity.h"

Entity::Entity(Entity::Id id, int x, int y) : id(id), x(x), y(y), screenX(x * Map::TILE_SIZE), screenY(y * Map::TILE_SIZE) {}

Entity::Entity(Entity::Id id, const char *name, int x, int y)
        : id(id), name(name), x(x), y(y), screenX(x * Map::TILE_SIZE), screenY(y * Map::TILE_SIZE) {}

Entity::Entity(Entity::Id id, const char *name, int x, int y, Direction direction)
        : id(id), name(name), x(x), y(y), screenX(x * Map::TILE_SIZE), screenY(y * Map::TILE_SIZE), currentDirection(direction) {}

Entity::Entity(Entity::Id id, const char *name, int x, int y, Direction direction, int vision)
        : id(id), name(name), x(x), y(y), screenX(x * Map::TILE_SIZE), screenY(y * Map::TILE_SIZE), currentDirection(direction), vision(vision) {}

Entity::~Entity() {
    for (auto &set : Entity::sprites) {
        for (auto &animation : set.second) {
            SDL_DestroyTexture(animation.second.sprite);
            if (strlen(SDL_GetError()) > 0) {
                std::clog << "Unable to destroy sprite: " << SDL_GetError() << '\n';
                SDL_ClearError();
            }
        }
    }
}

void Entity::init() {
    auto populate = [](Entity::Id entityId, Direction direction, const char *path) -> void {
        const std::string base("sprites/Hilbert/HilbertSpriteSheet");

        const auto data = TextureManager::getInstance().loadTextureData(base + path + ".png");
        Entity::sprites[entityId][direction] = SpriteData(
                std::get<0>(data),
                std::get<1>(data) / Map::TILE_SIZE,
                std::get<2>(data) / Map::TILE_SIZE
        );
    };

    populate(Entity::Id::PLAYER, Direction::UP, "Up");
    populate(Entity::Id::PLAYER, Direction::DOWN, "Down");
    populate(Entity::Id::PLAYER, Direction::LEFT, "Left");
    populate(Entity::Id::PLAYER, Direction::RIGHT, "Right");

    populate(Entity::Id::YOUNGSTER, Direction::UP, "Up");
    populate(Entity::Id::YOUNGSTER, Direction::DOWN, "Down");
    populate(Entity::Id::YOUNGSTER, Direction::LEFT, "Left");
    populate(Entity::Id::YOUNGSTER, Direction::RIGHT, "Right");
}

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
    ++this->sprite.currentCol;

    if (this->sprite.currentCol == Entity::sprites.at(this->id).at(this->currentDirection).numCols) {
        this->sprite.currentCol = 0;

        ++this->sprite.currentRow;
        if (this->sprite.currentRow == Entity::sprites.at(this->id).at(this->currentDirection).numRows) {
            this->sprite.currentRow = 0;
        }
    }
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
        TextureManager::getInstance().drawFrame(
                Entity::sprites.at(this->id).at(this->currentDirection).sprite,
                SDL_Rect(this->screenX, this->screenY, Map::TILE_SIZE, Map::TILE_SIZE),
                this->sprite.currentCol,
                this->sprite.currentRow
        );
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

void Entity::walk() {
    this->walkCounter += ::State::getInstance<Overworld>().getScrollSpeed();
    this->shift(this->currentDirection, ::State::getInstance<Overworld>().getScrollSpeed());

    if (this->walkCounter % (Map::TILE_SIZE / 2) == 0) {
        this->updateAnimation();
    }
    if (this->walkCounter % Map::TILE_SIZE == 0) {
        this->currentState = Entity::State::IDLE;
        this->walkCounter = 0;
    }
}

void Entity::collide() {
    if (this->bumpCounter == 10 * (Game::getInstance().getFps() / 30)) {
        this->updateAnimation();
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
