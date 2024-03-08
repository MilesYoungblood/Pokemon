//
// Created by Miles Youngblood on 12/4/2023.
//

#include "QuickAttack.h"

QuickAttack::QuickAttack() : Move(30) {}

std::string QuickAttack::getName() const {
    return "Quick Attack";
}

std::string QuickAttack::getDescription() const {
    return "The user lunges at the target at a speed that makes it almost invisible. It is sure to strike first.";
}

int QuickAttack::getPower(const Pokemon & /*attacker*/, const Pokemon & /*defender*/) const {
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

namespace {
    std::jthread init([] -> void {
        const std::scoped_lock<std::mutex> scoped_lock(moveMutex);
        moveMap.insert(std::make_pair(Move::Id::IRON_TAIL,
                                      [] -> std::unique_ptr<Move> { return std::make_unique<QuickAttack>(); }));
    });
}
