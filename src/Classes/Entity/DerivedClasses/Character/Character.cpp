//
// Created by Miles on 10/1/2023.
//

#include "../../../Singleton/DerivedClasses/Game/Game.h"
#include "../../../Singleton/DerivedClasses/GraphicsEngine/GraphicsEngine.h"
#include "../../../Singleton/DerivedClasses/Mixer/Mixer.h"
#include "../../../Singleton/DerivedClasses/KeyManager/KeyManager.h"
#include "Character.h"

Character::Character(const char *id, int x, int y, Direction direction)
        : Entity(x, y), id(id), currentDirection(direction) {}

Character::Character(const char *id, const char *name, int x, int y, Direction direction, int vision)
        : Entity(x, y), id(id), name(name), currentDirection(direction), vision(vision) {}

void Character::init() {
    auto populate = [](const char *entityId, Direction direction, const char *path) -> void {
        const std::string base("sprites/Hilbert/HilbertSpriteSheet");

        const auto data = TextureManager::getInstance().loadTextureData(base + path + ".png");
        Character::sprites[entityId].at(static_cast<std::size_t>(direction)) = Sprite::Sheet(
                std::get<0>(data),
                std::get<1>(data) / Map::TILE_SIZE,
                std::get<2>(data) / Map::TILE_SIZE
        );
    };

    populate("Player", Direction::UP, "Up");
    populate("Player", Direction::DOWN, "Down");
    populate("Player", Direction::LEFT, "Left");
    populate("Player", Direction::RIGHT, "Right");

    populate("Youngster", Direction::UP, "Up");
    populate("Youngster", Direction::DOWN, "Down");
    populate("Youngster", Direction::LEFT, "Left");
    populate("Youngster", Direction::RIGHT, "Right");
}

void Character::clean() {
    for (auto &set : Character::sprites) {
        for (auto &animation : set.second) {
            if (animation.sprite != nullptr) {
                SDL_DestroyTexture(animation.sprite);
                if (strlen(SDL_GetError()) > 0) {
                    std::clog << "Unable to destroy sprite: " << SDL_GetError() << '\n';
                    SDL_ClearError();
                }
            }
        }
    }
}

void Character::setName(const char *newName) {
    this->name = newName;
}

std::string Character::getName() const {
    return this->name;
}

void Character::setDialogue(const char *text) {
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

void Character::setDialogue(const std::vector<std::string> &text) {
    for (const auto &i : text) {
        this->dialogue.push_back(i);
    }
}

std::vector<std::string> Character::getDialogue() const {
    return this->dialogue;
}

void Character::moveForward() {
    switch (this->currentDirection) {
        case Direction::UP:
            this->translateY(false);
            break;
        case Direction::RIGHT:
            this->translateX(true);
            break;
        case Direction::DOWN:
            this->translateY(true);
            break;
        case Direction::LEFT:
            this->translateX(false);
            break;
    }
}

void Character::setDirection(const Direction direction) {
    this->currentDirection = direction;
}

Direction Character::getDirection() const {
    return this->currentDirection;
}

// makes this face the entity
void Character::face(const Character *entity) {
    this->setDirection(oppositeDirection(entity->getDirection()));
}

bool Character::isFacing(Direction direction) const {
    return this->currentDirection == direction;
}

void Character::setState(Character::State state) {
    this->currentState = state;
}

Character::State Character::getState() const {
    return this->currentState;
}

bool Character::canMoveForward(gsl::owner<Map *> map) const {
    switch (this->currentDirection) {
        case Direction::UP:
            return not map->isObstructionHere(this->getMapX(), this->getMapY() - 1) and map->isExitPointHere(this->getMapX(), this->getMapY() - 1) == std::nullopt;
        case Direction::RIGHT:
            return not map->isObstructionHere(this->getMapX() + 1, this->getMapY()) and map->isExitPointHere(this->getMapX() + 1, this->getMapY()) == std::nullopt;
        case Direction::DOWN:
            return not map->isObstructionHere(this->getMapX(), this->getMapY() + 1) and map->isExitPointHere(this->getMapX(), this->getMapY() + 1) == std::nullopt;
        case Direction::LEFT:
            return not map->isObstructionHere(this->getMapX() - 1, this->getMapY()) and map->isExitPointHere(this->getMapX() - 1, this->getMapY()) == std::nullopt;
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
            return entity->getMapX() == this->getMapX() and entity->getMapY() < this->getMapY() and entity->getMapY() >= this->getMapY() - this->vision;
        case Direction::DOWN:
            return entity->getMapX() == this->getMapX() and entity->getMapY() > this->getMapY() and entity->getMapY() <= this->getMapY() + this->vision;
        case Direction::LEFT:
            return entity->getMapY() == this->getMapY() and entity->getMapX() < this->getMapX() and entity->getMapX() >= this->getMapX() - this->vision;
        case Direction::RIGHT:
            return entity->getMapY() == this->getMapY() and entity->getMapX() > this->getMapX() and entity->getMapX() <= this->getMapX() + this->vision;
        default:
            throw std::invalid_argument("Invalid direction: canMoveForward()");
    }
}

void Character::setAction(void (*function)(Character *)) {
    this->action = function;
}

void Character::interact() {
    // if the player manually clicked Enter
    // (the trainer will have opened the TextBox if it has contacted the player already)
    if (not GraphicsEngine::getInstance().hasAny<TextBox>()) {
        KeyManager::getInstance().lockKey(SDL_Scancode::SDL_SCANCODE_RETURN);

        Player::getPlayer().setState(Character::State::IMMOBILE);
        this->face(&Player::getPlayer());

        // only create the textbox here if the trainer cannot fight;
        // the program will loop back to the trainer's update() in the next cycle
        // and create it there if the trainer can fight
        if (not this->canFight()) {
            this->currentState = Character::State::IMMOBILE;
            Overworld::createTextBox(this->getDialogue());
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

                Player::getPlayer().setState(Character::State::IDLE);
                this->setState(Character::State::IDLE);
            }
        }
        // re-lock the Enter key
        KeyManager::getInstance().lockKey(SDL_Scancode::SDL_SCANCODE_RETURN);

        // sets a cool-down period before the Enter key can be registered again;
        // this is needed because the program will register a button as
        // being pressed faster than the user can lift their finger
        std::thread coolDown([] -> void {
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            KeyManager::getInstance().unlockKey(SDL_Scancode::SDL_SCANCODE_RETURN);
        });
        coolDown.detach();

        keyDelay.reset();
    }
}

