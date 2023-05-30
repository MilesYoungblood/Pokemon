//
// Created by Miles Youngblood on 6/7/2022.
//

#pragma once

#include "TypeCalculations/TypeChart.h"
#include "GeneralFunctions.h"

void displayMoves(const Pokemon &pokemon) {
    printMessage("Choose a move:\n");
    for (int i = 0; i < pokemon.numMoves(); ++i) {
        std::cout << '\t' << pokemon[i] << std::string(15 - pokemon[i].getName().length(), ' ')
                  << " (PP: " << pokemon[i].getPP() << std::string(2 - std::to_string(pokemon[i].getPP()).length(), ' ')
                  << '/' << pokemon[i].getMaxPP() << std::string(2 - std::to_string(pokemon[i].getMaxPP()).length(), ' ')
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
    std::cout << "\nCancel (0)\n";
    std::cout.flush();
}

int getPhysicalAttack(const Pokemon &attackingPokemon, const Pokemon &defendingPokemon, const Move &move) {
    int levelCalc = (2 * attackingPokemon.getLevel() / 5) + 2;
    return levelCalc * attackingPokemon.getBaseAttack() * move.getDamage() / defendingPokemon.getBaseDefense();
}

int getSpecialAttack(const Pokemon &attackingPokemon, const Pokemon &defendingPokemon, const Move &move) {
    int levelCalc = (2 * attackingPokemon.getLevel() / 5) + 2;
    return levelCalc * attackingPokemon.getBaseSpAttack() * move.getDamage() / defendingPokemon.getBaseSpDefense();
}

float criticalHit(bool &crit) {
    // returns 2 in order to double the damage
    if (generateInteger(1, 16) == 1) {
        crit = true;
        return 2.0f;
    }
    // returns 1 if no crit
    else {
        crit = false;
        return 1.0f;
    }
}

// returns 1.5 if move is a STAB move, and 1.0 otherwise
float stabCheck(const Pokemon &pokemon, const Move &move) {
    return pokemon.getType(true) == move.getType() or pokemon.getType(false) == move.getType() ? 1.5f : 1.0f;
}

int calculateDamage(const Pokemon &attackingPokemon, const Pokemon &defendingPokemon, const Move &move, bool &crit) {
    int initialDamage{};
    if (move.getCategory() == "physical") {
        initialDamage = getPhysicalAttack(attackingPokemon, defendingPokemon, move);
    }
    else if (move.getCategory() == "special") {
        initialDamage = getSpecialAttack(attackingPokemon, defendingPokemon, move);
    }
    int finalDamage = (initialDamage / 50) + 2;
    //FIXME recalculate damage
    return static_cast<int>(static_cast<float>(finalDamage) * stabCheck(attackingPokemon, move) * getTypeEffective(move, defendingPokemon) *
                            criticalHit(crit));
}

void attack(Pokemon &defendingPokemon, Move &move, int damage) {
    // damage will be negative if the attack misses
    if (damage > 0)
        defendingPokemon.setHP(defendingPokemon.getHP() - damage);

    move.setPP(move.getPP() - 1);
}

void attackMessage(const Pokemon &attackingPokemon, const Pokemon &defendingPokemon, int move, int damage, bool criticalHit) {
    printMessage(attackingPokemon.getName() + " used " + attackingPokemon[move].getName() + "! ");
    sleep(1);
    // damage will be negative if the attack misses
    if (damage > 0) {
        if (getTypeEffective(attackingPokemon[move], defendingPokemon) == 0.0) {
            printMessage("It doesn't affect " + defendingPokemon.getName() + "...\n");
            sleep(1);
        }
        else if (getTypeEffective(attackingPokemon[move], defendingPokemon) >= 2.0) {
            printMessage(attackingPokemon[move].getName() + " did " + std::to_string(damage) + " damage! ");
            sleep(1);
            printMessage("It's super effective!\n");
            sleep(1);
            if (criticalHit) {
                printMessage("A critical hit! ");
                sleep(1);
            }
        }
        else if (getTypeEffective(attackingPokemon[move], defendingPokemon) <= 0.5) {
            printMessage(attackingPokemon[move].getName() + " did " + std::to_string(damage) + " damage! ");
            sleep(1);
            printMessage("It's not very effective...\n");
            sleep(1);
            if (criticalHit) {
                printMessage("A critical hit! ");
                sleep(1);
            }
        }
        else {
            printMessage(attackingPokemon[move].getName() + " did " + std::to_string(damage) + " damage!\n");
            sleep(1);
        }
    }
    else {
        printMessage(defendingPokemon.getName() + " avoided the attack!\n");
        sleep(1);
    }
    std::cout.flush();
}

void attackErrorMessage() {
    printMessage("That move is out of PP. Please select another move.\n");
    sleep(2);
}

void takeDamage(Trainer t, int damage) {
    t[0].setHP(t[0].getHP() - damage);
    if (t[0].isFainted()) {
        t[0].faint();
        t.incFaintCount();
    }
}

namespace status {
    void takeDamageMessage(const Pokemon& pokemon) {
        if (pokemon.getStatus() == "burn")
            printMessage(pokemon.getName() + "took damage from it's burn!\n");

        else if (pokemon.getStatus() == "poison")
            printMessage(pokemon.getName() + " took damage from it's poisoning!\n");

        sleep(1);
    }
}

struct battlePhase {
private:
    static void SwitchOut(Trainer &trainer, bool isUser) {
        int toSwitch;

        if (isUser) {
            forcedSwitchPrompt();

            if (getChar({'f', 'r'}) == 'r') {
                bool runSuccess = run();
                runMessage(runSuccess);
                if (runSuccess)
                    exit(0);
            }

            while (true) {
                displayPokemon(trainer);
                toSwitch = getInt(2, trainer.partySize()) - 1;

                if (trainer[toSwitch].isFainted())
                    hpEmptyMessage(trainer[toSwitch - 1]);

                else
                    break;
            }
        }

        else {
            toSwitch = generateInteger(0, trainer.partySize() - 1);
            while (trainer[toSwitch].isFainted())
                toSwitch = generateInteger(0, trainer.partySize() - 1);
        }

        switchOut(trainer, toSwitch);
        sendOutMessage(trainer[0]);
    }

    static void Attack(Trainer &attacker, Trainer &defender, int move, bool &switched, bool isUserAttacking) {
        bool crit = false;
        int damage = calculateDamage(attacker[0], defender[0], attacker[0][move], crit);

        attack(defender[0], attacker[0][move], damage);
        attackMessage(attacker[0], defender[0], move, damage, crit);

        if (defender[0].isFainted()) {
            defender[0].faint();
            defender.incFaintCount();
            faintMessage(defender[0]);
            if (not defender.canFight()) {
                isUserAttacking ? winMessage() : loseMessage();
                exit(0);
            }
            else {
                isUserAttacking ? SwitchOut(defender, false) : SwitchOut(defender, true);
                switched = true;
            }
        }
    }

    static void PostStatus(Trainer &trainer, bool isUser) {
        takeDamage(trainer, static_cast<int>(trainer[0].getMaxHp() * .0625));
        status::takeDamageMessage(trainer[0]);

        if (not trainer.canFight()) {
            isUser ? loseMessage() : winMessage();
            exit(0);
        }
        else
            isUser ? SwitchOut(trainer, true) : SwitchOut(trainer, false);
    }

    // This function commences attacking of each Pokemon and takes into account who is faster.
    // If a Pokemon is inflicted by a pre-attack status condition (paralysis, sleep, frozen), it cannot attack.
    static void PreStatus(Trainer &user, Trainer &opponent, int userMove, int opponentMove, bool isUserFaster) {
        bool skip = false;
        if (isUserFaster) {
            not preStatus(user[0].getStatus()) ? Attack(user, opponent, userMove, skip, true) : inflictedMessage(user[0]);

            if (not skip)
                not preStatus(opponent[0].getStatus()) ? Attack(opponent, user, opponentMove, skip, false) : inflictedMessage(opponent[0]);
        }
        else {
            not preStatus(opponent[0].getStatus()) ? Attack(opponent, user, opponentMove, skip, false) : inflictedMessage(opponent[0]);

            if (not skip)
                not preStatus(user[0].getStatus()) ? Attack(user, opponent, userMove, skip, true) : inflictedMessage(user[0]);
        }
    }

    // If a Pokemon is inflicted with a post-move status condition (burn, poison), it will take damage based on max HP.
    static void PostStatus(Trainer &user, Trainer &opponent, bool isUserFaster) {
        if (isUserFaster) {
            // if Pokémon is inflicted with a post-move status condition...
            if (postStatus(user[0].getStatus()))
                PostStatus(user, true);

            // if Pokémon is inflicted with a post-move status condition...
            if (postStatus(opponent[0].getStatus()))
                PostStatus(opponent, false);
        }
        else {
            // if Pokémon is inflicted with a post-move status condition...
            if (postStatus(opponent[0].getStatus()))
                PostStatus(opponent, false);

            // if Pokémon is inflicted with a post-move status condition...
            if (postStatus(user[0].getStatus()))
                PostStatus(user, true);
        }
    }

public:
    static void fight(Trainer &user, Trainer &opponent, int userMove, size_t &turn) {
        int opponentMove = generateInteger(0, opponent[0].numMoves() - 1);
        // re-selects opponent move if it's out of PP
        while (not opponent[0][opponentMove].canUse())
            opponentMove = generateInteger(0, 3);

        bool skip = false;
        // if trainer chose to attack this turn...
        if (userMove != 0) {
            // if trainer is faster than opponent...
            if (user[0].isFasterThan(opponent[0])) {
                PreStatus(user, opponent, userMove - 1, opponentMove, true);
                PostStatus(user, opponent, true);
            }
            // if opponent is faster than trainer...
            else if (opponent[0].isFasterThan(user[0])) {
                PreStatus(user, opponent, userMove - 1, opponentMove, false);
                PostStatus(user, opponent, false);
            }
            // if trainer and opponent rival in speed; choose randomly
            else {
                if (generateInteger(0, 1) == 0) {
                    PreStatus(user, opponent, userMove - 1, opponentMove, true);
                    PostStatus(user, opponent, true);
                }
                else {
                    PreStatus(user, opponent, userMove - 1, opponentMove, false);
                    PostStatus(user, opponent, false);
                }
            }
        }
        // trainer chose not to attack this turn
        else {
            not preStatus(opponent[0].getStatus()) ? Attack(opponent, user, opponentMove, skip, false) : inflictedMessage(opponent[0]);

            // if trainer is faster than opponent...
            if (user[0].isFasterThan(opponent[0]))
                PostStatus(user, opponent, true);

            // if opponent is faster than trainer...
            else if (opponent[0].isFasterThan(user[0]))
                PostStatus(user, opponent, false);

            // if trainer and opponent rival in speed; choose randomly
            else
                generateInteger(0, 1) == 1 ? PostStatus(user, opponent, true) : PostStatus(user, opponent, false);
        }
        ++turn;
    }
};