//
// Created by Miles Youngblood on 7/5/2022.
//

#pragma once

class [[maybe_unused]] Sorter {
public:
    Sorter() = delete;

    Sorter(const Sorter &) = delete;

    Sorter(Sorter &&) noexcept = delete;

    Sorter &operator=(const Sorter &) = delete;

    Sorter &operator=(Sorter &&) noexcept = delete;

    ~Sorter() = delete;

    template<typename Comparable, std::size_t Size>
    static void mergeSort(std::array<Comparable, Size> &array) {
        mergeSort(array, 0, array.size());
    }

    template<typename Comparable>
    static void mergeSort(std::vector<Comparable> &vector) {
        mergeSort(vector, 0, vector.size());
    }

private:
    template<typename Comparable, std::size_t Size>
    static void merge(std::array<Comparable, Size> &array, const std::size_t left, const std::size_t mid, const std::size_t right) {
        const std::size_t subArrayOne = mid - left + 1;
        const std::size_t subArrayTwo = right - mid;

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

        std::size_t indexOfSubArrayOne = 0;
        std::size_t indexOfSubArrayTwo = 0;
        std::size_t indexOfMergedArray = left;

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
    static void merge(std::vector<Comparable> &array, const std::size_t left, const std::size_t mid, const std::size_t right) {
        const std::size_t subArrayOne = mid - left + 1;
        const std::size_t subArrayTwo = right - mid;

        // Create temp arrays
        std::vector<Comparable> leftArray(subArrayOne);
        std::vector<Comparable> rightArray(subArrayTwo);

        // Copy data to temp arrays leftArray[] and rightArray[]
        for (std::size_t i = 0; i < subArrayOne; ++i) {
            leftArray[i] = array[left + i];
        }
        for (std::size_t i = 0; i < subArrayTwo; ++i) {
            rightArray[i] = array[mid + i + 1];
        }

        std::size_t indexOfSubArrayOne = 0;
        std::size_t indexOfSubArrayTwo = 0;
        std::size_t indexOfMergedArray = left;

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
    static void mergeSort(std::array<Comparable, Size> &array, const std::size_t left, const std::size_t right) {
        if (left < right) {
            const std::size_t mid = left + (right - left) / 2;
            mergeSort(array, left, mid);
            mergeSort(array, mid + 1, right);
            merge(array, left, mid, right);
        }
    }

    // begin is for left index and the end is right index
    // of the sub-array of arr to be sorted
    template<typename Comparable>
    static void mergeSort(std::vector<Comparable> &vector, const std::size_t left, const std::size_t right) {
        if (left < right) {
            const std::size_t mid = left + (right - left) / 2;
            mergeSort(vector, left, mid);
            mergeSort(vector, mid + 1, right);
            merge(vector, left, mid, right);
        }
    }
};

const char *getCategoryAsString(int category);

// returns true if character is a vowel
bool isVowel(char ltr);

bool binomial(double prob = 50.0);

// returns a random integer from a range
int generateInteger(int a, int b);

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
