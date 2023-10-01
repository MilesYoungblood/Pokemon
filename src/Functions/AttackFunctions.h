//
// Created by Miles Youngblood on 6/7/2022.
//

#pragma once

#include "TypeCalculations/TypeChart.h"
#include "GeneralFunctions.h"

void displayMoves(const Pokemon &pokemon, int arrow, bool &print) {
    if (print) {
        printMessage("Choose a move:\n");
    }
    else {
        std::cout << "Choose a move:\n";
    }
    for (int i = 0; i < pokemon.numMoves(); ++i) {
        if (arrow == i) {
            std::cout << "   ->   " << pokemon[i] << std::string(15 - pokemon[i].getName().length(), ' ')
                      << " (PP: " << pokemon[i].getPP() << std::string(2 - std::to_string(pokemon[i].getPP()).length(), ' ')
                      << '/' << std::string(2 - std::to_string(pokemon[i].getMaxPP()).length(), ' ') << pokemon[i].getMaxPP()
                      << ")\n";
        }
        else {
            std::cout << '\t' << pokemon[i] << std::string(15 - pokemon[i].getName().length(), ' ')
                      << " (PP: " << pokemon[i].getPP() << std::string(2 - std::to_string(pokemon[i].getPP()).length(), ' ')
                      << '/' << std::string(2 - std::to_string(pokemon[i].getMaxPP()).length(), ' ') << pokemon[i].getMaxPP()
                      << ")\n";
        }
    }
    arrow == pokemon.numMoves() ? std::cout << "\n   ->   Cancel\n" : std::cout << "\n\tCancel\n";
    std::cout.flush();

    print = false;
}

void displayMoves(const Pokemon &pokemon) {
    printMessage("Choose a move:\n");
    for (int i = 0; i < pokemon.numMoves(); ++i) {
        std::cout << '\t' << pokemon[i] << std::string(15 - pokemon[i].getName().length(), ' ')
                  << " (PP: " << pokemon[i].getPP()
                  << std::string(2 - std::to_string(pokemon[i].getPP()).length(), ' ')
                  << '/' << pokemon[i].getMaxPP()
                  << std::string(2 - std::to_string(pokemon[i].getMaxPP()).length(), ' ')
                  << ") -> " << i + 1 << '\n';
    }
    std::cout << "\nCancel (0)\n";
    std::cout.flush();
}

void displayMoveSummary(const Move &move) {
    std::cout << move << '\n';
    std::cout << "\tType:     " << move.getType() << '\n';
    std::cout << "\tCategory: " << move.getCategory() << '\n';
    std::cout << "\tPower:    " << move.getPower() << '\n';
    std::cout << "\tAccuracy: " << move.getAccuracy() << '\n';
    std::cout << "\tPP:       " << move.getPP() << '/' << move.getMaxPP() << '\n';
    std::cout << "\n\tCancel (ENTER)\n";
    std::cout.flush();
}

void attackErrorMessage() {
    printMessage("That move is out of PP. Please select another move.\n");
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
}

void takeDamage(Trainer &t, int damage) {
    t[0].setHP(t[0].getHP() - damage);
    if (t[0].isFainted()) {
        t[0].faint();
        t.incFaintCount();
    }
}

namespace status {
    void takeDamageMessage(const Pokemon& pokemon) {
        printMessage(pokemon.getName() + " took " + std::to_string(static_cast<int>(lround(pokemon.getMaxHp() * .0625))) + " damage from it's ");
        if (pokemon.getStatus() == "burn")
            printMessage( "burn!\n");

        else if (pokemon.getStatus() == "poison")
            printMessage("poisoning!\n");

        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}

struct battlePhase {
private:
    static int getPhysicalAttack(const Pokemon &attackingPokemon, const Pokemon &defendingPokemon, Move &move) {
        const int levelCalc = (2 * attackingPokemon.getLevel() / 5) + 2;
        return levelCalc * attackingPokemon.getBaseAttack() * move.getDamage() / defendingPokemon.getBaseDefense();
    }

