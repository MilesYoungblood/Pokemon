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

int getPhysicalAttack(const Pokemon &attackingPokemon, const Pokemon &defendingPokemon, Move &move) {
    int levelCalc = (2 * attackingPokemon.getLevel() / 5) + 2;
    return levelCalc * attackingPokemon.getBaseAttack() * move.getDamage() / defendingPokemon.getBaseDefense();
}

int getSpecialAttack(const Pokemon &attackingPokemon, const Pokemon &defendingPokemon, Move &move) {
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

int calculateDamage(const Pokemon &attackingPokemon, const Pokemon &defendingPokemon, Move &move, bool &crit) {
    int initialDamage{};
    if (move.getCategory() == "physical")
        initialDamage = getPhysicalAttack(attackingPokemon, defendingPokemon, move);

    else if (move.getCategory() == "special")
        initialDamage = getSpecialAttack(attackingPokemon, defendingPokemon, move);

    int finalDamage = (initialDamage / 50) + 2;
    //FIXME recalculate damage
    return static_cast<int>(static_cast<float>(finalDamage) * stabCheck(attackingPokemon, move) * getTypeEffective(move, defendingPokemon) *
                            criticalHit(crit));
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
        printMessage(pokemon.getName() + " took " + std::to_string(static_cast<int>(pokemon.getMaxHp() * .0625)) + " damage from it's ");
        if (pokemon.getStatus() == "burn")
            printMessage( "burn!\n");

        else if (pokemon.getStatus() == "poison")
            printMessage("poisoning!\n");

        sleep(1);
    }
}

struct battlePhase {
private:
    static void SwitchOut(Trainer &trainer, bool isUser, bool &keepPlaying) {
        int toSwitch;

        if (isUser) {
            forcedSwitchPrompt();

            if (getChar({'f', 'r'}) == 'r') {
                bool runSuccess = run();
                runMessage(runSuccess);
                if (runSuccess)
                    keepPlaying = false;
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

    static void Action(Trainer &attacker, Trainer &defender, int move, bool &switched, bool isUserAttacking, bool &keepPlaying) {
        bool crit = false;
        int damage = calculateDamage(attacker[0], defender[0], attacker[0][move], crit);

        attacker[0][move].action(attacker[0], defender[0], damage);
        attacker[0][move].actionMessage(attacker[0], defender[0], damage, crit, getTypeEffective(attacker[0][move], defender[0]));

        if (defender[0].isFainted()) {
            defender[0].faint();
            defender.incFaintCount();
            faintMessage(defender[0]);
            if (not defender.canFight()) {
                //TODO add defeat()
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
        takeDamage(trainer, static_cast<int>(trainer[0].getMaxHp() * .0625));
        status::takeDamageMessage(trainer[0]);

        if (not trainer.canFight()) {
            //TODO add defeat()
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
        if (userMove != 0) {
            // if trainer is faster than opponent...
            if (user[0].isFasterThan(opponent[0])) {
                PreStatus(user, opponent, userMove - 1, opponentMove, true, keepPlaying);
                PostStatus(user, opponent, true, keepPlaying);
            }
            // if opponent is faster than trainer...
            else if (opponent[0].isFasterThan(user[0])) {
                PreStatus(user, opponent, userMove - 1, opponentMove, false, keepPlaying);
                PostStatus(user, opponent, false, keepPlaying);
            }
            // if trainer and opponent rival in speed; choose randomly
            else {
                if (generateInteger(0, 1) == 0) {
                    PreStatus(user, opponent, userMove - 1, opponentMove, true, keepPlaying);
                    PostStatus(user, opponent, true, keepPlaying);
                }
                else {
                    PreStatus(user, opponent, userMove - 1, opponentMove, false, keepPlaying);
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