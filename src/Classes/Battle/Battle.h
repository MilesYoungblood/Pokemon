//
// Created by Miles on 10/1/2023.
//

#pragma once

#include "../../Classes/Entity/DerivedClasses/Trainer/DerivedClasses/Player/Player.h"
#include "../../Functions/ItemFunctions.h"

class Battle {
private:
    static Player *player;
    static Trainer *opponent;
    static size_t turn;

    static bool skipPlayerTurn;
    static bool skipOpponentTurn;

    static void sendOutMessage(const Pokemon &pokemon, bool isPlayer);
    static void returnMessage(const Pokemon &pokemon);

    static void introMessage();

    static void displayChoices(int arrow, bool &print);

    static void displayPokemon(int arrow, bool &index);

    static void displayHPBar(bool displayPokemon);

    static void faintMessage(const Pokemon &pokemon);

    static void forcedSwitchPrompt(int arrow, bool &print);

    static bool run();
    static void runMessage(bool runStatus);
    static void runErrorMessage();

    static void pokemonPrompt(int arrow, bool &print);

    static void switchOutMessage(const Trainer *trainer, int pokemonSwitched);

    static void inBattleMessage();

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

    static void switchOut(Trainer *trainer, const bool isUser, bool &keepPlaying);

    static void action(Trainer *attacker, Trainer *defender, const int move, bool &switched, const bool isUserAttacking, bool &keepPlaying);

    static void preStatus(int skipTurn, int opponentMove, bool isUserFaster, bool &keepPlaying);
    static void postStatus(bool isUserFaster, bool &keepPlaying);

    static int chooseMove(bool &skip);
    static void chooseItem(bool &skip, bool isTrainerBattle, bool &keepPlaying);
    static bool runAway(bool &skip, bool canRun);
    static void choosePokemon(bool &skip);

    static void fight(int userMove, bool &keepPlaying);
    static void engageBattle(bool isTrainer);

public:
    Battle(Player *trainer1, Trainer *trainer2);
};
