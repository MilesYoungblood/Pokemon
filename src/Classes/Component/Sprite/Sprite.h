//
// Created by Miles Youngblood on 4/14/2024.
//

#pragma once

namespace Project {
    class Sprite {
    private:
        int currentRow;
        int currentCol;

    public:
        struct Sheet {
            SDL_Texture *sprite{ nullptr };
            Uint32 numRows{ 0 };
            Uint32 numCols{ 0 };
        };

        [[nodiscard]] int getCurrentRow() const;

        [[nodiscard]] int getCurrentCol() const;

        void update(int numRows, int numCols);
    };
}
