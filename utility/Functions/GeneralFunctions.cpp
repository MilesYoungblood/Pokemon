//
// Created by miles on 4/15/2024.
//

#include "GeneralFunctions.h"

bool isVowel(const char ltr)  {
    return tolower(ltr) == 'a' or tolower(ltr) == 'e' or
           tolower(ltr) == 'i' or tolower(ltr) == 'o' or tolower(ltr) == 'u';
}

bool binomial(const double prob) {
    static std::random_device rd;
    static std::mt19937 mt(rd());
    std::binomial_distribution dist(1, prob / 100.0);

    return dist(mt) == 1;
}

int generateInteger(int a, int b) {
    if (a > b) {
        std::swap(a, b);
    }
    static std::random_device rd;
    static std::mt19937 mt(rd());
    std::uniform_int_distribution dist(a, b);

    return dist(mt);
}
