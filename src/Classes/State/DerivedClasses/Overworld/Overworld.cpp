//
// Created by Miles on 1/28/2024.
//

#include "../../../Singleton/DerivedClasses/Game/Game.h"
#include "Overworld.h"

void createTextBox(const std::vector<std::string> &messages) {
    GraphicsEngine::getInstance().addGraphic<TextBox>(TextBox::getInstance());
    GraphicsEngine::getInstance().getGraphic<TextBox>().setFinishedCallback([] -> void {
        KeyManager::getInstance().unlockKey(SDL_Scancode::SDL_SCANCODE_RETURN);
    });

    const int box_width = Constants::TILE_SIZE * 7;
    const int box_height = Constants::TILE_SIZE * 2;
    const SDL_Rect rect(
            Game::getInstance().getWindowWidth() / 2 - box_width / 2,
            Game::getInstance().getWindowHeight() - box_height,
            box_width,
            box_height - Constants::TILE_SIZE / 2
    );
    GraphicsEngine::getInstance().getGraphic<TextBox>().init(
            rect,
            rect.h / (Constants::TILE_SIZE * 3 / 10),
            rect.x + Constants::TILE_SIZE / 10,
            rect.y + Constants::TILE_SIZE / 10
    );
    GraphicsEngine::getInstance().getGraphic<TextBox>().push(messages);
}

void changeMap(const std::tuple<int, int, Map::Id> &data) {
    if (Mix_FadeOutMusic(2000) == 0) {
        std::clog << "Error fading out \"" << Game::getInstance().getCurrentMap()->getMusic() << "\": "
                  << SDL_GetError() << '\n';
        SDL_ClearError();
        Game::getInstance().terminate();
        return;
    }

    Mix_HookMusicFinished([] -> void {
        Mixer::getInstance().playMusic(Game::getInstance().getCurrentMap()->getMusic());
    });

    Game::getInstance().getCurrentMap()->reset();

    // move the new map into the current map variable
    Game::getInstance().changeMap(std::get<2>(data));

    // resets the states of these variables for each trainer
    for (auto &trainer : *Game::getInstance().getCurrentMap()) {
        keepLooping[&trainer] = true;
    }

    Player::getPlayer().setCoordinates(std::get<0>(data), std::get<1>(data));

    Camera::getInstance().lockOnPlayer(Game::getInstance().getCurrentMap());
}

void handleMove(SDL_Scancode scancode) {
    static const std::unordered_map<SDL_Scancode, Direction> direction_to_key{
            std::make_pair(SDL_Scancode::SDL_SCANCODE_W, Direction::UP),
            std::make_pair(SDL_Scancode::SDL_SCANCODE_A, Direction::LEFT),
            std::make_pair(SDL_Scancode::SDL_SCANCODE_S, Direction::DOWN),
            std::make_pair(SDL_Scancode::SDL_SCANCODE_D, Direction::RIGHT)
    };

    if (not GraphicsEngine::getInstance().hasAny<Rectangle>()) {
        if (not Player::getPlayer().isFacing(direction_to_key.at(scancode))) {
            Player::getPlayer().setDirection(direction_to_key.at(scancode));
        }
        if (KeyManager::getInstance().getKey(scancode) and (momentum or keyDelay >= 10)) {
            momentum = true;
            keyDelay.stop();
            keyDelay.reset();

            if (Player::getPlayer().canMoveForward(Game::getInstance().getCurrentMap())) {
                Player::getPlayer().moveForward();
                Player::getPlayer().setState(Entity::State::WALKING);
            }
            else {
                Player::getPlayer().setState(Entity::State::COLLIDING);
                Player::getPlayer().updateAnimation();

                Mixer::getInstance().playSound("bump");
            }
        }
    }
}

void handleReturn() {
    for (auto &trainer : *Game::getInstance().getCurrentMap()) {
        if (Player::getPlayer().hasVisionOf(&trainer)) {
            // if the player manually clicked Enter
            if (not GraphicsEngine::getInstance().hasAny<TextBox>()) {
                Player::getPlayer().setState(Entity::State::FROZEN);
                trainer.face(&Player::getPlayer());

                // only create the textbox here if the trainer cannot fight;
                // the program will loop back to checkForOpponents() in the next cycle
                // and create it there if the trainer can fight
                if (not trainer.canFight()) {
                    trainer.setState(Entity::State::FROZEN);
                    createTextBox(trainer.getDialogue());
                }
            }
            else {
                // if the textbox still has messages to print
                if (not GraphicsEngine::getInstance().getGraphic<TextBox>().empty()) {
                    GraphicsEngine::getInstance().getGraphic<TextBox>().pop();

                    if (not GraphicsEngine::getInstance().getGraphic<TextBox>().empty()) {
                        Mixer::getInstance().playSound("accept");
                    }
                }
                // if the textbox is done printing
                if (GraphicsEngine::getInstance().getGraphic<TextBox>().empty()) {
                    GraphicsEngine::getInstance().removeGraphic<TextBox>();

                    if (trainer.canFight()) {
                        Mixer::getInstance().playMusic("TrainerBattle");

                        trainer.clearParty();
                        Game::getInstance().setState(State::Id::BATTLE);
                        Game::getInstance().setRenderColor(Constants::Color::WHITE);

                        GraphicsEngine::getInstance().addGraphic<ResourceBar>(
                                SDL_Rect(Game::getInstance().getWindowWidth() - 200 - 50, 50, 200, 10),
                                Constants::Color::GREEN,
                                Constants::Color::BLACK,
                                5,
                                100
                        );
                    }
                    else {
                        Player::getPlayer().setState(Entity::State::IDLE);
                        trainer.setState(Entity::State::IDLE);
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
                return;
            }
        }
    }
}

void Overworld::update() {
    Player::getPlayer().update();

    for (auto &trainer : *Game::getInstance().getCurrentMap()) {
        trainer.update();
    }

    GraphicsEngine::getInstance().update();
}

void Overworld::render() {
    Game::getInstance().getCurrentMap()->render();
    GraphicsEngine::getInstance().render();
}

void Overworld::changeMap(std::size_t index) {

}

void Overworld::changeMap(const std::tuple<int, int, Map::Id> &data) {

}

Map *Overworld::getCurrentMap() const {

}

void Overworld::createTextBox(const std::vector<std::string> &messages) {

}

void Overworld::handleMove(SDL_Scancode scancode) {

}

void Overworld::handleReturn() {

}
