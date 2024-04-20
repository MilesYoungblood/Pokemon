//
// Created by Miles Youngblood on 4/14/2024.
//

#pragma once

namespace Component {
    class Sprite {
    public:
        struct Sheet {
            SDL_Texture *sprite{ nullptr };
            Uint32 numRows{ 0 };
            Uint32 numCols{ 0 };
        };

        Sprite() = default;

        [[nodiscard]] int getCurrentRow() const;

        [[nodiscard]] int getCurrentCol() const;

        void update(int numRows, int numCols);

    private:
        int currentRow;
        int currentCol;
    };
}
