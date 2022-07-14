//
// Created by Miles Youngblood on 7/5/2022.
//

#pragma once

#include <windows.h>

bool isVowel(char character) {
    return (character == 'A' or character == 'a' or character == 'E' or character == 'e' or
           character == 'I' or character == 'i' or character == 'O' or character == 'o' or
           character == 'U' or character == 'u') and std::isalpha(character);
}

char getChar() {
    char userChar;
    std::cin >> userChar;

    while (userChar != 'f' and userChar != 'b' and userChar != 'r' and userChar != 'p') {
        std::cin >> userChar;
    }

    return userChar;
}

int getInt(int lower, int upper) {
    int userInt;
    std::cin >> userInt;

    while (userInt < lower or upper < userInt) {
        std::cin >> userInt;
    }

    return userInt;
}

int generateInteger(int lower, int upper) {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(lower, upper);

    return dist(mt);
}

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