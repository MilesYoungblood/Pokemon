//
// Created by miles on 4/19/2024.
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
