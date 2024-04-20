//
// Created by Miles Youngblood on 12/7/2023.
//

#pragma once

template<typename Derived>
class Singleton {
protected:
    Singleton() = default;

public:
    Singleton(const Singleton &) = default;

    Singleton(Singleton &&) noexcept = default;

    Singleton &operator=(const Singleton &) = default;

    Singleton &operator=(Singleton &&) noexcept = default;

    virtual ~Singleton() = default;

    static Derived &getInstance() {
        static Derived instance;
        return instance;
    }
};
