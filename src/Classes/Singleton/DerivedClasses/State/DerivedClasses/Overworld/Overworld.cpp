//
// Created by Miles on 1/28/2024.
//

#include "../../../Game/Game.h"
#include "../../../GraphicsEngine/GraphicsEngine.h"
#include "../../../Mixer/Mixer.h"
#include "../../../KeyManager/KeyManager.h"
#include "../../../Camera/Camera.h"
#include "Overworld.h"

void Overworld::init() {
    this->currentMap = std::make_unique<Map>("Nuvema Town");

    Player::getPlayer().setName("Hilbert");

    Player::getPlayer().addPokemon("Emboar");
    Player::getPlayer()[0].addMove("Heat Crash");
    Player::getPlayer()[0].addMove("Head Smash");
}

void Overworld::handleEvents() {
    static SDL_Event event;
    if (SDL_PollEvent(&event) == 1) {
        switch (event.type) {
            case SDL_EventType::SDL_QUIT:
                Game::getInstance().terminate();
                break;
            case SDL_EventType::SDL_KEYDOWN:
                keyDelay.start();
                break;
            case SDL_EventType::SDL_KEYUP:
                keyDelay.stop();
                break;
            default:
                break;
        }
    }
}

void Overworld::update() {
    for (auto &entity : *this->currentMap) {
        entity->update();
    }
    Player::getPlayer().update();

    GraphicsEngine::getInstance().update();
}

void Overworld::render() {
    this->currentMap->render();
    GraphicsEngine::getInstance().render();
}

void Overworld::save() {
}

void Overworld::changeMap(const std::tuple<int, int, std::string> &data) {
    if (Mix_FadeOutMusic(2000) == 0) {
        std::clog << "Error fading out \"" << this->currentMap->getMusic() << "\": "
                  << SDL_GetError() << '\n';
        SDL_ClearError();
        Game::getInstance().terminate();
        return;
    }

    Mix_HookMusicFinished([] -> void {
        Mixer::getInstance().playMusic(State::getInstance<Overworld>().currentMap->getMusic());
    });

    // move the new map into the current map variable
    this->currentMap = std::make_unique<Map>(std::get<2>(data).c_str());

    Player::getPlayer().setCoordinates(std::get<0>(data), std::get<1>(data));

    Camera::getInstance().lockOnPlayer(*this->currentMap);
}

Map &Overworld::getCurrentMap() const {
    return *this->currentMap;
}

void Overworld::createTextBox(const std::string &message, const std::function<void()> &function) {
    const int box_width = Map::TILE_SIZE * 7;
    const int box_height = Map::TILE_SIZE * 2;
    const SDL_Rect rect(
            Game::WINDOW_WIDTH / 2 - box_width / 2,
            Game::WINDOW_HEIGHT - box_height,
            box_width,
            box_height - Map::TILE_SIZE / 2
    );

    GraphicsEngine::getInstance().addGraphic<TextBox>(
            rect,
            rect.h / (Map::TILE_SIZE * 3 / 10),
            rect.x + Map::TILE_SIZE / 10,
            rect.y + Map::TILE_SIZE / 10
    );

    GraphicsEngine::getInstance().getGraphic<TextBox>().push(message, function);
}

void Overworld::createTextBox(const std::vector<std::string> &dialogue) {
    const int box_width = Map::TILE_SIZE * 7;
    const int box_height = Map::TILE_SIZE * 2;
    const SDL_Rect rect(
            Game::WINDOW_WIDTH / 2 - box_width / 2,
            Game::WINDOW_HEIGHT - box_height,
            box_width,
            box_height - Map::TILE_SIZE / 2
    );

    GraphicsEngine::getInstance().addGraphic<TextBox>(
            rect,
            rect.h / (Map::TILE_SIZE * 3 / 10),
            rect.x + Map::TILE_SIZE / 10,
            rect.y + Map::TILE_SIZE / 10
    );

    const std::function<void()> callback = [] -> void {
        KeyManager::getInstance().unlockKey(SDL_Scancode::SDL_SCANCODE_RETURN);
    };
    GraphicsEngine::getInstance().getGraphic<TextBox>().push(
            dialogue,
            std::vector<std::function<void()>>({ callback, callback, callback })
    );
}

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

void Overworld::handleMove(SDL_Scancode scancode) {
    if (not GraphicsEngine::getInstance().hasAny<SelectionBox>()) {
        // turns the player
        if (not Player::getPlayer().isFacing(scancodeToDirection(scancode))) {
            Player::getPlayer().setDirection(scancodeToDirection(scancode));
        }
        // if the user is still holding down the key after 10ms, begin movement
        if (KeyManager::getInstance().getKey(scancode) and (momentum or keyDelay >= 10)) {
            momentum = true;
            keyDelay.stop();
            keyDelay.reset();

            if (Player::getPlayer().canMoveForward(*this->currentMap)) {
                Player::getPlayer().moveForward();
                Player::getPlayer().setState(Character::State::WALKING);
            }
            else {
                Player::getPlayer().setState(Character::State::COLLIDING);
                Player::getPlayer().updateAnimation();

                Mixer::getInstance().playSound("bump");
            }
        }
    }
}

void Overworld::handleReturn() {
    for (auto &entity : *this->currentMap) {
        if (Player::getPlayer().hasVisionOf(entity.get())) {
            entity->interact();
            return;
        }
    }
}
