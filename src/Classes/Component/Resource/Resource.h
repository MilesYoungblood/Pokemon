//
// Created by Miles Youngblood on 4/14/2024.
//

#pragma once

namespace Project {
    class Resource {
    public:
        Resource() = default;

        Resource(int current, int max);

        void raise(int x);

        void lower(int x);

        void increaseMax(int x);

        void fill();

        [[nodiscard]] int getCurrent() const;

        [[nodiscard]] int getMax() const;

        [[nodiscard]] bool full() const;

        [[nodiscard]] bool empty() const;

    private:
        int current;
        int max;
    };
}
