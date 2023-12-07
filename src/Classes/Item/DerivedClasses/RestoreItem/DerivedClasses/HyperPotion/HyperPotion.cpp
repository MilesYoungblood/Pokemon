//
// Created by Miles Youngblood on 12/6/2023.
//

#include "HyperPotion.h"

HyperPotion::HyperPotion(int n) : RestoreItem(n) {}

std::string HyperPotion::getName() const {
    return "Hyper Potion";
}

std::string HyperPotion::getEffect() const {
    return "A spray-type medicine for wounds. It restores the HP of one Pokemon by 200 points.";
}

int HyperPotion::getAmount() const {
    return 200;
}

bool HyperPotion::isHp() const {
    return true;
}

RestoreItem::Id HyperPotion::getId() const {
    return RestoreItem::Id::HYPER_POTION;
}

namespace {
    AutoThread init([] -> void {
        restoreItems.insert(std::make_pair(RestoreItem::Id::HYPER_POTION, [](int n) -> std::unique_ptr<RestoreItem> {
            return std::make_unique<HyperPotion>(n);
        }));
    });
}
