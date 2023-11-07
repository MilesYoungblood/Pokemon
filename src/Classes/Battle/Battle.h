//
// Created by Miles on 10/1/2023.
//

#pragma once

#include "../../Classes/Entity/DerivedClasses/Trainer/DerivedClasses/Player/Player.h"
#include "../../Functions/ItemFunctions.h"

class Battle {
private:
    Player *player;
    Trainer *opponent;
    size_t turn;

    bool skipPlayerTurn;
    bool skipOpponentTurn;

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

    static std::pair<double, bool> criticalHit();

    static double stabCheck(const Pokemon &pokemon, const Move &move);

    static double checkType(const Move &move, const Pokemon &pokemon);

    static int calculateDamage(const Pokemon &attackingPokemon, const Pokemon &defendingPokemon, const Move &move, bool &crit);

    void switchOut(Trainer *trainer, bool isUser, bool &keepPlaying);

    void action(Trainer *attacker, Trainer *defender, int move, bool &switched, bool isUserAttacking, bool &keepPlaying);

    void preStatus(int skipTurn, int opponentMove, bool isUserFaster, bool &keepPlaying);

    void postStatus(bool isUserFaster, bool &keepPlaying);

    int chooseMove(bool &skip);

    void chooseItem(bool &skip, bool isTrainerBattle, bool &keepPlaying);

    bool runAway(bool &skip, bool canRun);

    void choosePokemon(bool &skip);

    void fight(int userMove, bool &keepPlaying);

    Battle(Player *trainer1, Trainer *trainer2);

public:
    static Battle &getInstance(Player *trainer1, Trainer *trainer2);

    void engageBattle(bool isTrainer);
};
