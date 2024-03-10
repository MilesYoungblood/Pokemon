//
// Created by Miles Youngblood on 12/3/2023.
//

#include "../../../Entity/DerivedClasses/Character/DerivedClasses/Pokemon/Pokemon.h"
#include "AuraSphere.h"

AuraSphere::AuraSphere() : Move(20) {}

void AuraSphere::action(Pokemon &attacker, Pokemon &defender, bool & /*skip*/) {
    this->resetFlags();

    this->calculateDamage(attacker, defender);
    // if the calculation registers as a miss, force it as a hit
    defender.takeDamage(std::max(this->getDamageFlag(), this->getDamageFlag() * -1));
    this->use();
}

std::string AuraSphere::getName() const {
    return "Aura Sphere";
}

std::string AuraSphere::getDescription() const {
    return "The user looses a blast of aura power from deep within its body at the target. This move is certain to hit.";
}

int AuraSphere::getPower(const Pokemon & /*attacker*/, const Pokemon & /*defender*/) const {
    return 90;
}

Type AuraSphere::getType() const {
    return Type::FIGHTING;
}

Move::Category AuraSphere::getCategory() const {
    return Move::Category::SPECIAL;
}

namespace {
    std::jthread init([] -> void {
        const std::scoped_lock<std::mutex> scoped_lock(moveMutex);
        moveMap["Aura Sphere"] = [] -> std::unique_ptr<Move> { return std::make_unique<AuraSphere>(); };
    });
}
