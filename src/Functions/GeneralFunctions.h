//
// Created by Miles Youngblood on 7/5/2022.
//

#pragma once

#include <iostream>
#include <filesystem>
#include <vector>
#include <random>
#include <algorithm>
#include <thread>
#include <conio.h>
#include <windows.h>

enum Keys {
    ESC = 27,
    ENTER = 13
};

class [[maybe_unused]] SortClass {
private:
    template <typename Comparable>
    static void merge(std::vector<Comparable> &array, const size_t left, const size_t mid, const size_t right) {
        const size_t subArrayOne = mid - left + 1;
        const size_t subArrayTwo = right - mid;

        // Create temp arrays
        std::vector<Comparable> leftArray(subArrayOne);
        std::vector<Comparable> rightArray(subArrayTwo);

        // Copy data to temp arrays leftArray[] and rightArray[]
        for (int i = 0; i < subArrayOne; ++i) {
            leftArray[i] = array[left + i];
        }
        for (int i = 0; i < subArrayTwo; ++i) {
            rightArray[i] = array[mid + i + 1];
        }

        size_t indexOfSubArrayOne = 0;
        size_t indexOfSubArrayTwo = 0;
        size_t indexOfMergedArray = left;

        // Merge the temp arrays back into array[left.right]
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
        // the left array if there are any
        while (indexOfSubArrayOne < subArrayOne) {
            array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
            ++indexOfSubArrayOne;
            ++indexOfMergedArray;
        }

        // Copy the remaining elements of
        // right[] if there are any
        while (indexOfSubArrayTwo < subArrayTwo) {
            array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
            ++indexOfSubArrayTwo;
            ++indexOfMergedArray;
        }
    }

    // begin is for left index and the end is right index
    // of the sub-array of arr to be sorted
    template <typename Comparable>
    static void mergeSort(std::vector<Comparable> &array, const size_t left, const size_t right) {
        if (left < right) {
            const size_t mid = left + (right - left) / 2;
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
inline bool isVowel(char ltr) {
    return tolower(ltr) == 'a' or tolower(ltr) == 'e' or tolower(ltr) == 'i' or tolower(ltr) == 'o' or tolower(ltr) == 'u';
}

// returns true once the user has pressed enter and false if the user chooses up (w) or down (s)
inline bool chooseOption(int &option, const int upper) {
    while (true) {
        switch (static_cast<char>(getch())) {
            case 'w':
                if (option - 1 >= 0) {
                    --option;
                    return false;
                }
                else {
                    continue;
                }

            case 's':
                if (option + 1 <= upper) {
                    ++option;
                    return false;
                }
                else {
                    continue;
                }

            case Keys::ENTER:
                return true;

            case Keys::ESC:
                option = upper;
                return true;

            default:
                continue;
        }
    }
}

inline bool coinFlip() {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(0, 1);

    return dist(mt) == 1;
}

// returns a random integer from a range
inline int generateInteger(const int from, const int to) {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(from, to);

    return dist(mt);
}

// prints out a c-string and sleeps in between prints
inline void printMessage(const char *message, const int interval = 25) {
    bool sleep = true;
    const std::string_view str = message;

    for (const char ltr : str) {
        if (sleep and (_kbhit() != 0)) {
            if (static_cast<char>(_getch()) == Keys::ENTER) {
                sleep = false;
            }
        }
        std::cout << ltr;
        if (sleep) {
            std::this_thread::sleep_for(std::chrono::milliseconds(interval));
        }
    }
}

// prints out a string and sleeps in between prints
inline void printMessage(std::string_view message, const int interval = 25) {
    bool sleep = true;
    for (const char ltr : message) {
        if (sleep and (_kbhit() != 0)) {
            if (static_cast<char>(_getch()) == Keys::ENTER) {
                sleep = false;
            }
        }
        std::cout << ltr;
        if (sleep) {
            std::this_thread::sleep_for(std::chrono::milliseconds(interval));
        }
    }
}

// prints out a character then sleeps
inline void printMessage(const char message) {
    std::cout << message;
    std::this_thread::sleep_for(std::chrono::milliseconds(25));
}

inline void pressEnter() {
    while (true) {
        if (static_cast<char>(_getch()) == Keys::ENTER) {
            return;
        }
    }
}
