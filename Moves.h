//
// Created by miles on 5/5/2022.
//

#ifndef POKEMON_BATTLE_MOVES_H
#define POKEMON_BATTLE_MOVES_H

#include <string>

class Moves {
private:
    int pp, maxPp, power;
    std::string type, name;
public:
    Moves();
    Moves(const std::string& name, const std::string& type, int pp, int power);
    Moves(const Moves& moveToCopy);

    void SetPP(int newPp);
    int GetPP() const;

    int GetMaxPP() const;

    int GetPower() const;

    __attribute__((unused)) void SetType(std::string& newType);
    __attribute__((unused)) std::string GetType() const;

    std::string GetName() const;
};

#endif //POKEMON_BATTLE_MOVES_H
