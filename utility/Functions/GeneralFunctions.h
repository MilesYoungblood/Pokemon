//
// Created by Miles Youngblood on 7/5/2022.
//

#pragma once

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

/*
template<typename I>
void displayItems(Trainer *trainer, int arrow, bool &print) {
    std::cout << "Choose an item:\n";

    const int starting = 10 * (arrow / 10);
    const int num_items = trainer->getNumItems<I>();

    int remaining = 10;
    if (arrow >= 10 * (num_items / 10)) {
        remaining = num_items % 10;
    }

    for (int i = starting; i < starting + remaining; ++i) {
        const I *item = &trainer->getItem<I>(i);
        arrow == i ? std::cout << "   ->   " : std::cout << '\t';
        std::cout << item << std::string(15 - item->getName().length(), ' ') << " x" << item->getQuantity() << '\n';
    }

    arrow == num_items ? std::cout << "\n   ->   Cancel\n" : std::cout << "\n\tCancel\n";
    std::cout.flush();

    print = false;
}
*/
