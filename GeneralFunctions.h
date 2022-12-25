//
// Created by Miles Youngblood on 7/5/2022.
//

#pragma once

#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

// returns true if character is a vowel
bool isVowel(char ltr) {
    return tolower(ltr) == 'a' or tolower(ltr) == 'e' or tolower(ltr) == 'i' or tolower(ltr) == 'o' or tolower(ltr) == 'u';
}

// return true if all of a string is a number
bool isNumber(const std::string &str) {
    return std::all_of(str.begin(), str.end(), [](char ltr){ return std::isdigit(ltr); });
}

// returns a char of the users selections
char getChar(const std::vector<std::string> &options) {
    while (true) {
        std::string userChar;
        getline(std::cin, userChar, '\n');

        for (const std::string &ltr : options) {
            if (userChar == ltr) {
                return userChar[0];
            }
        }
    }
}

// returns an integer from a range of a user's choice
int getInt(int lower, int upper) {
    while (true) {
        std::string userInt;
        getline(std::cin, userInt, '\n');

        if (isNumber(userInt) and lower <= std::stoi(userInt) and std::stoi(userInt) <= upper) {
            return std::stoi(userInt);
        }
    }
}

// returns a random integer from a range
int generateInteger(int lower, int upper) {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(lower, upper);

    return dist(mt);
}

/*
void clearScreen() {
    char fill = ' ';
    COORD t1 = {0,0};
    CONSOLE_SCREEN_BUFFER_INFO s;
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(console, &s);
    DWORD written, cells = s.dwSize.X * s.dwSize.Y;
    FillConsoleOutputCharacter(console, fill, cells, t1, &written);
    FillConsoleOutputAttribute(console, s.wAttributes, cells, t1, &written);
    SetConsoleCursorPosition(console, t1);
}
*/