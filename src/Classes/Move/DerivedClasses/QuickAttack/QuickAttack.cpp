//
// Created by Miles Youngblood on 12/4/2023.
//

#include "QuickAttack.h"

QuickAttack::QuickAttack() : Move(30) {}

std::string QuickAttack::getName() const {
    return "Quick Attack";
}

const char *QuickAttack::getDescription() const {
    return "The user lunges at the target at a speed that makes it almost invisible. It is sure to strike first.";
}

int QuickAttack::getPower() const {
    return 40;
}

Type QuickAttack::getType() const {
    return Type::NORMAL;
}

Move::Category QuickAttack::getCategory() const {
    return Move::Category::PHYSICAL;
}

Move::Id QuickAttack::getId() const {
    return Move::Id::QUICK_ATTACK;
}
