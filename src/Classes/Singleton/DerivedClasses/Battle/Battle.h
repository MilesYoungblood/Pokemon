//
// Created by Miles on 10/1/2023.
//

#pragma once

#include "../../../Entity/DerivedClasses/Item/DerivedClasses/Items.h"
#include "../../../Entity/DerivedClasses/Character/DerivedClasses/Trainer/DerivedClasses/Player/Player.h"
#include "../../Singleton.h"

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

class Battle : public Singleton<Battle> {
    Player *player{ nullptr };
    Trainer *opponent{ nullptr };
    size_t turn{ 0 };

    bool isRunning{ true };

    friend class Singleton<Battle>;

    Battle() = default;

    static void forcedSwitchPrompt(int arrow, bool &print);

    static void pokemonPrompt(int arrow, bool &print);

    static void switchOutMessage(const Trainer *trainer, int pokemonSwitched);

    void switchOut(Trainer *trainer, bool isUser);

    void chooseItem(bool &skip, bool isTrainerBattle);

    void choosePokemon(bool &skip);
};
