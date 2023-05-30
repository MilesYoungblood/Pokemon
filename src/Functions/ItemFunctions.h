//
// Created by Miles Youngblood on 6/7/2022.
//

#pragma once

void failMessage() {
    printMessage("But it failed!\n");
    sleep(1);
}

void displayBag() {
    printMessage("Choose an option:\n");
    std::cout << "\tHP/PP restore  (1)\n";
    std::cout << "\tStatus restore (2)\n";
    std::cout << "\tPoke Balls     (3)\n";
    std::cout << "\tBattle Items   (4)\n";
    std::cout << "\nCancel (0)\n";
    std::cout.flush();
}

template <typename Item>
void displayItems(const std::vector<Item> &items) {
    printMessage("Choose an item:\n");
    for (int i = 0; i < items.size(); ++i)
        std::cout << '\t' << items[i].getName() << std::string(15 - items[i].getName().length(), ' ') << " x" << items[i].getQuantity() << " (" << i + 1 << ")\n";

    std::cout << "\nCancel (0)\n";
    std::cout.flush();
}

namespace HP {
    void restore(Pokemon &pokemonToRestore, int amountToRestore) {
        pokemonToRestore.setHP(pokemonToRestore.getHP() + amountToRestore);
        if (pokemonToRestore.getHP() > pokemonToRestore.getMaxHp())
            pokemonToRestore.setHP(pokemonToRestore.getMaxHp());
    }

    void restoreMessage(const Pokemon &pokemonRestored, int amountRestored) {
        printMessage(pokemonRestored.getName() + " recovered " + std::to_string(amountRestored) + " HP!\n");
        sleep(2);
    }
}

namespace PP {
    void restore(Move &moveToRestore, int amountToRestore) {
        moveToRestore.setPP(moveToRestore.getPP() + amountToRestore);
        if (moveToRestore.getPP() > moveToRestore.getMaxPP())
            moveToRestore.setPP(moveToRestore.getMaxPP());
    }

    void restoreMessage(const Move &moveRestored, int amountRestored) {
        printMessage(moveRestored.getName() + " recovered " + std::to_string(amountRestored) + " PP!\n");
        sleep(2);
    }
}

void cure(Pokemon& pokemon, const StatusItem& item) {
    if (pokemon.getStatus() == item.getRestoreType())
        pokemon.setStatus("No status");
}

void cureMessage(const Pokemon& pokemonCured, const std::string& status) {
    if (pokemonCured.getStatus() == "No status") {
        printMessage(pokemonCured.getName() + " recovered from " + status + "!\n");
        sleep(1);
    }
    else
        failMessage();
}

bool catchPokemon(bool attempts[]) {
    // FIXME catch function does not take into account levels or catch rates
    attempts[0] = generateInteger(1, 100) < 80;
    attempts[1] = generateInteger(1, 100) < 70;
    attempts[2] = generateInteger(1, 100) < 60;
    attempts[3] = generateInteger(1, 100) < 50;

    return attempts[0] and attempts[1] and attempts[2] and attempts[3];
}

void catchPokemonMessage(const Pokemon &pokemon, const bool attempts[]) {
    if (attempts[0]) {
        printMessage("1...");
        sleep(1);
        if (attempts[1]) {
            printMessage("2...");
            sleep(1);
            if (attempts[2]) {
                printMessage("3...");
                sleep(1);
                if (attempts[3]) {
                    printMessage("Gotcha! " + pokemon.getName() + " was caught!\n");
                    sleep(1);
                }
                else {
                    printMessage("Almost had it!\n");
                    sleep(1);
                }
            }
            else {
                printMessage("No! " + pokemon.getName() + " escaped!\n");
                sleep(1);
            }
        }
        else {
            printMessage(pokemon.getName() + " failed to be caught!\n");
            sleep(1);
        }
    }
    else {
        printMessage("Not even close!\n");
        sleep(1);
    }
    std::cout.flush();
}

void boostStat(const BattleItem &itemToUse, Pokemon &pokemonToBoost, int amountToBoost, bool &limitReached) {
    if (itemToUse.getStat() == "attack") {
        if (pokemonToBoost.getAttack() < 6)
            pokemonToBoost.setAttack(pokemonToBoost.getAttack() + amountToBoost);

        else
            limitReached = true;
    }
    else if (itemToUse.getStat() == "spAttack") {
        if (pokemonToBoost.getSpAttack() < 6)
            pokemonToBoost.setSpAttack(pokemonToBoost.getSpAttack() + amountToBoost);

        else
            limitReached = true;
    }
    else if (itemToUse.getStat() == "defense") {
        if (pokemonToBoost.getDefense() < 6)
            pokemonToBoost.setDefense(pokemonToBoost.getDefense() + amountToBoost);

        else
            limitReached = true;
    }
    else if (itemToUse.getStat() == "spDefense") {
        if (pokemonToBoost.getSpDefense() < 6)
            pokemonToBoost.setSpDefense(pokemonToBoost.getSpDefense() + amountToBoost);

        else
            limitReached = true;
    }
    else if (itemToUse.getStat() == "speed") {
        if (pokemonToBoost.getSpeed() < 6)
            pokemonToBoost.setSpeed(pokemonToBoost.getSpeed() + amountToBoost);

        else
            limitReached = true;
    }
    else if (itemToUse.getStat() == "accuracy") {
        if (pokemonToBoost.getAccuracy() < 6)
            pokemonToBoost.setAccuracy(pokemonToBoost.getAccuracy() + amountToBoost);

        else
            limitReached = true;
    }
}

void boostMessage(const Pokemon &pokemon, const std::string &statBoosted, int amountBoosted, bool limit) {
    if (not limit) {
        printMessage(pokemon.getName() + "'s " + statBoosted + " rose");
        if (amountBoosted == 2)
            printMessage(" sharply");

        else if (amountBoosted > 2)
            printMessage(" drastically");

        printMessage("!\n");
    }
    else
        printMessage(pokemon.getName() + "'s " + statBoosted + " can't go any higher!\n");

    sleep(2);
}

template <typename I>
void useItem(I &itemToUse) {
    itemToUse.setQuantity(itemToUse.getQuantity() - 1);
}

void useItemMessage(const std::string &itemUsed) {
    if (itemUsed.substr(itemUsed.length() - 4) != "Ball") {
        printMessage("You used a");

        if (isVowel(itemUsed[0]))
            printMessage('n');

        printMessage(' ' + itemUsed + "! ");
    }
    else {
        printMessage("You threw a");

        if (isVowel(itemUsed[0]))
            printMessage('n');

        printMessage(' ' + itemUsed + "! ");
    }
    sleep(1);
}

template <typename I>
void itemErrorMessage(const I &item) {
    printMessage("You don't have any " + item.getName() + "'s.\n");
    sleep(1);
}

template <typename I>
void noEffectMessage(const I &item, const Pokemon &pokemon) {
    printMessage(item.getName() + " had no effect on " + pokemon.getName() + ".\n");
    sleep(1);
}