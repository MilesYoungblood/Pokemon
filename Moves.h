//
// Created by miles on 5/5/2022.
//

#ifndef POKEMON_BATTLE_MOVES_H
#define POKEMON_BATTLE_MOVES_H

#include <string>

using namespace std;

class Moves {
private:
    int pp;
    int damage;
    string type, name;
public:
    Moves();
    Moves(const string& nameToSet, const string& typeToSet, int ppToSet, int damageToSet);

    void SetPP(int val);
    int GetPP() const;

    void SetDamage(int val);
    int GetDamage() const;

    __attribute__((unused)) void SetType(string& type);
    __attribute__((unused)) string GetType() const;

    void SetName(const string& newName);
    std::string GetName() const;
};

#endif //POKEMON_BATTLE_MOVES_H
