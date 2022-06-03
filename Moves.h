//
// Created by miles on 5/5/2022.
//

#ifndef POKEMON_BATTLE_MOVES_H
#define POKEMON_BATTLE_MOVES_H

#include <string>

class Moves {
protected:
    int pp, damage;
    std::string type, name;
public:
    Moves();
    Moves(const std::string& nameToSet, const std::string& typeToSet, int ppToSet, int damageToSet);
    Moves(const Moves& moveToCopy);

    void SetPP(int val);
    int GetPP() const;

    void SetDamage(int val);
    int GetDamage() const;

    __attribute__((unused)) void SetType(std::string& type);
    __attribute__((unused)) std::string GetType() const;

    void SetName(const std::string& newName);
    std::string GetName() const;
};

#endif //POKEMON_BATTLE_MOVES_H
