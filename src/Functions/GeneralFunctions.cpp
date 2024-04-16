//
// Created by miles on 4/15/2024.
//

#include "GeneralFunctions.h"

const char *getCategoryAsString(const int category) {
    switch (category) {
        case 0:
            return "physical";

        case 1:
            return "special";

        case 2:
            return "status";

        default:
            throw std::runtime_error("Unexpected error: function getCategoryAsString");
    }
}

bool isVowel(const char ltr)  {
    return tolower(ltr) == 'a' or tolower(ltr) == 'e' or
           tolower(ltr) == 'i' or tolower(ltr) == 'o' or tolower(ltr) == 'u';
}

bool binomial(const double prob) {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::binomial_distribution dist(1, prob / 100.0);

    return dist(mt) == 1;
}

int generateInteger(int a, int b) {
    if (a > b) {
        std::swap(a, b);
    }
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution dist(a, b);

    return dist(mt);
}
