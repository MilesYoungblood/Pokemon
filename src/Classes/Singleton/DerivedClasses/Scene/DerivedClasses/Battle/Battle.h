//
// Created by Miles on 1/28/2024.
//

#pragma once

#include "../../../TextureManager/TextureManager.h"
#include "../../../../../Entity/DerivedClasses/Character/DerivedClasses/Trainer/DerivedClasses/Player/Player.h"
#include "../../Scene.h"
#include "../../../../../Graphic/DerivedClasses/Rectangle/DerivedClasses/ResourceBar/ResourceBar.h"

class Battle : public Scene {
private:
    enum class State : Uint8 {
        MAIN,
        SELECT_MOVE,
        SELECT_POKEMON,
        ENGAGE
    };
    std::stack<Battle::State> states{{ Battle::State::MAIN }};

    const std::array<std::function<void()>, 4> INIT_FUNCTIONS{
            [this] -> void { this->initMain(); },
            [this] -> void { this->initFight(); },
            [this] -> void { this->initPokemon(); },
            Battle::initEngage
    };

    const std::array<std::function<void()>, 4> UPDATE_FUNCTIONS{
            nullptr,
            nullptr,
            nullptr,
            [this] -> void { this->updateEngage(); }
    };

    std::unordered_map<std::string, SDL_Texture *> playerSprites;
    std::unordered_map<std::string, SDL_Texture *> opponentSprites;

    std::size_t turn{ 0 };

    Trainer *opponent{ nullptr };

    ResourceBar *playerBar{ nullptr };
    ResourceBar *opponentBar{ nullptr };

    int playerMove{ 0 };
    int opponentMove{ 0 };

    bool skipPlayer{ false };
    bool skipOpponent{ false };

    bool renderPlayer{ false };
    bool renderOpponent{ false };

    bool isRunning{ true };

    friend class Scene;

    Battle() = default;

    void initMain();

    void initFight();

    void initPokemon();

    static void initEngage();

    void engage(Trainer *attacker, Trainer *defender, int move, bool *skip);

    void preStatus(bool isPlayerFaster);

    void postStatus(bool isPlayerFaster);

    void handleTurn(int move);

    void updateEngage();

    void handleRun();

    void terminate();

    void changeState(Battle::State state, bool clear);

public:
    void init(Trainer *trainer);

    void update() override;

    void render() override;
};
