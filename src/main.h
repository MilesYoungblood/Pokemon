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

enum keys {
    ESC = 27,
    UP_ARROW __attribute__((unused)) = 72,
    LEFT_ARROW __attribute__((unused)) = 75,
    DOWN_ARROW __attribute__((unused)) = 80,
    RIGHT_ARROW __attribute__((unused)) = 77,
    ENTER = 13
};

// toggles cursor
void ShowConsoleCursor(bool showFlag) {
    CONSOLE_CURSOR_INFO cursorInfo;

    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
    cursorInfo.bVisible = showFlag; // set the cursor visibility
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

class SortClass {
private:
    template <typename Comparable>
    static void merge(std::vector<Comparable> &array, const size_t left, const size_t mid, const size_t right) {
        const size_t subArrayOne = mid - left + 1;
        const size_t subArrayTwo = right - mid;

        // Create temp arrays
        Comparable leftArray[subArrayOne];
        Comparable rightArray[subArrayTwo];

        // Copy data to temp arrays leftArray[] and rightArray[]
        for (int i = 0; i < subArrayOne; ++i)
            leftArray[i] = array[left + i];
        for (int i = 0; i < subArrayTwo; ++i)
            rightArray[i] = array[mid + i + 1];

        size_t indexOfSubArrayOne = 0;
        size_t indexOfSubArrayTwo = 0;
        size_t indexOfMergedArray = left;

        // Merge the temp arrays back into array[left..right]
        while (indexOfSubArrayOne < subArrayOne and indexOfSubArrayTwo < subArrayTwo) {
            if (leftArray[indexOfSubArrayOne]<= rightArray[indexOfSubArrayTwo]) {
                array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
                ++indexOfSubArrayOne;
            }
            else {
                array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
                ++indexOfSubArrayTwo;
            }
            ++indexOfMergedArray;
        }

        // Copy the remaining elements of
        // left[], if there are any
        while (indexOfSubArrayOne < subArrayOne) {
            array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
            ++indexOfSubArrayOne;
            ++indexOfMergedArray;
        }

        // Copy the remaining elements of
        // right[], if there are any
        while (indexOfSubArrayTwo < subArrayTwo) {
            array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
            ++indexOfSubArrayTwo;
            ++indexOfMergedArray;
        }
    }

    // begin is for left index and end is right index
    // of the sub-array of arr to be sorted
    template <typename Comparable>
    static void mergeSort(std::vector<Comparable> &array, const size_t left, const size_t right) {
        if (left < right) {
            size_t mid = left + (right - left) / 2;
            mergeSort(array, left, mid);
            mergeSort(array, mid + 1, right);
            merge(array, left, mid, right);
        }
    }

public:
    template<typename Comparable>
    static void mergeSort(std::vector<Comparable> &array) {
        mergeSort(array, 0, array.size());
    }
};

// returns true if character is a vowel
bool isVowel(char ltr) {
    return tolower(ltr) == 'a' xor tolower(ltr) == 'e' xor tolower(ltr) == 'i' xor tolower(ltr) == 'o' xor tolower(ltr) == 'u';
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

bool coinFlip() {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(0, 1);

    return dist(mt) == 1;
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