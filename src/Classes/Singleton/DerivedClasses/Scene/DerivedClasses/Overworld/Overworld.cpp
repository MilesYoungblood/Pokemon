//
// Created by Miles on 1/28/2024.
//

#include "../../../Game/Game.h"
#include "../../../GraphicsEngine/GraphicsEngine.h"
#include "../../../Mixer/Mixer.h"
#include "../../../KeyManager/KeyManager.h"
#include "../../../Camera/Camera.h"
#include "Overworld.h"

namespace {
    std::unordered_map<Character *, Character::State> characterStates;
}

void Overworld::init() {
    this->currentMap = std::make_unique<Map>("Nuvema Town");

    Player::getPlayer().setName("Hilbert");

    Player::getPlayer().addPokemon("Emboar");
    Player::getPlayer()[0].addMove("Heat Crash");
    Player::getPlayer()[0].addMove("Head Smash");
}

void Overworld::handleEvents() {
    std::unique_lock lock(this->mutex);
    this->cv.wait(lock, [this] -> bool { return entitiesUpdating > 0 or this->waitEvent(); });
    std::cout << "\tWaiting on " << entitiesUpdating << " entities\n";

    switch (this->getEventType()) {
        case SDL_QUIT:
            Game::getInstance().terminate();
            break;
        case SDL_KEYDOWN:
            keyDelay.start();
            break;
        case SDL_KEYUP:
            keyDelay.stop();
            break;
        default:
            break;
    }
}

void Overworld::update() {
    for (const auto &entity : *this->currentMap) {
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

void Overworld::changeMap(const std::pair<Project::Position, std::string> &data) {
    if (Mix_FadeOutMusic(2000) == 0) {
        std::clog << "Error fading out \"" << this->currentMap->getMusic() << "\": " << SDL_GetError() << '\n';
        SDL_ClearError();
        Game::getInstance().terminate();
        return;
    }

    Mix_HookMusicFinished([] -> void {
        Mixer::getInstance().playMusic(getInstance<Overworld>().currentMap->getMusic());
    });

    characterStates.clear();

    // move the new map into the current map variable
    this->currentMap = std::make_unique<Map>(data.second.c_str());

    Player::getPlayer().getMapPosition() = data.first;
    Player::getPlayer().getScreenPosition().setPosition(data.first.getX() * Map::TILE_SIZE, data.first.getY() * Map::TILE_SIZE);

    Camera::getInstance().lockOnPlayer(*this->currentMap);
}

Map &Overworld::getCurrentMap() const {
    return *this->currentMap;
}

void Overworld::createTextBox(const std::string &message, const std::function<void()> &function) {
    constexpr int boxWidth = Map::TILE_SIZE * 7;
    constexpr int boxHeight = Map::TILE_SIZE * 2;
    constexpr SDL_Rect rect(
            Game::WINDOW_WIDTH / 2 - boxWidth / 2,
            Game::WINDOW_HEIGHT - boxHeight,
            boxWidth,
            boxHeight - Map::TILE_SIZE / 2
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
    constexpr int boxWidth = Map::TILE_SIZE * 7;
    constexpr int boxHeight = Map::TILE_SIZE * 2;
    constexpr SDL_Rect rect(
            Game::WINDOW_WIDTH / 2 - boxWidth / 2,
            Game::WINDOW_HEIGHT - boxHeight,
            boxWidth,
            boxHeight - Map::TILE_SIZE / 2
    );

    GraphicsEngine::getInstance().addGraphic<TextBox>(
            rect,
            rect.h / (Map::TILE_SIZE * 3 / 10),
            rect.x + Map::TILE_SIZE / 10,
            rect.y + Map::TILE_SIZE / 10
    );

    std::vector<std::pair<std::string, std::function<void()>>> pairs;
    pairs.reserve(dialogue.size());
    for (const auto &message : dialogue) {
        pairs.emplace_back(
                message,
                [] -> void { KeyManager::getInstance().unlock(SDL_SCANCODE_RETURN); }
        );
    }
    GraphicsEngine::getInstance().getGraphic<TextBox>().push(pairs);
}

void Overworld::handleEscape() {
    if (GraphicsEngine::getInstance().hasAny<SelectionBox>()) {
        GraphicsEngine::getInstance().removeGraphic<SelectionBox>();
        Player::getPlayer().setState(Character::State::IDLE);
        for (auto &entity : *this->currentMap) {
            if (auto *character = dynamic_cast<Character *>(entity.get()); character != nullptr) {
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
        Player::getPlayer().setState(Character::State::IMMOBILE);
        for (auto &entity : *this->currentMap) {
            if (auto *character = dynamic_cast<Character *>(entity.get()); character != nullptr) {
                characterStates[character] = character->getState();
                character->setState(Character::State::IMMOBILE);
            }
        }
    }
    // re-lock the Enter key
    KeyManager::getInstance().lock(SDL_SCANCODE_ESCAPE);

    // sets a cool-down period before the Enter key can be registered again;
    // this is needed because the program will register a button as
    // being pressed faster than the user can lift their finger
    std::thread coolDown([] -> void {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        KeyManager::getInstance().unlock(SDL_SCANCODE_ESCAPE);
    });
    coolDown.detach();
}
