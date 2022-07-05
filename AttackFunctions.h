//
// Created by Miles Youngblood on 6/7/2022.
//

#pragma once

#include "TypeChart.h"
#include "GeneralFunctions.h"

void displayMoves(Pokemon& pokemon) {
    std::cout << "Choose a move:\n";
    for (int i = 0; i < NUM_MOVES; ++i) {
        std::cout << '\t' << pokemon.getMove(i).getName() << std::string(15 - pokemon.getMove(i).getName().length(), ' ')
                  << " (PP: " << pokemon.getMove(i).getPP() << std::string(2 - std::to_string(pokemon.getMove(i).getPP()).length(), ' ')
                  << '/' << pokemon.getMove(i).getMaxPP() << std::string(2 - std::to_string(pokemon.getMove(i).getMaxPP()).length(), ' ')
                  << ") -> " << i + 1 << '\n';
    }
    std::cout << "\nCancel (0)\n";
    std::cout.flush();
}

void displayMoveSummary(const Moves& move) {
    std::cout << move.getName() << '\n';
    std::cout << "\tType:     " << move.getType() << '\n';
    std::cout << "\tCategory: " << move.getCategory() << '\n';
    std::cout << "\tPower:    " << move.getPower() << '\n';
    std::cout << "\tAccuracy: " << move.getAccuracy() << '\n';
    std::cout << "\tPP:       " << move.getPP() << '/' << move.getMaxPP() << '\n';
    std::cout << "\nCancel (0)\n";
    std::cout.flush();
}

int getPhysicalAttack(const Pokemon& attackingPokemon, const Pokemon& defendingPokemon, Moves move) {
    int levelCalc = (2 * attackingPokemon.getLevel() / 5) + 2;
    int finalCalc = levelCalc * attackingPokemon.getBaseAttack() * move.getDamage() / defendingPokemon.getBaseDefense();
    return finalCalc;
}

int getSpecialAttack(const Pokemon& attackingPokemon, const Pokemon& defendingPokemon, Moves move) {
    int levelCalc = (2 * attackingPokemon.getLevel() / 5) + 2;
    int finalCalc = levelCalc * attackingPokemon.getBaseSpAttack() * move.getDamage() / defendingPokemon.getBaseSpDefense();
    return finalCalc;
}

int criticalHit(bool& crit) {
    if (generateInteger(1, 16) == 1) {
        crit = true;
        return 2;
    }
    else {
        crit = false;
        return 1;
    }
}

float stabCheck(const Pokemon& pokemon, const Moves& move) {
    if (pokemon.getType() == move.getType() or pokemon.getType(1) == move.getType()) {
        return 1.5f;
    }
    else {
        return 1.0f;
    }
}

int calculateDamage(const Pokemon& attackingPokemon, const Pokemon& defendingPokemon, const Moves& move, bool& crit) {
    int initialDamage = 0;
    if (move.getCategory() == "physical") {
        initialDamage = getPhysicalAttack(attackingPokemon, defendingPokemon, move);
    }
    else if (move.getCategory() == "special") {
        initialDamage = getSpecialAttack(attackingPokemon, defendingPokemon, move);
    }
    int finalDamage = (initialDamage / 50) + 2;
    finalDamage = static_cast<int>(static_cast<float>(finalDamage) * stabCheck(attackingPokemon, move) * getTypeEffective(move, defendingPokemon) *
                  static_cast<float>(criticalHit(crit)));

    return finalDamage;
}

void attack(Pokemon& defendingPokemon, Moves& move, int damage, bool& landed) {
    if (damage >= 0) { // damage will be negative if the attack misses
        defendingPokemon.setHP(defendingPokemon.getHP() - damage);
        landed = true;
    }
    move.setPP(move.getPP() - 1);
}

void attackMessage(Pokemon& attackingPokemon, const Pokemon& defendingPokemon, int move, int damage, bool landed, bool criticalHit) {
    std::cout << attackingPokemon.getName() << " used " << attackingPokemon.getMove(move).getName() << "! ";
    sleep(1);
    if (landed) {
        if (getTypeEffective(attackingPokemon.getMove(move), defendingPokemon) == 0.0) {
            std::cout << "It doesn't affect " << defendingPokemon.getName() << "...\n";
            sleep(1);
        }
        else if (getTypeEffective(attackingPokemon.getMove(move), defendingPokemon) >= 2.0) {
            std::cout << attackingPokemon.getMove(move).getName() << " did " << damage << " damage! ";
            std::cout << "It's super effective!\n";
            sleep(1);
            if (criticalHit) {
                std::cout << "A critical hit! ";
                sleep(1);
            }
        }
        else if (getTypeEffective(attackingPokemon.getMove(move), defendingPokemon) <= 0.5) {
            std::cout << attackingPokemon.getMove(move).getName() << " did " << damage << " damage! ";
            std::cout << "It's not very effective...\n";
            sleep(1);
            if (criticalHit) {
                std::cout << "A critical hit! ";
                sleep(1);
            }
        }
        else {
            std::cout << '\n';
        }
    }
    else {
        std::cout << defendingPokemon.getName() << " avoided the attack!\n";
        sleep(1);
    }
    std::cout.flush();
}

void attackErrorMessage() {
    std::cout << "That move is out of PP. Please select another move.\n";
    sleep(2);
}

void takeDamage(Pokemon& pokemon, int damage) {
    pokemon.setHP(pokemon.getHP() - damage);
}

namespace status {
    void takeDamageMessage(const Pokemon& pokemon) {
        if (pokemon.getStatus() == "burn") {
            std::cout << pokemon.getName() << " took damage from it's burn!\n";
        }
        else if (pokemon.getStatus() == "poison") {
            std::cout << pokemon.getName() << " took damage from it's poisoning!\n";
        }
        sleep(1);
    }
}