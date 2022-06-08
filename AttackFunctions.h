//
// Created by Miles Youngblood on 6/7/2022.
//

#ifndef POKEMON_BATTLE_ATTACK_FUNCTIONS_H
#define POKEMON_BATTLE_ATTACK_FUNCTIONS_H

void displayMoves(Pokemon& pokemon) {
    std::cout << "Choose a move:\n";
    for (int i = 0; i < NUM_MOVES; ++i) {
        std::cout << '\t' << pokemon.getMove(i).getName() << std::string(15 - pokemon.getMove(i).getName().length(), ' ')
                  << " (PP: " << pokemon.getMove(i).getPP() << std::string(2 - std::to_string(pokemon.getMove(i).getPP()).length(), ' ')
                  << '/' << pokemon.getMove(i).getMaxPP() << std::string(2 - std::to_string(pokemon.getMove(i).getMaxPP()).length(), ' ')
                  << ") -> " << i + 1 << '\n';
    }
    std::cout << "\nGo back (0)\n";
}

int getPhysicalAttack(const Pokemon& attackingPokemon, const Pokemon& defendingPokemon, const Moves& move) {
    int levelCalc = (2 * attackingPokemon.getLevel() / 5) + 2;
    int finalCalc = levelCalc * attackingPokemon.getBaseAttack() * move.getPower() / defendingPokemon.getBaseDefense();
    return finalCalc;
}

int getSpecialAttack(const Pokemon& attackingPokemon, const Pokemon& defendingPokemon, const Moves& move) {
    int levelCalc = (2 * attackingPokemon.getLevel() / 5) + 2;
    int finalCalc = levelCalc * attackingPokemon.getSpAttack() * move.getPower() / defendingPokemon.getSpDefense();
    return finalCalc;
}

double stabCheck(const Pokemon& pokemon, const Moves& move) {
    if (pokemon.getType(0) == move.getType() or pokemon.getType(1) == move.getType()) {
        return 1.5;
    }
    else {
        return 1.0;
    }
}

int calculateDamage(const Pokemon& attackingPokemon, const Pokemon& defendingPokemon, const Moves& move) {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(85, 100);

    int initialDamage = 0, finalDamage;
    if (move.getCategory() == "physical") {
        initialDamage = getPhysicalAttack(attackingPokemon, defendingPokemon, move);
    }
    else if (move.getCategory() == "special") {
        initialDamage = getSpecialAttack(attackingPokemon, defendingPokemon, move);
    }
    finalDamage = (initialDamage / 50) + 2;
    finalDamage = (int)(finalDamage * stabCheck(attackingPokemon, move));
    finalDamage = finalDamage * dist(mt) / 100;

    return finalDamage;
}

void attack(Pokemon& defendingPokemon, Moves& move, int damage, bool& landed) {
    if (damage != -1) {
        defendingPokemon.setHP(defendingPokemon.getHP() - damage);
        landed = true;
    }
    move.setPP(move.getPP() - 1);
}

void attackMessage(Pokemon& attackingPokemon, const Pokemon& defendingPokemon, int move, int damage, bool landed) {
    std::cout << attackingPokemon.getName() << " used " << attackingPokemon.getMove(move).getName() << "! ";
    sleep(1);
    if (landed) {
        std::cout << attackingPokemon.getMove(move).getName() << " did " << damage << " damage!\n";
    }
    else {
        std::cout << defendingPokemon.getName() << " avoided the attack!\n";
    }
    sleep(2);
}

void attackErrorMessage() {
    std::cout << "That move is out of PP. Please select another move.\n";
    sleep(2);
}

#endif //POKEMON_BATTLE_ATTACK_FUNCTIONS_H
