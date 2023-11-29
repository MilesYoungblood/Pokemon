//
// Created by Miles Youngblood on 7/5/2022.
//

#pragma once

#include <conio.h>
#include <windows.h>

enum Keys {
    ESC = 27,
    ENTER = 13
};

class [[maybe_unused]] SortClass {
private:
    template <typename Comparable, std::size_t size>
    static void merge(std::array<Comparable, size> &array, const size_t left, const size_t mid, const size_t right) {
        const size_t sub_array_one = mid - left + 1;
        const size_t sub_array_two = right - mid;

        // Create temp arrays
        std::vector<Comparable> leftArray(sub_array_one);
        std::vector<Comparable> rightArray(sub_array_two);

        // Copy data to temp arrays leftArray[] and rightArray[]
        for (int i = 0; i < sub_array_one; ++i) {
            leftArray[i] = array[left + i];
        }
        for (int i = 0; i < sub_array_two; ++i) {
            rightArray[i] = array[mid + i + 1];
        }

        size_t indexOfSubArrayOne = 0;
        size_t indexOfSubArrayTwo = 0;
        size_t indexOfMergedArray = left;

        // Merge the temp arrays back into array[left.right]
        while (indexOfSubArrayOne < sub_array_one and indexOfSubArrayTwo < sub_array_two) {
            if (leftArray[indexOfSubArrayOne] <= rightArray[indexOfSubArrayTwo]) {
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
        while (indexOfSubArrayOne < sub_array_one) {
            array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
            ++indexOfSubArrayOne;
            ++indexOfMergedArray;
        }

        // Copy the remaining elements of
        // right[] if there are any
        while (indexOfSubArrayTwo < sub_array_two) {
            array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
            ++indexOfSubArrayTwo;
            ++indexOfMergedArray;
        }
    }

    template <typename Comparable>
    static void merge(std::vector<Comparable> &array, const size_t left, const size_t mid, const size_t right) {
        const size_t sub_array_one = mid - left + 1;
        const size_t sub_array_two = right - mid;

        // Create temp arrays
        std::vector<Comparable> leftArray(sub_array_one);
        std::vector<Comparable> rightArray(sub_array_two);

        // Copy data to temp arrays leftArray[] and rightArray[]
        for (int i = 0; i < sub_array_one; ++i) {
            leftArray[i] = array[left + i];
        }
        for (int i = 0; i < sub_array_two; ++i) {
            rightArray[i] = array[mid + i + 1];
        }

        size_t indexOfSubArrayOne = 0;
        size_t indexOfSubArrayTwo = 0;
        size_t indexOfMergedArray = left;

        // Merge the temp arrays back into array[left.right]
        while (indexOfSubArrayOne < sub_array_one and indexOfSubArrayTwo < sub_array_two) {
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
        while (indexOfSubArrayOne < sub_array_one) {
            array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
            ++indexOfSubArrayOne;
            ++indexOfMergedArray;
        }

        // Copy the remaining elements of
        // right[] if there are any
        while (indexOfSubArrayTwo < sub_array_two) {
            array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
            ++indexOfSubArrayTwo;
            ++indexOfMergedArray;
        }
    }

    // begin is for left index and the end is right index
    // of the sub-array of arr to be sorted
    template <typename Comparable, std::size_t size>
    static void mergeSort(std::array<Comparable, size> &array, const size_t left, const size_t right) {
        if (left < right) {
            const size_t mid = left + (right - left) / 2;
            mergeSort(array, left, mid);
            mergeSort(array, mid + 1, right);
            merge(array, left, mid, right);
        }
    }

    // begin is for left index and the end is right index
    // of the sub-array of arr to be sorted
    template <typename Comparable>
    static void mergeSort(std::vector<Comparable> &vector, const size_t left, const size_t right) {
        if (left < right) {
            const size_t mid = left + (right - left) / 2;
            mergeSort(vector, left, mid);
            mergeSort(vector, mid + 1, right);
            merge(vector, left, mid, right);
        }
    }

public:
    SortClass() = delete;

    template<typename Comparable, std::size_t size>
    static void mergeSort(std::array<Comparable, size> &array) {
        SortClass::mergeSort(array, 0ULL, array.size());
    }

    template<typename Comparable>
    static void mergeSort(std::vector<Comparable> &vector) {
        SortClass::mergeSort(vector, 0ULL, vector.size());
    }
};

inline const char *getCategoryAsString(int category) {
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

inline const char *getTypeAsString(int type) {
    switch (type) {
        case 1:
            return "normal";

        case 2:
            return "fire";

        case 3:
            return "water";

        case 4:
            return "electric";

        case 5:
            return "grass";

        case 6:
            return "ice";

        case 7:
            return "fighting";

        case 8:
            return "poison";

        case 9:
            return "ground";

        case 10:
            return "flying";

        case 11:
            return "psychic";

        case 12:
            return "bug";

        case 13:
            return "rock";

        case 14:
            return "ghost";

        case 15:
            return "dragon";

        case 16:
            return "dark";

        case 17:
            return "steel";

        case 18:
            return "fairy";

        default:
            throw std::runtime_error("Unexpected error: function getTypeAsString");
    }
}

// returns true if character is a vowel
inline bool isVowel(char ltr) {
    return tolower(ltr) == 'a' or tolower(ltr) == 'e' or
           tolower(ltr) == 'i' or tolower(ltr) == 'o' or tolower(ltr) == 'u';
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
    std::binomial_distribution<int> dist;

    return dist(mt) == 1;
}

// returns a random integer from a range
inline int generateInteger(int from, int to) {
    if (from > to) {
        std::swap(from, to);
    }
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(from, to);

    return dist(mt);
}

// prints out a c-string and sleeps in between prints
inline void printMessage(const char *message, const int interval = 25) {
    bool sleep = true;
    const std::string_view str(message);

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
