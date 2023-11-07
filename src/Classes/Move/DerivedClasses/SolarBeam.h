//
// Created by Miles Youngblood on 10/24/2023.
//

#pragma once

//TODO solar beam action
class SolarBeam : public Move {
private:
    const static int MAX_PP = 16;

public:
    SolarBeam() : Move(10) {}

    explicit SolarBeam(const int currentPP) : SolarBeam() {
        if (currentPP < 0) {
            this->fillToMax();
        }
        else {
            this->setPP(currentPP);
        }
    }

    [[nodiscard]] int getPower() const override {
        return 120;
    };

    [[nodiscard]] Type getType() const override {
        return Type::GRASS;
    }

    [[nodiscard]] Move::Category getCategory() const override {
        return Move::Category::SPECIAL;
    }

    [[nodiscard]] Move::ID getID() const override {
        return Move::ID::SOLAR_BEAM;
    }

    [[nodiscard]] std::string getName() const override {
        return "Solar Beam";
    }

    [[nodiscard]] const char *getDescription() const override {
        return "A two-turn attack. The user gathers light, then blasts a bundled beam on the second turn.";
    }
};
