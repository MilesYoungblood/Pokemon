//
// Created by Miles Youngblood on 4/14/2024.
//

#pragma once

namespace Component {
    class Sprite {
    public:
        Sprite(int frameSpeed, int numCols, int numRows);

        Sprite(const Sprite &) = default;

        Sprite(Sprite &&) noexcept = default;

        Sprite &operator=(const Sprite &) = delete;

        Sprite &operator=(Sprite &&) noexcept = delete;

        [[nodiscard]] int getCurrentCol() const;

        void update();

    private:
        int framesElapsed{ 0 };
        int currentCol{ 0 };
        int currentRow{ 0 };

        const int frameSpeed;
        const int numCols;
        const int numRows;
    };
}
