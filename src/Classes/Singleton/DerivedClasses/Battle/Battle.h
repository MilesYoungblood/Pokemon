//
// Created by Miles on 10/1/2023.
//

#pragma once

#include "../../../Entity/DerivedClasses/Item/DerivedClasses/Items.h"
#include "../../../Entity/DerivedClasses/Character/DerivedClasses/Trainer/DerivedClasses/Player/Player.h"
#include "../../../../Functions/ItemFunctions.h"
#include "../../Singleton.h"

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
