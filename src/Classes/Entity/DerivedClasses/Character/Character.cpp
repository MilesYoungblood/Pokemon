//
// Created by Miles on 10/1/2023.
//

#include "../../../Singleton/DerivedClasses/Game/Game.h"
#include "../../../Singleton/DerivedClasses/GraphicsEngine/GraphicsEngine.h"
#include "../../../Singleton/DerivedClasses/Mixer/Mixer.h"
#include "../../../Singleton/DerivedClasses/KeyManager/KeyManager.h"
#include "Character.h"

#include <utility>

Character::Character(const char *id, int x, int y, Direction direction)
        : Entity(x, y), id(id), currentDirection(direction) {}

Character::Character(const char *id, const char *name, int x, int y, Direction direction, int vision)
        : Entity(x, y), id(id), name(name), currentDirection(direction), vision(vision) {}

Character::~Character() {
    this->cv.notify_one();
    if (this->autonomy.joinable()) {
        this->autonomy.join();
    }
}

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
        default:
            std::clog << "Invalid direction " << this->currentDirection.load() << '\n';
            Game::getInstance().terminate();
    }
}

void Character::setDirection(Direction x) {
    this->currentDirection = x;
}

Direction Character::getDirection() const {
    return this->currentDirection;
}

// makes this face the entity
void Character::face(const Character *entity) {
    switch (entity->currentDirection) {
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
            std::clog << "Invalid direction " << entity->currentDirection.load() << '\n';
            Game::getInstance().terminate();
            return;
    }
}

bool Character::isFacing(Direction direction) const {
    return this->currentDirection == direction;
}

void Character::setState(Character::State x) {
    this->currentState = x;
}

Character::State Character::getState() const {
    return this->currentState;
}

