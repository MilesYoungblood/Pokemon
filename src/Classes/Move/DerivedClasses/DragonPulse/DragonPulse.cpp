//
// Created by Miles Youngblood on 12/3/2023.
//

#include "DragonPulse.h"

DragonPulse::DragonPulse() : Move(10) {}

std::string DragonPulse::getName() const {
    return "Dragon Pulse";
}

const char *DragonPulse::getDescription() const {
    return "The target is attacked with a shock wave generated by the user’s gaping mouth.";
}

int DragonPulse::getPower() const {
    return 90;
}

Type DragonPulse::getType() const {
    return Type::DRAGON;
}

Move::Category DragonPulse::getCategory() const {
    return Move::Category::SPECIAL;
}

Move::Id DragonPulse::getId() const {
    return Move::Id::DRAGON_PULSE;
}

namespace {
    std::jthread init([] -> void {
        const std::lock_guard<std::mutex> lock_guard(moveMutex);
        moveMap.insert(std::make_pair(Move::Id::DRAGON_PULSE,
                                      [] -> std::unique_ptr<Move> { return std::make_unique<DragonPulse>(); }));
    });
}