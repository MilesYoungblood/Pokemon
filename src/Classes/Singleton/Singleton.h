//
// Created by Miles Youngblood on 12/7/2023.
//

#pragma once

template<typename Derived>
class Singleton {
protected:
    Singleton() = default;

public:
    Singleton(const Singleton &toCopy) = default;

    Singleton(Singleton &&toMove) noexcept = default;

    Singleton &operator=(const Singleton &rhs) = default;

    Singleton &operator=(Singleton &&rhs) noexcept = default;

    virtual ~Singleton() = default;

    inline static Derived &getInstance() {
        static Derived instance;
        return instance;
    }
};
