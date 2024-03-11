//
// Created by Miles on 18/05/2023.
//

#include "PokeBall.h"

PokeBall::PokeBall(int n) : Item(n) {}

PokeBall::PokeBall(int n, int x, int y) : Item(n, x, y) {}

std::string PokeBall::getName() const {
    return "Poke Ball";
}

std::string PokeBall::getEffect() const {
    return "A device for catching wild Pokemon. It is thrown like a ball at the target. It is designed as a capsule system.";
}

double PokeBall::getCatchRate(const Pokemon & /*pokemon*/, Time  /*time*/, int  /*turn*/, bool  /*isCave*/) const {
    return 1.0;
}

void PokeBall::postCatch(Pokemon &pokemon) const {}

Item::Class PokeBall::getClass() const {
    return Item::Class::POKE_BALL;
}

std::string PokeBall::useMessage() const {
    std::string message("You threw a");

    if (isVowel(this->getName()[0])) {
        message += 'n';
    }

    return message.append(' ' + this->getName() + '!');
}

bool PokeBall::catchPokemon(const Pokemon &pokemon, std::array<bool, 4> &attempts) const {
    // using gen III-IV catch mechanics

    double a = 3 * pokemon.getMaxHp() - 2 * pokemon.getHp();
    a /= 3.0 * pokemon.getMaxHp();
    a *= pokemon.getCatchRate();
    //FIXME shift
    a *= this->getCatchRate(pokemon, Time::NIGHT, 1, false);

    auto statusCalc = [&pokemon] {
        switch (pokemon.getStatus()) {
            case StatusCondition::SLEEP:
                return 2.0;

            case StatusCondition::PARALYSIS:
            case StatusCondition::POISON:
            case StatusCondition::BURN:
                return 1.5;

            default:
                return 1.0;
        }
    };

    a *= statusCalc();
    // Pokémon is automatically caught if a >= 255
    if (a >= 255.0) {
        return true;
    }

    const double b = 1048560.0 / sqrt(sqrt(16711680.0 / a));
    for (int i = 0; i < 4; ++i) {
        attempts.at(i) = generateInteger(0, 65535) < b;
    }

    return attempts[0] and attempts[1] and attempts[2] and attempts[3];
}

namespace {
    std::jthread init([] -> void {
        const std::scoped_lock<std::mutex> scoped_lock(pokeBallMutex);
        pokeBalls["Poke Ball"] = [](int n) -> std::unique_ptr<PokeBall> { return std::make_unique<PokeBall>(n); };
    });
}
