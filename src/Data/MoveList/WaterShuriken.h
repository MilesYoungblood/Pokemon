//
// Created by Miles Youngblood on 6/14/2023.
//

#pragma once

struct WaterShuriken : public Move {
    WaterShuriken() : Move("Water Shuriken", "water", "special", 20, 15, 100) {}
    int numHits = 0; // number of hits landed (from 2 to 5)

    int getDamage() override {
        //FIXME calculate critical hits here instead of in calculateDamage()
        for (int i = 0; i < Move::generateInteger(2, 5); ++i) { // determines hits and misses
            if (Move::generateInteger(1, 100) <= this->accuracy) {
                ++this->numHits;
            }
        }

        return this->power * this->numHits;
    }

    void actionMessage(Pokemon &attackingPokemon, Pokemon &defendingPokemon, int damage, bool criticalHit, float typeEff) override {
        Move::printMessage(attackingPokemon.getName() + " used Water Shuriken! ");
        sleep(1);
        // damage will be negative if the attack misses
        if (damage > 0) {
            Move::printMessage("Water Shuriken did " + std::to_string(damage) + " damage! ");
            sleep(1);
            if (typeEff >= 2.0f) {
                Move::printMessage("It's super effective! ");
                sleep(1);
            }
            else if (typeEff <= 0.5f) {
                Move::printMessage("It's not very effective... ");
                sleep(1);
            }

            Move::printMessage("It hit " + std::to_string(this->numHits) + " times! ");
            sleep(1);
            if (criticalHit) {
                Move::printMessage('x' + std::to_string(this->numHits) + " critical hits!");
                sleep(1);
            }
        }
        else {
            Move::printMessage(defendingPokemon.getName() + " avoided the attack!");
            sleep(1);
        }

        Move::printMessage('\n', 0);
        this->numHits = 0;
    }
};