//
// Created by Miles on 18/05/2023.
//

#include "Pokeball.h"

PokeBall::PokeBall(const int quantity) : Item(quantity) {}

double PokeBall::getCatchRate(const Pokemon & /*pokemon*/, Time  /*time*/, int  /*turn*/, bool  /*isCave*/) const {
    return 1.0;
}

ItemType PokeBall::getType() const {
    return ItemType::POKE_BALL;
}

ItemID PokeBall::getID() const {
    return ItemID::POKE_BALL;
}

std::string PokeBall::getName() const {
    return "Poke Ball";
}

void PokeBall::useMessage() {
    printMessage("You threw a");

    if (isVowel(this->getName()[0])) {
        printMessage('n');
    }

    printMessage(' ' + this->getName() + "! ");
}

bool PokeBall::catchPokemon(const Pokemon &pokemon, std::array<bool, 4> &attempts) const {
    // using gen III-IV catch mechanics

    double a = 3 * pokemon.getMaxHp() - 2 * pokemon.getHP();
    a /= 3.0 * pokemon.getMaxHp();
    a *= pokemon.getCatchRate();
    //FIXME update
    a *= this->getCatchRate(pokemon, Time::NIGHT, 1, false);

    auto statusCalc = [&pokemon] {
        switch (pokemon.getStatus()) {
            case Status::SLEEP:
                return 2.0;

            case Status::PARALYSIS:
            case Status::POISON:
            case Status::BURN:
                return 1.5;

            default:
                return 1.0;
        }
    };

    a *= statusCalc();
    // Pokémon is automatically caught if a >= 255
    if (a >= 255) {
        return true;
    }

    const double b = 1048560 / sqrt(sqrt(16711680 / a));
    for (int i = 0; i < 4; ++i) {
        attempts.at(i) = generateInteger(0, 65535) < b;
    }

    return attempts[0] and attempts[1] and attempts[2] and attempts[3];
}
