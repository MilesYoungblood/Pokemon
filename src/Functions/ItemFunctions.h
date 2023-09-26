//
// Created by Miles Youngblood on 6/7/2022.
//

#pragma once

void failMessage() {
    printMessage("But it failed!\n");
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}

void displayBag(int arrow, bool &print) {
    if (print) {
        printMessage("Choose an option:\n");
    }
    else {
        std::cout << "Choose an option:\n";
    }
    arrow == 0 ? std::cout << "   ->   HP/PP restore\n" : std::cout << "\tHP/PP restore\n";
    arrow == 1 ? std::cout << "   ->   Status restore\n" : std::cout << "\tStatus restore\n";
    arrow == 2 ? std::cout << "   ->   Poke Balls\n" : std::cout << "\tPoke Balls\n";
    arrow == 3 ? std::cout << "   ->   Battle Items\n" : std::cout << "\tBattle Items\n";
    arrow == 4 ? std::cout << "\n   ->   Cancel\n" : std::cout << "\n\tCancel\n";
    std::cout.flush();

    print = false;
}

template <typename Item>
void displayItems(const std::vector<Item> &items, int arrow, bool &print) {
    if (print) {
        printMessage("Choose an item:\n");
    }
    else {
        std::cout << "Choose an item:\n";
    }
    for (int i = 0; i < items.size(); ++i)
        if (arrow == i) {
            std::cout << "   ->   " << items[i].getName() << std::string(15 - items[i].getName().length(), ' ') << " x"
                      << items[i].getQuantity() << '\n';
        }
        else {
            std::cout << '\t' << items[i].getName() << std::string(15 - items[i].getName().length(), ' ') << " x"
                      << items[i].getQuantity() << '\n';
        }

    arrow == items.size() ? std::cout << "\n   ->   Cancel\n" : std::cout << "\n\tCancel\n";
    std::cout.flush();

    print = false;
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
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
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
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    }
}

void cure(Pokemon& pokemon, const StatusItem& item) {
    if (pokemon.getStatus() == item.getRestoreType())
        pokemon.setStatus("No status");
}

void cureMessage(const Pokemon& pokemonCured, const std::string& status) {
    if (pokemonCured.getStatus() == "No status") {
        printMessage(pokemonCured.getName() + " recovered from " + status + "!\n");
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
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
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        if (attempts[1]) {
            printMessage("2...");
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            if (attempts[2]) {
                printMessage("3...");
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                if (attempts[3]) {
                    printMessage("Gotcha! " + pokemon.getName() + " was caught!\n");
                    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                }
                else {
                    printMessage("Almost had it!\n");
                    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                }
            }
            else {
                printMessage("No! " + pokemon.getName() + " escaped!\n");
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            }
        }
        else {
            printMessage(pokemon.getName() + " failed to be caught!\n");
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }
    }
    else {
        printMessage("Not even close!\n");
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
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

    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
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
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}

void itemErrorMessage(const Item * item) {
    printMessage("You don't have any " + item->getName() + "'s.\n");
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}

void noEffectMessage(const Item * item, const Pokemon &pokemon) {
    printMessage(item->getName() + " had no effect on " + pokemon.getName() + ".\n");
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}