//
// Created by Miles on 10/1/2023.
//

#pragma once

#include "../../Classes/Player/Player.h"
#include "../../Functions/ItemFunctions.h"
#include "../../Functions/TypeCalculations/TypeChart.h"

class Battle {
private:
    static Player *player;
    static Trainer *opponent;
    static size_t turn;

    //static void wildPokemonMessage(const Pokemon &pokemon);

    static void sendOutMessage(const Pokemon &pokemon);
    static void returnMessage(const Pokemon &pokemon);

    static void introMessage();

    static void displayChoices(int arrow, bool &print);

    static void displayPokemon(int arrow, bool &print);

    static void displayHPBar(bool displayPokemon);

    static void faintMessage(const Pokemon &pokemon);

    static void forcedSwitchPrompt(int arrow, bool &print);

    static bool run();
    static void runMessage(bool runStatus);
    static void runErrorMessage();

    static void pokemonPrompt(int arrow, bool &print);

    static void switchOutMessage(const Trainer *t, int pokemonSwitched);

    static void inBattleMessage();

    static void winMessage();
    static void loseMessage();

    static void inflictedMessage(const Pokemon &pokemon);

    static void displayMoves(const Pokemon &pokemon, int arrow, bool &print);
    static void displayMoveSummary(const Move &move);

    static void attackErrorMessage();

    static void takeDamage(Trainer *t, int damage);

    static int getPhysicalAttack(const Pokemon &attackingPokemon, const Pokemon &defendingPokemon, Move &move);
    static int getSpecialAttack(const Pokemon &attackingPokemon, const Pokemon &defendingPokemon, Move &move);

    static std::pair<double, bool> criticalHit();

    static double stabCheck(const Pokemon &pokemon, const Move &move);

    static int calculateDamage(const Pokemon &attackingPokemon, const Pokemon &defendingPokemon, Move &move, bool &crit);

    static void SwitchOut(Trainer *trainer, bool isUser, bool &keepPlaying);

    static void Action(Trainer *attacker, Trainer *defender, int move, bool &switched, bool isUserAttacking, bool &keepPlaying);

    static void PreStatus(int userMove, int opponentMove, bool isUserFaster, bool &keepPlaying);
    static void PostStatus(bool isUserFaster, bool &keepPlaying);

    static int chooseMove(bool &skip);
    static void chooseItem(bool &skip, bool isTrainerBattle, bool &keepPlaying);
    static bool runAway(bool &skip, bool canRun);
    static void choosePokemon(bool &skip);

    static void fight(int userMove, bool &keepPlaying);
    static void engageBattle(bool isTrainer);

public:
    Battle(Player *trainer_1, Trainer *trainer_2);
};
