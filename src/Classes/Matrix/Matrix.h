//
// Created by Miles Youngblood on 4/14/2024.
//

#pragma once

template<typename T>
class Matrix {
public:
    Matrix() = default;

    explicit Matrix(const std::size_t m, const std::size_t n) {
        this->data = std::vector(m, std::vector<T>(n));
    }

    [[nodiscard]] std::size_t getM() const {
        return this->data.size();
    }

    [[nodiscard]] std::size_t getN() const {
        return this->data[0].size();
    }

    T &operator()(const std::size_t i, const std::size_t j) {
        return this->data[i][j];
    }

    [[nodiscard]] T operator()(const std::size_t i, const std::size_t j) const {
        return this->data[i][j];
    }

    typename std::vector<std::vector<T>>::iterator begin() {
        return this->data.begin();
    }

    [[nodiscard]] typename std::vector<std::vector<T>>::const_iterator begin() const {
        return this->data.cbegin();
    }

    typename std::vector<std::vector<T>>::iterator end() {
        return this->data.end();
    }

    [[nodiscard]] typename std::vector<std::vector<T>>::const_iterator end() const {
        return this->data.cend();
    }

private:
    std::vector<std::vector<T>> data;
};
