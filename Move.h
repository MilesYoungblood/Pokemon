//
// Created by miles on 5/5/2022.
//

#pragma once

#include <iostream>
#include <random>

class Move {
protected:
    int pp;
    int maxPp;
    int power;
    int accuracy;

    std::string type;
    std::string category;
    std::string name;

public:
    Move();
    Move(const std::string& name, const std::string& type, const std::string& category, int pp, int power, int accuracy);
    Move(const Move &moveToCopy);

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

    friend std::ostream& operator<<(std::ostream &out, const Move &rhs);
};