    static int getSpecialAttack(const Pokemon &attackingPokemon, const Pokemon &defendingPokemon, Move &move) {
        const int levelCalc = (2 * attackingPokemon.getLevel() / 5) + 2;
        return levelCalc * attackingPokemon.getBaseSpAttack() * move.getDamage() / defendingPokemon.getBaseSpDefense();
    }

    static std::pair<double, bool> criticalHit() {
        if (generateInteger(1, 16) == 1) {
            return std::make_pair(2.0, true);
        }
        else {
            return std::make_pair(1.0, false);
        }
    }

    // returns 1.5 if move is a STAB move, and 1.0 otherwise
    static double stabCheck(const Pokemon &pokemon, const Move &move) {
        return pokemon.getType(true) == move.getType() or pokemon.getType(false) == move.getType() ? 1.5 : 1.0;
    }

    static int calculateDamage(const Pokemon &attackingPokemon, const Pokemon &defendingPokemon, Move &move, bool &crit) {
        int initialDamage = 0;
        if (move.getCategory() == "physical")
            initialDamage = getPhysicalAttack(attackingPokemon, defendingPokemon, move);

        else if (move.getCategory() == "special")
            initialDamage = getSpecialAttack(attackingPokemon, defendingPokemon, move);

        const int finalDamage = (initialDamage / 50) + 2;
        const std::pair<double, bool> c = criticalHit();
        crit = c.second;

        //FIXME recalculate damage
        return static_cast<int>(finalDamage * stabCheck(attackingPokemon, move) * getTypeEffective(move, defendingPokemon) * c.first);
    }

    static void SwitchOut(Trainer &trainer, bool isUser, bool &keepPlaying) {
        //TODO add HP bar
        int toSwitch;

        if (isUser) {
            forcedSwitchPrompt();

            if (getChar({ 'f', 'r' }) == 'r') {
                //FIXME consider trainer battle
                bool runSuccess = run();
                runMessage(runSuccess);
                if (runSuccess) {
                    keepPlaying = false;
                    return;
                }
            }

            while (true) {
                displayPokemon(trainer);
                toSwitch = getInt(2, trainer.partySize());

                //FIXME might be a bug
                if (trainer[toSwitch - 1].isFainted())
                    hpEmptyMessage(trainer[toSwitch - 1]);

                else
                    break;
            }
        }

        else {
            do {
                toSwitch = generateInteger(0, trainer.partySize() - 1);
            } while (trainer[toSwitch].isFainted());
        }

        switchOut(trainer, toSwitch);
        sendOutMessage(trainer[0]);
    }

    static void Action(Trainer &attacker, Trainer &defender, int move, bool &switched, bool isUserAttacking, bool &keepPlaying) {
        bool crit = false;
        const int damage = calculateDamage(attacker[0], defender[0], attacker[0][move], crit);

        attacker[0][move].action(attacker[0], defender[0], damage);
        attacker[0][move].actionMessage(attacker[0], defender[0], damage, crit, getTypeEffective(attacker[0][move], defender[0]));

        if (defender[0].isFainted()) {
            defender[0].faint();
            defender.incFaintCount();
            faintMessage(defender[0]);
            if (not defender.canFight()) {
                defender.defeat();
                //TODO add HP bar
                isUserAttacking ? winMessage() : loseMessage();
                keepPlaying = false;
            }
            else {
                isUserAttacking ? SwitchOut(defender, false, keepPlaying) : SwitchOut(defender, true, keepPlaying);
                switched = true;
            }
        }
    }

    static void PostStatus(Trainer &trainer, bool isUser, bool &keepPlaying) {
        takeDamage(trainer, static_cast<int>(lround(trainer[0].getMaxHp() * 0.0625)));
        status::takeDamageMessage(trainer[0]);

        if (not trainer.canFight()) {
            trainer.defeat();
            isUser ? loseMessage() : winMessage();
            keepPlaying = false;
        }
        if (trainer[0].isFainted())
            isUser ? SwitchOut(trainer, true, keepPlaying) : SwitchOut(trainer, false, keepPlaying);
    }

