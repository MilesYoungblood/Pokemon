//
// Created by miles on 5/5/2022.
//

#pragma once

#include <string>
#include <random>

class Move {
protected:
    int pp, maxPp, power, accuracy;
    std::string type, category, name;

public:
    Move();
    Move(const std::string &, const std::string &, const std::string &, int, int, int);
    Move(const Move &);

    virtual int getDamage();
    int getDamage() const;

    void setPP(int);
    int getPP() const;

    int getMaxPP() const;

    int getPower() const;

    int getAccuracy() const;

    std::string getType() const;

    std::string getCategory() const;

    std::string getName() const;

    friend std::ostream& operator<<(std::ostream &, const Move &);
};