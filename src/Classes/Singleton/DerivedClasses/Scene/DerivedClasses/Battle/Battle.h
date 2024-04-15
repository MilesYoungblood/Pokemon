//
// Created by Miles on 1/28/2024.
//

#pragma once

#include "../../../../../Entity/DerivedClasses/Character/DerivedClasses/Trainer/DerivedClasses/Player/Player.h"
#include "../../../../../Graphic/DerivedClasses/Rectangle/DerivedClasses/ResourceBar/ResourceBar.h"
#include "../../Scene.h"

class Battle final : public Scene {
public:
    void init(Trainer *t);

    void update() override;

    void render() override;

private:
    enum class State : Uint8 {
        MAIN,
        SELECT_MOVE,
        SELECT_POKEMON,
        ENGAGE
    };
    std::stack<State> states;

    const std::array<std::function<void()>, 4> initFunctions{
        [this] -> void { this->initMain(); },
        [this] -> void { this->initFight(); },
        [this] -> void { this->initPokemon(); },
        initEngage
};

    const std::array<std::function<void()>, 4> updateFunctions{
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

    void changeState(State state, bool clear);
};
