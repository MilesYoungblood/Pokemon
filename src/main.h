//
// Created by Miles Youngblood on 7/5/2022.
//

#pragma once

#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <conio.h>
#include <windows.h>

// returns true if character is a vowel
bool isVowel(char ltr) {
    return tolower(ltr) == 'a' or tolower(ltr) == 'e' or tolower(ltr) == 'i' or tolower(ltr) == 'o' or tolower(ltr) == 'u';
}

// returns a char of the users selections
char getChar(const std::vector<char> &options) {
    while (true) {
        char c = static_cast<char>(getch());
        for (const char ltr : options) {
            if (c == ltr)
                return c;
        }
    }
}

// returns an integer from a range of a user's choice
int getInt(int lower, int upper) {
    while (true) {
        int i = getch() - '0';
        if (lower <= i and i <= upper)
            return i;
    }
}

// returns a random integer from a range
int generateInteger(int from, int to) {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(from, to);

    return dist(mt);
}

// prints out a string and sleeps in between prints
void printMessage(const std::string &message) {
    for (char ltr : message) {
        std::cout << ltr;
        Sleep(25);
    }
}

// prints out a character then sleeps
void printMessage(char message) {
    std::cout << message;
    Sleep(25);
}