//
// Created by Miles Youngblood on 6/7/2022.
//

#pragma once

#include "Moves.h"
#include <random>
#include <iostream>
#include <unistd.h>

struct WaterShuriken : public Moves {
    WaterShuriken() : Moves("Water Shuriken", "water", "special", 20, 15, 100) {}
    int numHits = 0; // number of possible hits (from 2 to 5)
    int trueHits = 0; // number of hits landed (from 2 to 5)
    int trueDamage = 0;

    int getDamage() override {
        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_int_distribution<int> dist(2, 5);
        std::uniform_int_distribution<int> hit(1, 100);

        numHits = dist(mt);
        std::cout << numHits << std::endl;

        for (int i = 0; i < numHits; ++i) { // determines hits and misses
            if (hit(mt) <= accuracy) {
                ++trueHits;
            }
        }

        return power * trueHits;
    }

    __attribute__((unused)) void attackMessage(Pokemon& attackingPokemon, Pokemon& defendingPokemon) {
        std::cout << attackingPokemon.getName() << " used " << name << "! ";
        sleep(1);

        std::cout << "It hit " << trueHits << " times!" << std::endl;
        sleep(1);

        std::cout << name << " did " << trueDamage << " damage!" << std::endl;
        sleep(2);
    }
};

struct DarkPulse : public Moves {
    DarkPulse() : Moves("Dark Pulse", "dark", "special", 15, 80, 100) {}
};

struct IceBeam : public Moves {
    IceBeam() : Moves("Ice Beam", "ice", "special", 10, 90, 100) {}
};

struct Extrasensory : public Moves {
    Extrasensory() : Moves("Extrasensory", "psychic", "special", 15, 90, 100) {}
};

struct Flamethrower : public Moves {
    Flamethrower() : Moves("Flamethrower", "fire", "special", 15, 90, 100) {}
};

struct AirSlash : public Moves {
    AirSlash() : Moves("Air Slash", "flying", "special", 15, 75, 95) {}
};

struct DragonPulse : public Moves {
    DragonPulse() : Moves("Dragon Pulse", "dragon", "special", 10, 85, 100) {}
};

struct SolarBeam : public Moves {
    SolarBeam() : Moves("Solar Beam", "grass", "special", 10, 120, 100) {}
};

struct FocusBlast : public Moves {
    FocusBlast() : Moves("Focus Blast", "fighting", "special", 5, 120, 70) {}
};

struct AuraSphere : public Moves {
    AuraSphere() : Moves("Aura Sphere", "fighting", "special", 20, 80, 100) {}
};

struct FlashCannon : public Moves {
    FlashCannon() : Moves("Flash Cannon", "steel", "special", 10, 80, 100) {}
};

struct Thunder : public Moves {
    Thunder() : Moves("Thunder", "electric", "special", 10, 110, 70) {}
};

struct QuickAttack : public Moves {
    QuickAttack() : Moves("Quick Attack", "normal", "physical", 30, 40, 100) {}
};

struct IronTail : public Moves {
    IronTail() : Moves("Iron Tail", "steel", "physical", 15, 100, 75) {}
};

struct VoltTackle : public Moves {
    VoltTackle() : Moves("Volt Tackle", "electric", "physical", 15, 120, 100) {}
};