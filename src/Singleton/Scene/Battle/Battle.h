//
// Created by Miles on 1/28/2024.
//

#pragma once

#include "../../../Entity/Character/Trainer/Player/Player.h"
#include "../../../Graphic/Rectangle/ResourceBar/ResourceBar.h"
#include "../Scene.h"

/*
double getStat(Stat stat) const {
    switch (this->statModifiers.at(static_cast<std::size_t>(stat))) {
        case -6:
            return 0.25;
        case -5:
            return 2.0 / 7.0;
        case -4:
            return 2.0 / 6.0;
        case -3:
            return 0.4;
        case -2:
            return 0.5;
        case -1:
            return 2.0 / 3.0;
        case 0:
            return 1.0;
        case 1:
            return 1.5;
        case 2:
            return 2.0;
        case 3:
            return 2.5;
        case 4:
            return 3.0;
        case 5:
            return 3.5;
        case 6:
            return 4.0;
        default:
            throw std::runtime_error("Unexpected error: function getStatMod");
    }
}
*/

class Battle final : public Scene {
public:
    void init() override;

    void init(Character *);

    void fadeIn() override;

    void update() override;

    void fadeOut() override;

    void launch();

    void render() const override;

    void openSelectionBox(const std::function<void()> &callback);

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

    std::size_t turn{ 0 };

    struct Data {
        ResourceBar *hpBar{ nullptr };

        int move{ 0 };
        int skipCounter{ 0 };

        bool skip { false };
        bool renderSprite { false };

        std::unordered_map<std::string, int> statModifiers;
        std::unordered_map<std::string, SDL_Texture *> sprites;
    };

    std::array<std::pair<Character *, std::unique_ptr<Data>>, 2> participants;

    bool isRunning{ true };

    friend class Scene;

    Battle() = default;

    Data &getParticipant(const Character *character);

    void initMain();

    void initFight();

    void initPokemon();

    static void initEngage();

    void engage(Character *attacker, Character *defender);

    void preStatus(Character *first, Character *second);

    void postStatus(Character *first, Character *second);

    void handleTurn(int move);

    void updateEngage();

    void handleRun();

    void terminate();

    void changeState(State x, bool clear);
};
