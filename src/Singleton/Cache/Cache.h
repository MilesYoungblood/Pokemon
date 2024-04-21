//
// Created by miles on 4/21/2024.
//

#pragma once

template<typename Derived>
class Cache {
public:
    Cache(const Cache &) = default;

    Cache(Cache &&) noexcept = default;

    Cache &operator=(const Cache &) = default;

    Cache &operator=(Cache &&) noexcept = default;

    virtual ~Cache() {
        if (instanceCounter != 0) {
            std::clog << "Not all caches cleared\n";
        }
    }

    template<typename ...Args>
    static Derived *getInstance(Args ...args) {
        load(args...);
        return instance;
    }

    template<typename ...Args>
    static void load(Args ...args) {
        if (instance == nullptr) {
            instance = new Derived(args...);
            ++instanceCounter;
        }
    }

    static void clear() {
        if (instance != nullptr) {
            --instanceCounter;
            delete instance;
            instance = nullptr;
        }
    }

protected:
    template<typename T>
    using set = std::unordered_map<std::string, T>;

    Cache() = default;

private:
    inline static Derived *instance = nullptr;
    inline static int instanceCounter = 0;
};
