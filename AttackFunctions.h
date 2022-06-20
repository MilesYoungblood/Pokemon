//
// Created by Miles Youngblood on 6/7/2022.
//

#pragma once

#include "TypeChart.h"

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
    int finalCalc = levelCalc * attackingPokemon.getSpAttack() * move.getDamage() / defendingPokemon.getSpDefense();
    return finalCalc;
}

int criticalHit(bool& crit) {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(1, 16);

    int critical = dist(mt);
    if (critical == 1) {
        crit = true;
        return 2.0;
    }
    else {
        crit = false;
        return 1.0;
    }
}

double stabCheck(const Pokemon& pokemon, const Moves& move) {
    if (pokemon.getType() == move.getType() or pokemon.getType(1) == move.getType()) {
        return 1.5;
    }
    else {
        return 1.0;
    }
}

int calculateDamage(const Pokemon& attackingPokemon, const Pokemon& defendingPokemon, const Moves& move, bool& crit) {
    int initialDamage = 0, finalDamage;
    if (move.getCategory() == "physical") {
        initialDamage = getPhysicalAttack(attackingPokemon, defendingPokemon, move);
    }
    else if (move.getCategory() == "special") {
        initialDamage = getSpecialAttack(attackingPokemon, defendingPokemon, move);
    }
    finalDamage = (initialDamage / 50) + 2;
    finalDamage = static_cast<int>((finalDamage * stabCheck(attackingPokemon, move) * getTypeEffective(move, defendingPokemon) *
            criticalHit(crit)));

    return finalDamage;
}

void attack(Pokemon& defendingPokemon, Moves& move, int damage, bool& landed) {
    if (damage >= 0) {
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
        }
        else if (getTypeEffective(attackingPokemon.getMove(move), defendingPokemon) >= 2.0) {
            std::cout << attackingPokemon.getMove(move).getName() << " did " << damage << " damage! ";
            std::cout << "It's super effective!\n";
            if (criticalHit) {
                std::cout << "A critical hit! ";
            }
        }
        else if (getTypeEffective(attackingPokemon.getMove(move), defendingPokemon) <= 0.5) {
            std::cout << attackingPokemon.getMove(move).getName() << " did " << damage << " damage! ";
            std::cout << "It's not very effective...\n";
            if (criticalHit) {
                std::cout << "A critical hit! ";
            }
        }
        else {
            std::cout << '\n';
        }
    }
    else {
        std::cout << defendingPokemon.getName() << " avoided the attack!\n";
    }
    std::cout.flush();
    sleep(2);
}

void attackErrorMessage() {
    std::cout << "That move is out of PP. Please select another move.\n";
    sleep(2);
}