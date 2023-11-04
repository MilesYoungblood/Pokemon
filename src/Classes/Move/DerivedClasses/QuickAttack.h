//
// Created by Miles Youngblood on 10/24/2023.
//

#pragma once

class QuickAttack : public Move {
private:
    const static int MAX_PP = 48;

public:
    QuickAttack() : Move(30) {}

    explicit QuickAttack(const int currentPP) : QuickAttack() {
        if (currentPP < 0) {
            this->fillToMax();
        }
        else {
            this->setPP(currentPP);
        }
    }

    [[nodiscard]] int getPower() const override {
        return 40;
    }

    [[nodiscard]] Type getType() const override {
        return Type::NORMAL;
    }

    [[nodiscard]] Category getCategory() const override {
        return Category::PHYSICAL;
    }

    [[nodiscard]] MoveID getID() const override {
        return MoveID::QUICK_ATTACK;
    }

    [[nodiscard]] std::string getName() const override {
        return "Quick Attack";
    }

    [[nodiscard]] const char *getDescription() const override {
        return "The user lunges at the target at a speed that makes it almost invisible. It is sure to strike first.";
    }

    [[nodiscard]] bool isPriority() const override {
        return true;
    }
};