bool Character::canMoveForward(const Map &map) const {
    switch (this->currentDirection) {
        case Direction::UP:
            return not map.isCollisionHere(this->getMapX(), this->getMapY() - 1) and map.isExitPointHere(this->getMapX(), this->getMapY() - 1) == std::nullopt;
        case Direction::RIGHT:
            return not map.isCollisionHere(this->getMapX() + 1, this->getMapY()) and map.isExitPointHere(this->getMapX() + 1, this->getMapY()) == std::nullopt;
        case Direction::DOWN:
            return not map.isCollisionHere(this->getMapX(), this->getMapY() + 1) and map.isExitPointHere(this->getMapX(), this->getMapY() + 1) == std::nullopt;
        case Direction::LEFT:
            return not map.isCollisionHere(this->getMapX() - 1, this->getMapY()) and map.isExitPointHere(this->getMapX() - 1, this->getMapY()) == std::nullopt;
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

void Character::decide() {
    switch (generateInteger(1, 4)) {
        case 1:
            if (this->decisions.empty()) {
                this->decisions.emplace([](Character *character) -> void {
                    character->face(character);
                });
                Overworld::pushEvent();
                std::cout << this->name << "Made decision 1\n";
            }
            break;

        case 2:
            if (this->decisions.empty()) {
                this->decisions.emplace([](Character *character) -> void {
                    if (character->isFacing(Direction::UP) or character->isFacing(Direction::DOWN)) {
                        binomial() ? character->setDirection(Direction::LEFT) : character->setDirection(
                                Direction::RIGHT);
                    }
                    else {
                        binomial() ? character->setDirection(Direction::UP) : character->setDirection(Direction::DOWN);
                    }
                });
                Overworld::pushEvent();
                std::cout << this->name << "Made decision 2\n";
            }
            break;

        default:
            if (this->decisions.empty()) {
                this->decisions.emplace([](Character *character) -> void {
                    if (character->canMoveForward(Scene::getInstance<Overworld>().getCurrentMap())) {
                        character->moveForward();
                        character->setState(Character::State::WALKING);

                        if (character->hasVisionOf(&Player::getPlayer()) and
                            (Player::getPlayer().getState() == Character::State::IDLE)) {
                            Player::getPlayer().setState(Character::State::IMMOBILE);
                        }
                    }
                    else {
                        character->setState(Character::State::COLLIDING);
                        character->updateAnimation();
                    }
                    ++entitiesUpdating;
                });
                Overworld::pushEvent();
                std::cout << this->name << "Made decision 3\n";
            }
            break;
    }
}

void Character::makeAutonomous(const std::string &mapId) {
    this->autonomy = std::thread([this, mapId] -> void {
        while (true) {
            if (Scene::getInstance<Overworld>().getCurrentMap().getMusic() != mapId or
                not Game::getInstance().isRunning()) {
                return;
            }

            this->decide();

            {
                std::unique_lock<std::mutex> lock(this->mutex);
                this->cv.wait(lock, [this] -> bool { return this->currentState == Character::State::IDLE; });
            }

            std::unique_lock<std::mutex> lock(this->mutex);
            this->cv.wait_for(lock, std::chrono::seconds(generateInteger(2, 4)), [] -> bool {
                return not Game::getInstance().isRunning();
            });
        }
    });
}

void Character::interact() {
    return;
    // if the player manually clicked Enter
    // (the trainer will have opened the TextBox if it has contacted the player already)
    if (not GraphicsEngine::getInstance().hasAny<TextBox>()) {
        KeyManager::getInstance().lock(SDL_Scancode::SDL_SCANCODE_RETURN);

        Player::getPlayer().setState(Character::State::IMMOBILE);
        this->currentState = Character::State::IMMOBILE;
        this->face(&Player::getPlayer());

        Overworld::createTextBox(this->getDialogue());
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
                }
                else {
                    Player::getPlayer().setState(Character::State::IDLE);
                    this->currentState = Character::State::IDLE;
                }
            }
        }
        // re-lock the Enter key
        KeyManager::getInstance().lock(SDL_Scancode::SDL_SCANCODE_RETURN);

        // sets a cool-down period before the Enter key can be registered again;
        // this is needed because the program will register a button as
        // being pressed faster than the user can lift their finger
        std::thread coolDown([] -> void {
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            KeyManager::getInstance().unlock(SDL_Scancode::SDL_SCANCODE_RETURN);
        });
        coolDown.detach();

        keyDelay.reset();
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

        default:
            std::clog << "Invalid argument in function Character::update()\n";
            Game::getInstance().terminate();
            break;
    }
}

void Character::render() const {
    TextureManager::getInstance().drawFrame(
            Scene::getInstance<Overworld>().getCurrentMap().getSpriteSheet(this->id, this->currentDirection).sprite,
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

Character::Character(std::string id, std::string name) : name(std::move(name)), id(std::move(id)) {}

void Character::walk() {
    this->pixelCounter += Character::WALK_SPEED;
    this->shift(this->currentDirection, Character::WALK_SPEED);

    if (this->pixelCounter % (Map::TILE_SIZE / 2) == 0) {
        this->updateAnimation();
    }
    if (this->pixelCounter % Map::TILE_SIZE == 0) {
        this->currentState = Character::State::IDLE;
        this->pixelCounter = 0;
        this->cv.notify_one();

        --entitiesUpdating;
        Overworld::pushEvent();
    }
}

void Character::collide() {
    if (this->pixelCounter == 10 * (Game::getInstance().getFps() / 30)) {
        this->updateAnimation();
    }
    else if (this->pixelCounter == 20 * (Game::getInstance().getFps() / 30)) {
        this->currentState = Character::State::IDLE;
        this->pixelCounter = 0;
        this->cv.notify_one();

        --entitiesUpdating;
        Overworld::pushEvent();
    }
    if (this->currentState != Character::State::IDLE) {
        ++this->pixelCounter;
    }
}

void Character::idle() {
    if (not this->decisions.empty()) {
        this->decisions.front()(this);
        this->decisions.pop();
    }
}

void Character::incPixelCounter(int n) {
    this->pixelCounter += n;
}

void Character::resetPixelCounter() {
    this->pixelCounter = 0;
}

int Character::getPixelCounter() const {
    return this->pixelCounter;
}
