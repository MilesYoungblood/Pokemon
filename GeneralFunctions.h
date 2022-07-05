//
// Created by Miles Youngblood on 7/5/2022.
//

#pragma once

bool isVowel(char character) {
    return (character == 'A' or character == 'a' or character == 'E' or character == 'e' or
           character == 'I' or character == 'i' or character == 'O' or character == 'o' or
           character == 'U' or character == 'u') and std::isalpha(character);
}

int generateInteger(int lower, int upper) {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(lower, upper);

    return dist(mt);
}