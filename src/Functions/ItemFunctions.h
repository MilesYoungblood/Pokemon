//
// Created by Miles Youngblood on 6/7/2022.
//

#pragma once

#include "../Classes/Entity/DerivedClasses/Trainer/Trainer.h"

inline void failMessage() {
    std::cout << "But it failed!\n";
}

inline void displayBag(int arrow, bool &print) {
    std::cout << "Choose an option:\n";

    arrow == 0 ? std::cout << "   ->   HP/PP restore\n" : std::cout << "\tHP/PP restore\n";
    arrow == 1 ? std::cout << "   ->   StatusCondition restore\n" : std::cout << "\tStatusCondition restore\n";
    arrow == 2 ? std::cout << "   ->   Poke Balls\n" : std::cout << "\tPoke Balls\n";
    arrow == 3 ? std::cout << "   ->   Battle Items\n" : std::cout << "\tBattle Items\n";
    arrow == 4 ? std::cout << "\n   ->   Cancel\n" : std::cout << "\n\tCancel\n";
    std::cout.flush();

    print = false;
}

template<typename I>
inline void displayItems(Trainer *trainer, int arrow, bool &print) {
    std::cout << "Choose an item:\n";

    const int starting = 10 * (arrow / 10);
    const int num_items = trainer->getNumItems<I>();

    int remaining = 10;
    if (arrow >= 10 * (num_items / 10)) {
        remaining = num_items % 10;
    }

    for (int i = starting; i < starting + remaining; ++i) {
        const I *item = &trainer->getItem<I>(i);
        arrow == i ? std::cout << "   ->   " : std::cout << '\t';
        std::cout << item << std::string(15 - item->getName().length(), ' ') << " x" << item->getQuantity() << '\n';
    }

    arrow == num_items ? std::cout << "\n   ->   Cancel\n" : std::cout << "\n\tCancel\n";
    std::cout.flush();

    print = false;
}

inline void catchPokemonMessage(const Pokemon &pokemon, std::array<bool, 4> attempts) {
    if (attempts[0]) {
        std::cout << "1...";
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        if (attempts[1]) {
            std::cout << "2...";
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            if (attempts[2]) {
                std::cout << "3...";
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                if (attempts[3]) {
                    std::cout << "Gotcha! " + pokemon.getName() + " was caught!\n";
                    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                }
                else {
                    std::cout << "Almost had it!\n";
                    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                }
            }
            else {
                std::cout << "No! " + pokemon.getName() + " escaped!\n";
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            }
        }
        else {
            std::cout << pokemon.getName() + " failed to be caught!\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }
    }
    else {
        std::cout << "Not even close!\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
    std::cout.flush();
}

inline void noEffectMessage(const Item &item, const Pokemon &pokemon) {
    std::cout << item.getName() + " had no effect on " + pokemon.getName() + ".\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}
