//
// Created by Miles Youngblood on 6/7/2022.
//

#pragma once

#include <random>
#include <iostream>
#include <unistd.h>

#include "../../Classes/Pokemon/Pokemon.h"

// FIXME fix overridden function
struct WaterShuriken : public Move {
    WaterShuriken() : Move("Water Shuriken", "water", "special", 20, 15, 100) {}
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

struct DarkPulse : public Move {
    DarkPulse() : Move("Dark Pulse", "dark", "special", 15, 80, 100) {}
};

struct IceBeam : public Move {
    IceBeam() : Move("Ice Beam", "ice", "special", 10, 90, 100) {}
};

struct Extrasensory : public Move {
    Extrasensory() : Move("Extrasensory", "psychic", "special", 15, 90, 100) {}
};

struct Flamethrower : public Move {
    Flamethrower() : Move("Flamethrower", "fire", "special", 15, 90, 100) {}
};

struct AirSlash : public Move {
    AirSlash() : Move("Air Slash", "flying", "special", 15, 75, 95) {}
};

struct DragonPulse : public Move {
    DragonPulse() : Move("Dragon Pulse", "dragon", "special", 10, 85, 100) {}
};

struct SolarBeam : public Move {
    SolarBeam() : Move("Solar Beam", "grass", "special", 10, 120, 100) {}
};

struct FocusBlast : public Move {
    FocusBlast() : Move("Focus Blast", "fighting", "special", 5, 120, 70) {}
};

struct AuraSphere : public Move {
    AuraSphere() : Move("Aura Sphere", "fighting", "special", 20, 80, 100) {}
};

struct FlashCannon : public Move {
    FlashCannon() : Move("Flash Cannon", "steel", "special", 10, 80, 100) {}
};

struct Thunder : public Move {
    Thunder() : Move("Thunder", "electric", "special", 10, 110, 70) {}
};

struct QuickAttack : public Move {
    QuickAttack() : Move("Quick Attack", "normal", "physical", 30, 40, 100) {}
};

struct IronTail : public Move {
    IronTail() : Move("Iron Tail", "steel", "physical", 15, 100, 75) {}
};

struct VoltTackle : public Move {
    VoltTackle() : Move("Volt Tackle", "electric", "physical", 15, 120, 100) {}
};