//
// Created by Miles on 1/28/2024.
//

#include "../../Game/Game.h"
#include "../../GraphicsEngine/GraphicsEngine.h"
#include "../../TextureManager/TextureManager.h"
#include "../../Mixer/Mixer.h"
#include "../../EventHandler/EventHandler.h"
#include "../../KeyManager/KeyManager.h"
#include "../../Camera/Camera.h"
#include "../../Cache/Pokedex/Pokedex.h"
#include "Overworld.h"

namespace {
    std::unordered_map<Character *, Character::State> characterStates;
}

void Overworld::init() {
    static bool wasInit = false;
    if (not wasInit) {
        Pokedex::load();
        this->currentMap = std::make_unique<Map>("Nuvema Town", "NuvemaTown");

        Camera::getInstance().lockOnPlayer(*this->currentMap);

        wasInit = true;
        Pokedex::clear();
    }
}

void Overworld::fadeIn() {
    Game::getInstance().setRenderColor(Constants::Color::BLACK);

    TextureManager::getInstance().setScreenOpacity(SDL_ALPHA_TRANSPARENT);
    Mixer::getInstance().playMusic(this->currentMap->getId());
    this->setState(State::FADED_IN);
}

void Overworld::handleEvents() {
    std::unique_lock lock(this->mutex);
    this->cv.wait(lock, [this] -> bool { return entitiesUpdating > 0 or EventHandler::getInstance().waitEvent(); });

    if (entitiesUpdating > 0 and not EventHandler::getInstance().pollEvent()) {
        return;
    }
    switch (EventHandler::getInstance().getEventType()) {
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
        entity->update(*this->currentMap);
    }
    Player::getPlayer().update(*this->currentMap);

    GraphicsEngine::getInstance().update();
}

void Overworld::fadeOut() {
    static bool colorChanged = false;
    if (not colorChanged) {
        TextureManager::getInstance().setScreenColor(255, 255, 255);
        colorChanged = true;
        ++entitiesUpdating;
    }

    if (not TextureManager::getInstance().isScreenOpaque()) {
        TextureManager::getInstance().darken();
    }
    else {
        this->setState(State::FADED_OUT);
        colorChanged = false;
        --entitiesUpdating;
    }
}

void Overworld::render() const {
    this->currentMap->render();
    GraphicsEngine::getInstance().render();
}

void Overworld::clean() {
    this->currentMap.reset(nullptr);
}

void Overworld::changeMap(const std::pair<Component::Position, std::string> &data) {
    if (Mix_FadeOutMusic(2000) == 0) {
        std::clog << "Error fading out \"" << this->currentMap->getId() << "\": " << SDL_GetError() << '\n';
        SDL_ClearError();
        Game::getInstance().terminate();
        return;
    }

    Mix_HookMusicFinished([] -> void {
        Mixer::getInstance().playMusic(getInstance<Overworld>().currentMap->getId());
    });

    characterStates.clear();

    // move the new map into the current map variable
    this->currentMap = std::make_unique<Map>(data.second.c_str(), "");

    Player::getPlayer().getMapPosition() = data.first;
    Player::getPlayer().getScreenPosition().setPosition(data.first.getX() * Map::TILE_SIZE, data.first.getY() * Map::TILE_SIZE);

    Camera::getInstance().lockOnPlayer(*this->currentMap);
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
        pairs.emplace_back(message, [] -> void { KeyManager::getInstance().unlock(SDL_SCANCODE_RETURN); });
    }
    GraphicsEngine::getInstance().getGraphic<TextBox>().push(pairs);
}

void Overworld::handleEscape() const {
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
