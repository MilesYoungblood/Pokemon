//
// Created by Miles on 10/1/2023.
//

#pragma once

#include "../../../Item/ItemList.h"
#include "../../../Entity/DerivedClasses/Trainer/DerivedClasses/Player/Player.h"
#include "../../../../Functions/ItemFunctions.h"

class Battle : public Singleton<Battle> {
private:
    Player *player{ nullptr };
    Trainer *opponent{ nullptr };
    size_t turn{ 0 };

    bool skipPlayerTurn{ false };
    bool skipOpponentTurn{ false };

    bool isRunning{ true };

    friend class Singleton<Battle>;

    Battle() = default;

    static void sendOutMessage(const Pokemon &pokemon, bool isPlayer);

    static void returnMessage(const Pokemon &pokemon);

    void introMessage();

    void displayChoices(int arrow, bool &print);

    void displayPokemon(int arrow, bool &index);

    void displayHpBar(bool displayPokemon);

    static void faintMessage(const Pokemon &pokemon);

    static void forcedSwitchPrompt(int arrow, bool &print);

    bool run();

    static void runMessage(bool runStatus);

    static void runErrorMessage();

    static void pokemonPrompt(int arrow, bool &print);

    static void switchOutMessage(const Trainer *trainer, int pokemonSwitched);

    void inBattleMessage();

    static void winMessage();

    static void loseMessage();

    static void inflictedMessage(const Pokemon &pokemon);

    static void displayMoves(const Pokemon &pokemon, int index, bool &print);

    static void displayMoveSummary(const Move &move);

    static void attackErrorMessage();

    void switchOut(Trainer *trainer, bool isUser);

    void action(Trainer *attacker, Trainer *defender, int move, bool &switched, bool isUserAttacking);

    void preStatus(int skipTurn, int opponentMove, bool isUserFaster);

    void postStatus(bool isUserFaster);

    int chooseMove(bool &skip);

    void chooseItem(bool &skip, bool isTrainerBattle);

    bool runAway(bool &skip, bool canRun);

    void choosePokemon(bool &skip);

    void fight(int userMove);

public:
    enum class Flag : Uint8 {
    };

    void init(Player *trainer1, Trainer *trainer2);

    void engageBattle(bool isTrainer);
};
