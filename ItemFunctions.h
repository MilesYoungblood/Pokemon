//
// Created by Miles Youngblood on 6/7/2022.
//

#pragma once

void failMessage() {
    std::cout << "But it failed!\n";
    sleep(1);
}

void displayBag() {
    std::cout << "Choose an option:\n";
    std::cout << "\tHP/PP restore  (1)\n";
    std::cout << "\tStatus restore (2)\n";
    std::cout << "\tPoke Balls     (3)\n";
    std::cout << "\tBattle Items   (4)\n";
    std::cout << "\nCancel (0)\n";
    std::cout.flush();
}

template <typename T>
void displayItems(const std::vector<T>& items) {
    std::cout << "Choose an item:\n";
    for (int i = 0; i < items.size(); ++i) {
        std::cout << '\t' << items.at(i).getName() << std::string(15 - items.at(i).getName().length(), ' ') << " x" << items.at(i).getQuantity() << " (" << i + 1 << ")\n";
    }
    std::cout << "\nCancel (0)\n";
    std::cout.flush();
}

namespace HP {
    void restore(Pokemon &pokemonToRestore, int amountToRestore) {
        pokemonToRestore.setHP(pokemonToRestore.getHP() + amountToRestore);
        if (pokemonToRestore.getHP() > pokemonToRestore.getMaxHp()) {
            pokemonToRestore.setHP(pokemonToRestore.getMaxHp());
        }
    }

    void restoreMessage(const Pokemon &pokemonRestored, int amountRestored) {
        std::cout << pokemonRestored.getName() << " recovered " << amountRestored << " HP!\n";
        sleep(2);
    }
}

namespace PP {
    void restore(Moves &moveToRestore, int amountToRestore) {
        moveToRestore.setPP(moveToRestore.getPP() + amountToRestore);
        if (moveToRestore.getPP() > moveToRestore.getMaxPP()) {
            moveToRestore.setPP(moveToRestore.getMaxPP());
        }
    }

    void restoreMessage(const Moves &moveRestored, int amountRestored) {
        std::cout << moveRestored.getName() << " recovered " << amountRestored << " PP!\n";
        sleep(2);
    }
}

void cure(Pokemon& pokemonToCure, const StatusItems& itemToUse) {
    if (pokemonToCure.getStatus() == itemToUse.getRestoreType()) {
        pokemonToCure.setStatus("No status");
    }
}

void cureMessage(const Pokemon& pokemonCured, const std::string& status) {
    if (pokemonCured.getStatus() == "No status") {
        std::cout << pokemonCured.getName() << " recovered from " << status << "!\n";
        sleep(1);
    }
    else {
        failMessage();
    }
}

bool catchPokemon(bool& firstShake, bool& secondShake, bool& thirdShake) {
    // FIXME catch function does not take into account levels or catch rates
    firstShake = generateInteger(1, 100) < 75;
    secondShake = generateInteger(1, 100) < 65;
    thirdShake = generateInteger(1, 100) < 55;

    return firstShake and secondShake and thirdShake;
}

void catchPokemonMessage(const std::string& pokemon, bool first, bool second, bool third) {
    std::cout << "1...";
    sleep(1);
    if (first) {
        std::cout << "2...";
        sleep(1);
        if (second) {
            std::cout << "3...";
            sleep(1);
            if (third) {
                std::cout << "Gotcha! " << pokemon << " was caught!\n";
                sleep(1);
            }
            else {
                std::cout << "Almost had it!\n";
                sleep(1);
            }
        }
        else {
            std::cout << "No! " << pokemon << " escaped from the Poke Ball!\n";
            sleep(1);
        }
    }
    else {
        std::cout << "Not even close!\n";
        sleep(1);
    }
    std::cout.flush();
}

void boostStat(const BattleItems& itemToUse, Pokemon& pokemonToBoost, int amountToBoost, bool& limitReached) {
    if (itemToUse.getStat() == "attack") {
        pokemonToBoost.setAttack(pokemonToBoost.getAttack() + amountToBoost);
        if (pokemonToBoost.getAttack() > 6) {
            pokemonToBoost.setAttack(6);
            limitReached = true;
        }
    }
    else if (itemToUse.getStat() == "spAttack") {
        pokemonToBoost.setSpAttack(pokemonToBoost.getSpAttack() + amountToBoost);
        if (pokemonToBoost.getSpAttack() > 6) {
            pokemonToBoost.setSpAttack(6);
            limitReached = true;
        }
    }
    else if (itemToUse.getStat() == "defense") {
        pokemonToBoost.setDefense(pokemonToBoost.getDefense() + amountToBoost);
        if (pokemonToBoost.getDefense() > 6) {
            pokemonToBoost.setDefense(6);
            limitReached = true;
        }
    }
    else if (itemToUse.getStat() == "spDefense") {
        pokemonToBoost.setSpDefense(pokemonToBoost.getSpDefense() + amountToBoost);
        if (pokemonToBoost.getSpDefense() > 6) {
            pokemonToBoost.setSpDefense(6);
            limitReached = true;
        }
    }
    else if (itemToUse.getStat() == "speed") {
        pokemonToBoost.setSpeed(pokemonToBoost.getSpeed() + amountToBoost);
        if (pokemonToBoost.getSpeed() > 6) {
            pokemonToBoost.setSpeed(6);
            limitReached = true;
        }
    }
    else if (itemToUse.getStat() == "accuracy") {
        pokemonToBoost.setAccuracy(pokemonToBoost.getAccuracy() + amountToBoost);
        if (pokemonToBoost.getAccuracy() > 6) {
            pokemonToBoost.setAccuracy(6);
            limitReached = true;
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

template <typename T>
void useItem(T& itemToUse) {
    itemToUse.setQuantity(itemToUse.getQuantity() - 1);
}

void useItemMessage(const std::string& itemUsed) {
    if (itemUsed.substr(itemUsed.size() - 4) != "Ball") {
        std::cout << "You used a";

        if (isVowel(itemUsed.at(0))) {
            std::cout << 'n';
        }

        std::cout << ' ' << itemUsed << "! ";
    }
    else {
        std::cout << "You threw a " << itemUsed << "! ";
    }
    sleep(1);
}

void itemErrorMessage(const std::string& item) {
    std::cout << "You don't have any " << item << "'s." << std::endl;
    sleep(1);
}

void noEffectMessage(const std::string& item, const std::string& pokemon) {
    std::cout << item << " had no effect on " << pokemon << ".\n";
    sleep(1);
}