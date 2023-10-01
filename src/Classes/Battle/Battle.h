//
// Created by Miles on 10/1/2023.
//

#pragma once

#include "../../Classes/Trainer/Trainer.h"
#include "../../Data/Data.h"
#include "../../main.h"
#include "../../Functions/ItemFunctions.h"
#include "../../Functions/TypeCalculations/TypeChart.h"

class Battle {
private:
    static Trainer * user;
    static Trainer * opponent;
    static size_t turn;

    static void wildPokemonMessage(const Pokemon &pokemon);

    static void sendOutMessage(const Pokemon &pokemon);
    static void returnMessage(const Pokemon &pokemon);

    static void introMessage();

    static void displayChoices(int arrow, bool &print);

    static void displayPokemon(int arrow, bool &print);
    static void displayPokemon(const Trainer &t);

    static void displayHPBar(bool displayPokemon);

    static void faintMessage(const Pokemon &pokemon);

    static void forcedSwitchPrompt();

    __attribute__((unused)) static bool run(const Pokemon &trainer_1, const Pokemon &trainer_2);
    static bool run();
    static void runMessage(bool runStatus);
    static void runErrorMessage();

    static void pokemonPrompt(int arrow, bool &print);

    static void switchOut(Trainer &t, int pokemonToSwitch);
    static void switchOutMessage(const Trainer &t, int pokemonSwitched);

    static void inBattleMessage();

    static void hpEmptyMessage(const Pokemon &pokemon);
    static void hpFullMessage(const Pokemon &pokemon);

    static void winMessage();
    static void loseMessage();

    static void displayItems(int t, int arrow, bool &print) {
        if (print) {
            printMessage("Choose an item:\n");
        }
        else {
            std::cout << "Choose an item:\n";
        }
        for (int i = 0; i < Battle::user->getNumItems(t); ++i)
            if (arrow == i) {
                std::cout << "   ->   " << Battle::user->getItem(t, i).getName() << std::string(15 - Battle::user->getItem(t, i).getName().length(), ' ') << " x"
                          << Battle::user->getItem(t, i).getQuantity() << '\n';
            }
            else {
                std::cout << '\t' << Battle::user->getItem(t, i).getName() << std::string(15 - Battle::user->getItem(t, i).getName().length(), ' ') << " x"
                          << Battle::user->getItem(t, i).getQuantity() << '\n';
            }

        arrow == Battle::user->getNumItems(t) ? std::cout << "\n   ->   Cancel\n" : std::cout << "\n\tCancel\n";
        std::cout.flush();

        print = false;
    }

    static bool preStatus(const std::string& status);
    static bool postStatus(const std::string& status);

    static void inflictedMessage(const Pokemon& pokemon);

    static void displayMoves(const Pokemon &pokemon, int arrow, bool &print);
    static void displayMoveSummary(const Move &move);

    static void attackErrorMessage();

    static void takeDamage(Trainer &t, int damage);
    static void takeDamageMessage(const Pokemon& pokemon);

    static int getPhysicalAttack(const Pokemon &attackingPokemon, const Pokemon &defendingPokemon, Move &move);
    static int getSpecialAttack(const Pokemon &attackingPokemon, const Pokemon &defendingPokemon, Move &move);

    static std::pair<double, bool> criticalHit();

    static double stabCheck(const Pokemon &pokemon, const Move &move);

    static int calculateDamage(const Pokemon &attackingPokemon, const Pokemon &defendingPokemon, Move &move, bool &crit);

    static void SwitchOut(Trainer &trainer, bool isUser, bool &keepPlaying);

    static void Action(Trainer &attacker, Trainer &defender, int move, bool &switched, bool isUserAttacking, bool &keepPlaying);

    static void PostStatus(Trainer &trainer, bool isUser, bool &keepPlaying);
    static void PreStatus(int userMove, int opponentMove, bool isUserFaster, bool &keepPlaying);
    static void PostStatus(bool isUserFaster, bool &keepPlaying);

    static int chooseMove(bool &skip);
    static void chooseItem(bool &skip, bool isTrainerBattle, bool &keepPlaying);
    static bool runAway(bool &skip, bool canRun);
    static void choosePokemon(bool &skip);

    static void fight(int userMove, bool &keepPlaying);

public:
    Battle(Trainer * trainer_1, Trainer * trainer_2);

    static void engageBattle(bool isTrainer);
};