void Character::updateAnimation() {
    ++this->sprite.currentCol;

    if (this->sprite.currentCol == Character::sprites.at(this->id).at(static_cast<std::size_t>(this->currentDirection)).numCols) {
        this->sprite.currentCol = 0;

        ++this->sprite.currentRow;
        if (this->sprite.currentRow == Character::sprites.at(this->id).at(static_cast<std::size_t>(this->currentDirection)).numRows) {
            this->sprite.currentRow = 0;
        }
    }
}

void Character::update() {
    switch (this->currentState) {
        case State::WALKING:
            this->walk();
            break;

        case State::COLLIDING:
            this->collide();
            break;

        case State::IDLE:
        case State::IMMOBILE:
            this->idle();
            break;
    }
}

void Character::render() const {
    TextureManager::getInstance().drawFrame(
            Character::sprites.at(this->id).at(static_cast<std::size_t>(this->currentDirection)).sprite,
            SDL_Rect(this->getScreenX(), this->getScreenY(), Map::TILE_SIZE, Map::TILE_SIZE),
            this->sprite.currentCol,
            this->sprite.currentRow
    );
}

bool Character::canFight() const {
    return false;
}

bool Character::isTrainer() const {
    return false;
}

void Character::walk() {
    this->pixelCounter += Character::WALK_SPEED;
    this->shift(this->currentDirection, Character::WALK_SPEED);

    if (this->pixelCounter % (Map::TILE_SIZE / 2) == 0) {
        this->updateAnimation();
    }
    if (this->pixelCounter % Map::TILE_SIZE == 0) {
        this->currentState = Character::State::IDLE;
        this->pixelCounter = 0;
    }
}

void Character::collide() {
    if (this->pixelCounter == 10 * (Game::getInstance().getFps() / 30)) {
        this->updateAnimation();
    }
    else if (this->pixelCounter == 20 * (Game::getInstance().getFps() / 30)) {
        this->currentState = Character::State::IDLE;
        this->pixelCounter = 0;
    }
    if (this->currentState != Character::State::IDLE) {
        ++this->pixelCounter;
    }
}

void Character::idle() {
    this->act();
}

void Character::act() {
    if (this->currentState == Character::State::IDLE and this->action != nullptr) {
        this->action(this);
    }
}

void Character::incPixelCounter(int n) {
    this->pixelCounter += n;
}

void Character::resetPixelCounter() {
    this->pixelCounter = 0;
}

int Character::getWalkCounter() const {
    return this->pixelCounter;
}
