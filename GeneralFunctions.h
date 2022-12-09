//
// Created by Miles Youngblood on 7/5/2022.
//

#pragma once

#include <algorithm>

// returns true if character is a vowel
bool isVowel(char character) {
    return (character == 'A' or character == 'a' or character == 'E' or character == 'e' or
           character == 'I' or character == 'i' or character == 'O' or character == 'o' or
           character == 'U' or character == 'u') and std::isalpha(character);
}

char getChar() {
    std::string userChar;
    getline(std::cin, userChar, '\n');

    while (userChar != "f" and userChar != "b" and userChar != "r" and userChar != "p") {
        getline(std::cin, userChar, '\n');
    }

    return userChar[0];
}

// returns an integer from a range of a user's choice
int getInt(int lower, int upper) {
    std::string userInt;
    getline(std::cin, userInt, '\n');

    while (true) {
        if (lower <= std::stoi(userInt) and std::stoi(userInt) <= upper) {
            break;
        }
    }

    return std::stoi(userInt);
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