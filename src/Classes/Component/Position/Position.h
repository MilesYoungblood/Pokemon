//
// Created by Miles Youngblood on 4/14/2024.
//

#pragma once

#include "../../../Enums/Direction/Direction.h"

namespace Project {
    class Position {
    public:
        Position() = default;

        Position(int x, int y);

        Position(const Position &) = default;

        Position(Position &&) noexcept = default;

        Position &operator=(const Position &) = default;

        Position &operator=(Position &&) noexcept = default;

        ~Position() = default;

        /// \brief Sets the new position
        /// \param newX new x-position
        /// \param newY new y-position
        void setPosition(int newX, int newY);

        /// \brief Translates the x-position
        /// \param t amount
        void translateX(int t);

        /// \brief Translates the y-position
        /// \param t amount
        void translateY(int t);

        /// \brief Translates the position a certain direction
        /// \param d direction
        /// \param t amount
        void translate(Direction d, int t);

        /// \brief Getter for x-position
        /// \return the x-position
        [[nodiscard]] int getX() const;

        /// \brief Getter for y-position
        /// \return the y-position
        [[nodiscard]] int getY() const;

        /// \brief Checker for position
        /// \param xPos x-position
        /// \param yPos y-position
        /// \return true if the position matches the given position
        [[nodiscard]] bool isHere(int xPos, int yPos) const;

    private:
        int x;
        int y;
    };
}
