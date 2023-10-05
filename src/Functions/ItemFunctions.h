//
// Created by Miles Youngblood on 6/7/2022.
//

#pragma once

#include "../Classes/Trainer/Trainer.h"

inline void failMessage() {
    printMessage("But it failed!\n");
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}

inline void displayBag(int arrow, bool &print) {
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

inline void displayItems(const Trainer *trainer, int iType, int arrow, bool &print) {
    if (print) {
        printMessage("Choose an item:\n");
    }
    else {
        std::cout << "Choose an item:\n";
    }

    const int starting = 10 * (arrow / 10);
    const int numItems = trainer->getNumItems(iType);

    int remaining = 10;
    if (arrow >= 10 * (numItems / 10)) {
        remaining = numItems % 10;
    }

    for (int i = starting; i < starting + remaining; ++i) {
        const Item *item = &trainer->getItem(iType, i);
        if (arrow == i) {
            std::cout << "   ->   " << *item << std::string(15 - item->getName().length(), ' ') << " x" << item->getQuantity() << '\n';
        }
        else {
            std::cout << '\t' << *item << std::string(15 - item->getName().length(), ' ') << " x" << item->getQuantity() << '\n';
        }
    }

    arrow == numItems ? std::cout << "\n   ->   Cancel\n" : std::cout << "\n\tCancel\n";
    std::cout.flush();

    print = false;
}

inline bool catchPokemon(bool attempts[]) {
    // FIXME catch function does not take into account levels or catch rates
    attempts[0] = generateInteger(1, 100) < 80;
    attempts[1] = generateInteger(1, 100) < 70;
    attempts[2] = generateInteger(1, 100) < 60;
    attempts[3] = generateInteger(1, 100) < 50;

    return attempts[0] and attempts[1] and attempts[2] and attempts[3];
}

inline void catchPokemonMessage(const Pokemon &pokemon, const bool attempts[]) {
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

inline void boostStat(const Item *itemToUse, Pokemon &pokemonToBoost, int amountToBoost, bool &limitReached) {
    if (itemToUse->getStat() == Stat::ATTACK) {
        if (pokemonToBoost.getAttack() < 6)
            pokemonToBoost.setAttack(pokemonToBoost.getAttack() + amountToBoost);

        else
            limitReached = true;
    }
    else if (itemToUse->getStat() == Stat::SP_ATTACK) {
        if (pokemonToBoost.getSpAttack() < 6)
            pokemonToBoost.setSpAttack(pokemonToBoost.getSpAttack() + amountToBoost);

        else
            limitReached = true;
    }
    else if (itemToUse->getStat() == Stat::DEFENSE) {
        if (pokemonToBoost.getDefense() < 6)
            pokemonToBoost.setDefense(pokemonToBoost.getDefense() + amountToBoost);

        else
            limitReached = true;
    }
    else if (itemToUse->getStat() == Stat::SP_DEFENSE) {
        if (pokemonToBoost.getSpDefense() < 6)
            pokemonToBoost.setSpDefense(pokemonToBoost.getSpDefense() + amountToBoost);

        else
            limitReached = true;
    }
    else if (itemToUse->getStat() == Stat::SPEED) {
        if (pokemonToBoost.getSpeed() < 6)
            pokemonToBoost.setSpeed(pokemonToBoost.getSpeed() + amountToBoost);

        else
            limitReached = true;
    }
    else if (itemToUse->getStat() == Stat::ACCURACY) {
        if (pokemonToBoost.getAccuracy() < 6)
            pokemonToBoost.setAccuracy(pokemonToBoost.getAccuracy() + amountToBoost);

        else
            limitReached = true;
    }
}

inline void boostMessage(const Pokemon &pokemon, Stat statBoosted, int amountBoosted, bool limit) {
    const char * string;

    switch (statBoosted) {
        case Stat::ATTACK:
            string = "attack";
            break;

        case Stat::SP_ATTACK:
            string = "special attack";
            break;

        case Stat::DEFENSE:
            string = "defense";
            break;

        case Stat::SP_DEFENSE:
            string = "special defense";
            break;

        case Stat::SPEED:
            string = "speed";
            break;

        case Stat::ACCURACY:
            string = "accuracy";
            break;

        default:
            throw std::runtime_error("Unexpected error: function boostMessage");
    }

    if (not limit) {
        printMessage(pokemon.getName() + "'s " + string + " rose");
        if (amountBoosted == 2)
            printMessage(" sharply");

        else if (amountBoosted > 2)
            printMessage(" drastically");

        printMessage("!\n");
    }
    else
        printMessage(pokemon.getName() + "'s " + string + " can't go any higher!\n");

    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
}

inline void itemErrorMessage(const Item &item) {
    printMessage("You don't have any " + item.getName() + "'s.\n");
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}

inline void noEffectMessage(const Item &item, const Pokemon &pokemon) {
    printMessage(item.getName() + " had no effect on " + pokemon.getName() + ".\n");
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}