    // This function commences attacking of each Pokémon and takes into account who is faster.
    // If a Pokémon is inflicted by a pre-attack status condition (paralysis, sleep, frozen), it cannot attack.
    static void PreStatus(Trainer &user, Trainer &opponent, int userMove, int opponentMove, bool isUserFaster, bool &keepPlaying) {
        bool skip = false;
        if (isUserFaster) {
            not preStatus(user[0].getStatus()) ? Action(user, opponent, userMove, skip, true, keepPlaying) : inflictedMessage(user[0]);

            if (not skip and keepPlaying)
                not preStatus(opponent[0].getStatus()) ? Action(opponent, user, opponentMove, skip, false, keepPlaying) : inflictedMessage(opponent[0]);
        }
        else {
            not preStatus(opponent[0].getStatus()) ? Action(opponent, user, opponentMove, skip, false, keepPlaying) : inflictedMessage(opponent[0]);

            if (not skip and keepPlaying)
                not preStatus(user[0].getStatus()) ? Action(user, opponent, userMove, skip, true, keepPlaying) : inflictedMessage(user[0]);
        }
    }

    // If a Pokémon is inflicted with a post-move status condition (burn, poison), it will take damage based on max HP.
    static void PostStatus(Trainer &user, Trainer &opponent, bool isUserFaster, bool &keepPlaying) {
        if (isUserFaster) {
            // if Pokémon is inflicted with a post-move status condition...
            if (postStatus(user[0].getStatus()))
                PostStatus(user, true, keepPlaying);

            // if Pokémon is inflicted with a post-move status condition...
            if (postStatus(opponent[0].getStatus()))
                PostStatus(opponent, false, keepPlaying);
        }
        else {
            // if Pokémon is inflicted with a post-move status condition...
            if (postStatus(opponent[0].getStatus()))
                PostStatus(opponent, false, keepPlaying);

            // if Pokémon is inflicted with a post-move status condition...
            if (postStatus(user[0].getStatus()))
                PostStatus(user, true, keepPlaying);
        }
    }

public:
    static void fight(Trainer &user, Trainer &opponent, int userMove, size_t &turn, bool &keepPlaying) {
        displayHPBar(user[0], opponent[0], turn);
        int opponentMove = generateInteger(0, opponent[0].numMoves() - 1);
        // re-selects opponent move if it's out of PP
        while (not opponent[0][opponentMove].canUse())
            opponentMove = generateInteger(0, 3);

        bool skip = false;
        // if trainer chose to attack this turn...
        if (userMove != user[0].numMoves()) {
            // if trainer is faster than opponent...
            if (user[0].isFasterThan(opponent[0])) {
                PreStatus(user, opponent, userMove, opponentMove, true, keepPlaying);
                PostStatus(user, opponent, true, keepPlaying);
            }
            // if opponent is faster than trainer...
            else if (opponent[0].isFasterThan(user[0])) {
                PreStatus(user, opponent, userMove, opponentMove, false, keepPlaying);
                PostStatus(user, opponent, false, keepPlaying);
            }
            // if trainer and opponent rival in speed; choose randomly
            else {
                if (generateInteger(0, 1) == 0) {
                    PreStatus(user, opponent, userMove, opponentMove, true, keepPlaying);
                    PostStatus(user, opponent, true, keepPlaying);
                }
                else {
                    PreStatus(user, opponent, userMove, opponentMove, false, keepPlaying);
                    PostStatus(user, opponent, false, keepPlaying);
                }
            }
        }
        // trainer chose not to attack this turn
        else {
            not preStatus(opponent[0].getStatus()) ? Action(opponent, user, opponentMove, skip, false, keepPlaying) : inflictedMessage(opponent[0]);

            // if trainer is faster than opponent...
            if (user[0].isFasterThan(opponent[0]))
                PostStatus(user, opponent, true, keepPlaying);

            // if opponent is faster than trainer...
            else if (opponent[0].isFasterThan(user[0]))
                PostStatus(user, opponent, false, keepPlaying);

            // if trainer and opponent rival in speed; choose randomly
            else
                generateInteger(0, 1) == 1 ? PostStatus(user, opponent, true, keepPlaying) : PostStatus(user, opponent, false, keepPlaying);
        }
        ++turn;
    }
};