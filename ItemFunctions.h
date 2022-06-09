//
// Created by Miles Youngblood on 6/7/2022.
//

#ifndef POKEMON_BATTLE_ITEM_FUNCTIONS_H
#define POKEMON_BATTLE_ITEM_FUNCTIONS_H

void displayBag() {
    std::cout << "Choose an option:\n";
    std::cout << "\tHP/PP restore  (1)\n";
    std::cout << "\tStatus restore (2)\n";
    std::cout << "\tPoke Balls     (3)\n";
    std::cout << "\tBattle Items   (4)\n";
    std::cout << "\nCancel (0)\n";
}

template <typename T>
void displayItems(const std::vector<T>& items) {
    std::cout << "Choose an item:\n";
    for (int i = 0; i < items.size(); ++i) {
        std::cout << "   " << items.at(i).getName() << " x" << items.at(i).getQuantity() << std::string(15 - items.at(
                i).getName().length(), ' ')
                  << " (" << i + 1 << ")\n";
    }
    std::cout << "\nCancel (0)\n";
}

void restore(Pokemon& pokemonToRestore, int amountToRestore) { // HP variant
    pokemonToRestore.setHP(pokemonToRestore.getHP() + amountToRestore);
    if (pokemonToRestore.getHP() > pokemonToRestore.getMaxHp()) {
        pokemonToRestore.setHP(pokemonToRestore.getMaxHp());
    }
}

void restore(Moves& moveToRestore, int amountToRestore) { // PP variant
    moveToRestore.setPP(moveToRestore.getPP() + amountToRestore);
    if (moveToRestore.getPP() > moveToRestore.getMaxPP()) {
        moveToRestore.setPP(moveToRestore.getMaxPP());
    }
}

void restoreMessage(const Pokemon& pokemonRestored, int amountRestored) { // HP variant
    std::cout << pokemonRestored.getName() << " recovered " << amountRestored << " HP!\n";
    sleep(2);
}

void restoreMessage(const Moves& moveRestored, int amountRestored) { // PP variant
    std::cout << moveRestored.getName() << " recovered " << amountRestored << " PP!\n";
    sleep(2);
}

void cure(Pokemon& pokemonToCure, const StatusItems& itemToUse) {
    if (itemToUse.getRestoreType() == "paralysis") {
        if (pokemonToCure.getStatus() == "paralyzed") {
            pokemonToCure.setStatus("No status");
        }
    }
    else if (itemToUse.getRestoreType() == "burn") {
        if (pokemonToCure.getStatus() == "burned") {
            pokemonToCure.setStatus("No status");
        }
    }
    else if (itemToUse.getRestoreType() == "freeze") {
        if (pokemonToCure.getStatus() == "frozen") {
            pokemonToCure.setStatus("No status");
        }
    }
    else if (itemToUse.getRestoreType() == "poison") {
        if (pokemonToCure.getStatus() == "poisoned") {
            pokemonToCure.setStatus("No status");
        }
    }
    else if (itemToUse.getRestoreType() == "sleep") {
        if (pokemonToCure.getStatus() == "asleep") {
            pokemonToCure.setStatus("No status");
        }
    }
}

void cureMessage(Pokemon pokemonCured, const std::string& status) {
    if (pokemonCured.getStatus() == "No status") {
        std::cout << pokemonCured.getName() << " recovered from " << status << "!\n";
        sleep(1);
    }
    else {
        std::cout << "But it failed!\n";
        sleep(1);
    }
}

void boostStat(const BattleItems& itemToUse, Pokemon& pokemonToBoost, int amountToBoost, bool& higher) {
    if (itemToUse.getStat() == "getDamage") {
        pokemonToBoost.setAttack(pokemonToBoost.getAttack() + amountToBoost);
        if (pokemonToBoost.getAttack() > 6) {
            pokemonToBoost.setAttack(6);
            higher = true;
        }
    }
    else if (itemToUse.getStat() == "spAttack") {
        pokemonToBoost.setSpAttack(pokemonToBoost.getSpAttack() + amountToBoost);
        if (pokemonToBoost.getSpAttack() > 6) {
            pokemonToBoost.setSpAttack(6);
            higher = true;
        }
    }
    else if (itemToUse.getStat() == "defense") {
        pokemonToBoost.setDefense(pokemonToBoost.getDefense() + amountToBoost);
        if (pokemonToBoost.getDefense() > 6) {
            pokemonToBoost.setDefense(6);
            higher = true;
        }
    }
    else if (itemToUse.getStat() == "spDefense") {
        pokemonToBoost.setSpDefense(pokemonToBoost.getSpDefense() + amountToBoost);
        if (pokemonToBoost.getSpDefense() > 6) {
            pokemonToBoost.setSpDefense(6);
            higher = true;
        }
    }
    else if (itemToUse.getStat() == "speed") {
        pokemonToBoost.setSpeed(pokemonToBoost.getSpeed() + amountToBoost);
        if (pokemonToBoost.getSpeed() > 6) {
            pokemonToBoost.setSpeed(6);
            higher = true;
        }
    }
    else if (itemToUse.getStat() == "accuracy") {
        pokemonToBoost.setAccuracy(pokemonToBoost.getAccuracy() + amountToBoost);
        if (pokemonToBoost.getAccuracy() > 6) {
            pokemonToBoost.setAccuracy(6);
            higher = true;
        }
    }
}

void boostMessage(const Pokemon& pokemon, const std::string& statBoosted, int amountBoosted, bool limit) {
    if (!limit) {
        std::cout << pokemon.getName() << "'s " << statBoosted << " rose";
        if (amountBoosted == 2) {
            std::cout << " sharply";
        }
        else if (amountBoosted > 2) {
            std::cout << " drastically";
        }
        std::cout << '!' << std::endl;
    }
    else {
        std::cout << pokemon.getName() << "'s " << statBoosted << " can't go any higher!" << std::endl;
    }
    sleep(2);
}

void useItemMessage(const std::string& itemUsed) {
    std::cout << "You used " << itemUsed << "! ";
    sleep(1);
}

void itemErrorMessage(const std::string& item) {
    std::cout << "You don't have any " << item << "'s." << std::endl;
}

#endif //POKEMON_BATTLE_ITEM_FUNCTIONS_H
