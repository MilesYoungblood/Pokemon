//
// Created by Miles Youngblood on 6/14/2023.
//

#pragma once

struct WaterShuriken : public Move {
    WaterShuriken() : Move("Water Shuriken", "water", "special", 20, 15, 100) {}
    int numHits = 0; // number of hits landed (from 2 to 5)

    int getDamage() override {
        for (int i = 0; i < Move::generateInteger(2, 5); ++i) { // determines hits and misses
            if (Move::generateInteger(1, 100) <= this->accuracy) {
                ++this->numHits;
            }
        }

        return this->power * this->numHits;
    }

    void actionMessage(Pokemon &attackingPokemon, Pokemon &defendingPokemon, int damage, bool criticalHit, double typeEff) override {
        Move::printMessage(attackingPokemon.getName() + " used Water Shuriken! ");
        Sleep(1000);
        // damage will be negative if the attack misses
        if (damage > 0) {
            Move::printMessage("Water Shuriken did " + std::to_string(damage) + " damage! ");
            Sleep(1000);
            if (typeEff >= 2.0) {
                Move::printMessage("It's super effective! ");
                Sleep(1000);
            }
            else if (typeEff <= 0.5) {
                Move::printMessage("It's not very effective... ");
                Sleep(1000);
            }

            Move::printMessage("It hit " + std::to_string(this->numHits) + " times! ");
            Sleep(1000);
            if (criticalHit) {
                Move::printMessage('x' + std::to_string(this->numHits) + " critical hits!");
                Sleep(1000);
            }
        }
        else {
            Move::printMessage(defendingPokemon.getName() + " avoided the attack!");
            Sleep(1000);
        }

        Move::printMessage('\n', 0);
        this->numHits = 0;
    }
};