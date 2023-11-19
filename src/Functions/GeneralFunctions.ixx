//
// Created by Miles Youngblood on 11/12/2023.
//

export module GeneralFunctions;

// returns a random integer from a range
export int generateInteger(int from, int to) {
    if (from > to) {
        std::swap(from, to);
    }
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(from, to);

    return dist(mt);
}