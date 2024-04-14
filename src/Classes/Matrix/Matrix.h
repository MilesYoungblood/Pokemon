//
// Created by Miles Youngblood on 4/14/2024.
//

#pragma once

template<typename T>
class Matrix {
private:
    std::vector<std::vector<T>> data;

public:
    Matrix() = default;

    explicit Matrix(std::size_t m, std::size_t n) {
        this->data = std::vector<std::vector<T>>(m, std::vector<T>(n));
    }

    T &operator[](int i, int j) {
        return this->data[i][j];
    }

    [[nodiscard]] T operator[](int i, int j) const {
        return this->data[i][j];
    }

    T at(std::size_t i, std::size_t j) {
        return this->data.at(i).at(j);
    }

    std::vector<std::vector<T>>::iterator begin() {
        return this->data.begin();
    }

    [[nodiscard]] std::vector<std::vector<T>>::const_iterator begin() const {
        return this->data.cbegin();
    }

    std::vector<std::vector<T>>::iterator end() {
        return this->data.end();
    }

    [[nodiscard]] std::vector<std::vector<T>>::const_iterator end() const {
        return this->data.cend();
    }
};