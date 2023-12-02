//
// Created by Miles on 18/05/2023.
//

#pragma once

#include "../../Item.h"

class BattleItem : public Item {
public:
    enum class Id {
        X_ATTACK,
        X_DEFENSE,
        X_SP_ATTACK,
        X_SP_DEFENSE,
        X_SPEED,
        X_ACCURACY
    };

    struct Data {
        std::string_view name;
        const Pokemon::Stat stat;
    };

    BattleItem(BattleItem::Id id, int quantity);

    static void init(BattleItem::Data (*instructions)(BattleItem::Id));

    [[nodiscard]] std::string getName() const override;

    [[nodiscard]] Pokemon::Stat getStat() const;

    [[nodiscard]] BattleItem::Id getId() const;

    [[nodiscard]] Item::Class getClass() const override;

private:
    BattleItem::Id id;

    inline static BattleItem::Data (*dataFunction)(BattleItem::Id){ nullptr };
};
