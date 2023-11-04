//
// Created by Miles Youngblood on 10/24/2023.
//

#pragma once

class DragonPulse : public Move {
private:
    const static int MAX_PP = 16;

public:
    DragonPulse() : Move(10) {}

    explicit DragonPulse(const int currentPP) : DragonPulse() {
        if (currentPP < 0) {
            this->fillToMax();
        }
        else {
            this->setPP(currentPP);
        }
    }

    [[nodiscard]] int getPower() const override {
        return 90;
    }

    [[nodiscard]] Type getType() const override {
        return Type::DRAGON;
    }

    [[nodiscard]] Category getCategory() const override {
        return Category::SPECIAL;
    }

    [[nodiscard]] MoveID getID() const override {
        return MoveID::DRAGON_PULSE;
    }

    [[nodiscard]] std::string getName() const override {
        return "Dragon Pulse";
    }

    [[nodiscard]] const char *getDescription() const override {
        return "The target is attacked with a shock wave generated by the user’s gaping mouth.";
    }
};
