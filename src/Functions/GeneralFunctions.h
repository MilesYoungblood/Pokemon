//
// Created by Miles Youngblood on 7/5/2022.
//

#pragma once

class [[maybe_unused]] Sort {
public:
    Sort() = delete;

    template<typename Comparable, std::size_t Size>
    static void mergeSort(std::array<Comparable, Size> &array) {
        Sort::mergeSort(array, 0ULL, array.size());
    }

    template<typename Comparable>
    static void mergeSort(std::vector<Comparable> &vector) {
        Sort::mergeSort(vector, 0ULL, vector.size());
    }

private:
    template<typename Comparable, std::size_t Size>
    static void merge(std::array<Comparable, Size> &array, const size_t left, const size_t mid, const size_t right) {
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

    template<typename Comparable>
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
    template<typename Comparable, std::size_t Size>
    static void mergeSort(std::array<Comparable, Size> &array, const size_t left, const size_t right) {
        if (left < right) {
            const size_t mid = left + (right - left) / 2;
            mergeSort(array, left, mid);
            mergeSort(array, mid + 1, right);
            merge(array, left, mid, right);
        }
    }

    // begin is for left index and the end is right index
    // of the sub-array of arr to be sorted
    template<typename Comparable>
    static void mergeSort(std::vector<Comparable> &vector, const size_t left, const size_t right) {
        if (left < right) {
            const size_t mid = left + (right - left) / 2;
            mergeSort(vector, left, mid);
            mergeSort(vector, mid + 1, right);
            merge(vector, left, mid, right);
        }
    }
};

inline const char *getCategoryAsString(const int category) {
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

// returns true if character is a vowel
inline bool isVowel(const char ltr) {
    return tolower(ltr) == 'a' or tolower(ltr) == 'e' or
           tolower(ltr) == 'i' or tolower(ltr) == 'o' or tolower(ltr) == 'u';
}

inline bool binomial(const double prob = 50.0) {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::binomial_distribution dist(1, prob / 100.0);

    return dist(mt) == 1;
}

// returns a random integer from a range
inline int generateInteger(int a, int b) {
    if (a > b) {
        std::swap(a, b);
    }
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution dist(a, b);

    return dist(mt);
}

template<typename G>
concept EnumType = std::is_enum_v<G>;

template<EnumType G>
std::string operator+(const std::string &lhs, G &rhs) {
    using underlyingType = std::underlying_type_t<G>;
    return lhs + std::to_string(static_cast<underlyingType>(rhs));
}

template<EnumType G>
std::string operator+=(std::string &lhs, G &rhs) {
    using underlyingType = std::underlying_type_t<G>;
    lhs += std::to_string(static_cast<underlyingType>(rhs));
    return lhs;
}

template<EnumType G>
std::ostream &operator<<(std::ostream &ostream, G rhs) {
    using underlyingType = std::underlying_type_t<G>;
    ostream << static_cast<underlyingType>(rhs);
    return ostream;
}

template<EnumType G>
std::istream &operator>>(std::istream &istream, G &rhs) {
    std::string buffer;
    istream >> buffer;

    using underlyingType = std::underlying_type_t<G>;
    rhs = static_cast<underlyingType>(std::stoi(buffer));
    return istream;
}

template<typename G>
concept IntType = std::is_integral_v<G> and not std::is_same_v<G, char>;

template<IntType G>
std::string operator+(const std::string &lhs, G &&rhs) {
    return lhs + std::to_string(std::forward<G>(rhs));
}

template<IntType G>
std::string operator+=(std::string &lhs, G &&rhs) {
    lhs += std::to_string(std::forward<G>(rhs));
    return lhs;
}

template<IntType G>
std::string operator+(const std::string &lhs, G &rhs) {
    return lhs + std::to_string(rhs);
}

template<IntType G>
std::string operator+=(std::string &lhs, G &rhs) {
    lhs += std::to_string(rhs);
    return lhs;
}
