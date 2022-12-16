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

template <typename Item>
void displayItems(const std::vector<Item> &items) {
    std::cout << "Choose an item:\n";
    for (int i = 0; i < items.size(); ++i) {
        std::cout << '\t' << items[i].getName() << std::string(15 - items[i].getName().length(), ' ') << " x" << items[i].getQuantity() << " (" << i + 1 << ")\n";
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
        std::cout << pokemonRestored << " recovered " << amountRestored << " HP!\n";
        sleep(2);
    }
}

namespace PP {
    void restore(Move &moveToRestore, int amountToRestore) {
        moveToRestore.setPP(moveToRestore.getPP() + amountToRestore);
        if (moveToRestore.getPP() > moveToRestore.getMaxPP()) {
            moveToRestore.setPP(moveToRestore.getMaxPP());
        }
    }

    void restoreMessage(const Move &moveRestored, int amountRestored) {
        std::cout << moveRestored << " recovered " << amountRestored << " PP!\n";
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
        std::cout << pokemonCured << " recovered from " << status << "!\n";
        sleep(1);
    }
    else {
        failMessage();
    }
}

bool catchPokemon(bool attempts[]) {
    //FIXME catch function does not take into account levels or catch rates
    attempts[0] = generateInteger(1, 100) < 80;
    attempts[1] = generateInteger(1, 100) < 70;
    attempts[2] = generateInteger(1, 100) < 60;
    attempts[3] = generateInteger(1, 100) < 50;

    return attempts[0] and attempts[1] and attempts[2] and attempts[3];
}

void catchPokemonMessage(const std::string &pokemon, const bool attempts[]) {
    if (attempts[0]) {
        std::cout << "1...";
        sleep(1);
        if (attempts[1]) {
            std::cout << "2...";
            sleep(1);
            if (attempts[2]) {
                std::cout << "3...";
                sleep(1);
                if (attempts[3]) {
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
            std::cout << pokemon << " failed to be caught!\n";
            sleep(1);
        }
    }
    else {
        std::cout << "Not even close!\n";
        sleep(1);
    }
    std::cout.flush();
}

void boostStat(const BattleItems &itemToUse, Pokemon &pokemonToBoost, int amountToBoost, bool &limitReached) {
    if (itemToUse.getStat() == "attack") {
        if (pokemonToBoost.getAttack() < 6) {
            pokemonToBoost.setAttack(pokemonToBoost.getAttack() + amountToBoost);
        }
        else {
            limitReached = true;
        }
    }
    else if (itemToUse.getStat() == "spAttack") {
        if (pokemonToBoost.getSpAttack() < 6) {
            pokemonToBoost.setSpAttack(pokemonToBoost.getSpAttack() + amountToBoost);
        }
        else {
            limitReached = true;
        }
    }
    else if (itemToUse.getStat() == "defense") {
        if (pokemonToBoost.getDefense() < 6) {
            pokemonToBoost.setDefense(pokemonToBoost.getDefense() + amountToBoost);
        }
        else {
            limitReached = true;
        }
    }
    else if (itemToUse.getStat() == "spDefense") {
        if (pokemonToBoost.getSpDefense() < 6) {
            pokemonToBoost.setSpDefense(pokemonToBoost.getSpDefense() + amountToBoost);
        }
        else {
            limitReached = true;
        }
    }
    else if (itemToUse.getStat() == "speed") {
        if (pokemonToBoost.getSpeed() < 6) {
            pokemonToBoost.setSpeed(pokemonToBoost.getSpeed() + amountToBoost);
        }
        else {
            limitReached = true;
        }
    }
    else if (itemToUse.getStat() == "accuracy") {
        if (pokemonToBoost.getAccuracy() < 6) {
            pokemonToBoost.setAccuracy(pokemonToBoost.getAccuracy() + amountToBoost);
        }
        else {
            limitReached = true;
        }
    }
}

void boostMessage(const Pokemon &pokemon, const std::string &statBoosted, int amountBoosted, bool limit) {
    if (not limit) {
        std::cout << pokemon << "'s " << statBoosted << " rose";
        if (amountBoosted == 2) {
            std::cout << " sharply";
        }
        else if (amountBoosted > 2) {
            std::cout << " drastically";
        }
        std::cout << '!' << std::endl;
    }
    else {
        std::cout << pokemon << "'s " << statBoosted << " can't go any higher!" << std::endl;
    }
    sleep(2);
}

template <typename I>
void useItem(I &itemToUse) {
    itemToUse.setQuantity(itemToUse.getQuantity() - 1);
}

void useItemMessage(const std::string &itemUsed) {
    if (itemUsed.substr(itemUsed.length() - 4) != "Ball") {
        std::cout << "You used a";

        if (isVowel(itemUsed[0])) {
            std::cout << 'n';
        }

        std::cout << ' ' << itemUsed << "! ";
    }
    else {
        std::cout << "You threw a";

        if (isVowel(itemUsed[0])) {
            std::cout << 'n';
        }

        std::cout << ' ' << itemUsed << "! ";
    }
    sleep(1);
}

void itemErrorMessage(const std::string &item) {
    std::cout << "You don't have any " << item << "'s." << std::endl;
    sleep(1);
}

void noEffectMessage(const std::string &item, const Pokemon &pokemon) {
    std::cout << item << " had no effect on " << pokemon << ".\n";
    sleep(1);
}