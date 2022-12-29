//
// Created by Miles Youngblood on 6/7/2022.
//

#pragma once

#include "TypeChart.h"
#include "GeneralFunctions.h"

void displayMoves(const Pokemon &pokemon) {
    std::cout << "Choose a move:\n";
    for (int i = 0; i < pokemon.numMoves(); ++i) {
        std::cout << '\t' << pokemon[i].getName() << std::string(15 - pokemon[i].getName().length(), ' ')
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
    return pokemon.getType() == move.getType() or pokemon.getType(1) == move.getType() ? 1.5f : 1.0f;
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
    std::cout << "Final Damage: " << finalDamage << std::endl;
    return static_cast<int>(static_cast<float>(finalDamage) * stabCheck(attackingPokemon, move) * getTypeEffective(move, defendingPokemon) *
                            criticalHit(crit));
}

void attack(Pokemon &defendingPokemon, Move &move, int damage) {
    // damage will be negative if the attack misses
    if (damage > 0) {
        defendingPokemon.setHP(defendingPokemon.getHP() - damage);
    }
    move.setPP(move.getPP() - 1);
}

void attackMessage(const Pokemon &attackingPokemon, const Pokemon &defendingPokemon, int move, int damage, bool criticalHit) {
    std::cout << attackingPokemon << " used " << attackingPokemon[move] << "! ";
    sleep(1);
    // damage will be negative if the attack misses
    if (damage > 0) {
        if (getTypeEffective(attackingPokemon[move], defendingPokemon) == 0.0) {
            std::cout << "It doesn't affect " << defendingPokemon << "...\n";
            sleep(1);
        }
        else if (getTypeEffective(attackingPokemon[move], defendingPokemon) >= 2.0) {
            std::cout << attackingPokemon[move] << " did " << damage << " damage! ";
            sleep(1);
            std::cout << "It's super effective!\n";
            sleep(1);
            if (criticalHit) {
                std::cout << "A critical hit! ";
                sleep(1);
            }
        }
        else if (getTypeEffective(attackingPokemon[move], defendingPokemon) <= 0.5) {
            std::cout << attackingPokemon[move] << " did " << damage << " damage! ";
            sleep(1);
            std::cout << "It's not very effective...\n";
            sleep(1);
            if (criticalHit) {
                std::cout << "A critical hit! ";
                sleep(1);
            }
        }
        else {
            std::cout << attackingPokemon[move] << " did " << damage << " damage!\n";
            sleep(1);
        }
    }
    else {
        std::cout << defendingPokemon << " avoided the attack!\n";
        sleep(1);
    }
    std::cout.flush();
}

void attackErrorMessage() {
    std::cout << "That move is out of PP. Please select another move.\n";
    sleep(2);
}

void takeDamage(Trainer t, int damage) {
    t[0].setHP(t[0].getHP() - damage);
    if (t[0].getHP() <= 0) {
        t[0].faint();
        t.incFaintCount();
    }
}

namespace status {
    void takeDamageMessage(const Pokemon& pokemon) {
        if (pokemon.getStatus() == "burn") {
            std::cout << pokemon << " took damage from it's burn!\n";
        }
        else if (pokemon.getStatus() == "poison") {
            std::cout << pokemon << " took damage from it's poisoning!\n";
        }
        sleep(1);
    }
}