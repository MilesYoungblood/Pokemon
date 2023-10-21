//
// Created by miles on 5/25/2022.
//

#pragma once

#include <iostream>

#include "../../Classes/Pokemon/Pokemon.h"

enum ItemID {
    POTION,
    SUPER_POTION,
    HYPER_POTION,
    ETHER,

    ANTIDOTE,
    AWAKENING,
    BURN_HEAL,
    ICE_HEAL,
    PARALYZE_HEAL,

    POKE_BALL,
    GREAT_BALL,
    ULTRA_BALL,
    MASTER_BALL,

    X_ATTACK,
    X_DEFENSE,
    X_SP_ATTACK,
    X_SP_DEFENSE,
    X_SPEED,
    X_ACCURACY
};

enum class RestoreType { NONE, HP, PP };
enum class Stat { NONE, ATTACK, DEFENSE, SP_ATTACK, SP_DEFENSE, SPEED, ACCURACY };

class Item {
private:
    const char *name{"N/A"};
    int quantity{0};

public:
    Item() = default;
    Item(const char *name, int n);
    Item(const Item &) = delete;
    auto operator=(const Item &) -> Item& = delete;
    Item(const Item &&) = delete;
    auto operator=(const Item &&) -> Item& = delete;
    virtual ~Item() = default;

    void setQuantity(int newQuantity);
    [[nodiscard]] auto getQuantity() const -> int;

    void use();
    virtual void useMessage();

    [[nodiscard]] virtual auto getAmount() const -> int;
    [[nodiscard]] virtual auto getRestoreType() const -> RestoreType;
    [[nodiscard]] virtual auto getStatus() const -> Status;
    [[nodiscard]] virtual auto getStat() const -> Stat;

    virtual void restore(Pokemon &pokemon) = 0;
    virtual void restore(Move &move) = 0;
    virtual void restoreMessage(const Pokemon &pokemon) = 0;
    virtual void restoreMessage(const Move &move) = 0;
    virtual auto catchPokemon(const Pokemon &pokemon, std::array<bool, 4> &attempts) -> bool = 0;

    [[nodiscard]] auto getName() const -> std::string;

    explicit operator bool() const;

    friend auto operator<<(std::ostream &out, const Item &rhs) -> std::ostream&;
};
