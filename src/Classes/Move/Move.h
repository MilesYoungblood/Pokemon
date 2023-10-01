//
// Created by miles on 5/5/2022.
//

#pragma once

#include <iostream>
#include <random>
#include <thread>

enum Type {
    NORMAL, FIRE, WATER, ELECTRIC, GRASS,
    ICE, FIGHTING, POISON, GROUND, FLYING,
    PSYCHIC, BUG, ROCK, GHOST, DRAGON,
    DARK, STEEL, FAIRY
};

enum categories { PHYSICAL, SPECIAL, STATUS };

class Pokemon;

class Move {
protected:
    int pp;
    int maxPp;
    int power;
    int accuracy;

    std::string type;
    std::string category;
    std::string name;

    // returns a random integer from a range
    static int generateInteger(int from, int to) {
        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_int_distribution<int> dist(from, to);

        return dist(mt);
    }

    // prints out a string and sleeps in between prints
    static void printMessage(const std::string &message) {
        for (char ltr : message) {
            std::cout << ltr;
            std::this_thread::sleep_for(std::chrono::milliseconds(25));
        }
    }

    // prints out a string and sleeps in between prints
    static void printMessage(const std::string &message, int interval) {
        for (char ltr : message) {
            std::cout << ltr;
            std::this_thread::sleep_for(std::chrono::milliseconds(interval));
        }
    }

    // prints out a character then sleeps
    static void printMessage(char message) {
        std::cout << message;
        std::this_thread::sleep_for(std::chrono::milliseconds(25));
    }

    // prints out a character then sleeps
    static void printMessage(char message, int interval) {
        std::cout << message;
        std::this_thread::sleep_for(std::chrono::milliseconds(interval));
    }

public:
    Move();
    Move(const char * name, const char * type, const char * category, int pp, int power, int accuracy);
    Move(const Move &moveToCopy);
    Move& operator=(const Move& rhs);

    virtual int getDamage();

    virtual void action(Pokemon &attackingPokemon, Pokemon &defendingPokemon, int damage);
    virtual void actionMessage(Pokemon &attackingPokemon, Pokemon &defendingPokemon, int damage, bool criticalHit, double typeEff);

    void setPP(int newPP);
    int getPP() const;

    int getMaxPP() const;

    int getPower() const;

    int getAccuracy() const;

    std::string getType() const;

    std::string getCategory() const;

    std::string getName() const;

    bool canUse() const;

    friend std::ostream& operator<<(std::ostream &out, const Move &rhs);
};