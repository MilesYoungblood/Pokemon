//
// Created by Miles Youngblood on 12/7/2023.
//

#pragma once

template<typename Derived>
class Singleton {
protected:
    Singleton() = default;

public:
    Singleton(const Singleton &toCopy) = delete;

    Singleton(Singleton &&toMove) noexcept = delete;

    Singleton &operator=(const Singleton &rhs) = delete;

    Singleton &operator=(Singleton &&rhs) noexcept = delete;

    virtual ~Singleton() = default;

    inline static Derived &getInstance() {
        static Derived instance;
        return instance;
    }
};
