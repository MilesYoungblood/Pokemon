//
// Created by miles on 5/25/2022.
//

#pragma once

#include "../../../../Enums/Time/Time.h"
#include "../Character/DerivedClasses/Pokemon/Pokemon.h"

class Item : public Entity {
private:
    inline static SDL_Texture *texture{ nullptr };
    int quantity;

public:
    enum class Class : Uint8 {
        RESTORE,
        STATUS,
        POKE_BALL,
        BATTLE
    };

    explicit Item(int n);

    Item(int n, int x, int y);

    Item(const Item &toCopy) = delete;

    Item(Item &&) noexcept = delete;

    Item &operator=(const Item &) = delete;

    Item &operator=(Item &&) noexcept = delete;

    ~Item() override = default;

    static void init();

    static void clean();

    [[nodiscard]] virtual std::string getName() const = 0;

    [[nodiscard]] virtual std::string getEffect() const = 0;

    [[nodiscard]] int getQuantity() const;

    void add(int n);

    void use();

    [[nodiscard]] virtual std::string useMessage() const;

    [[nodiscard]] std::string noEffectMessage(const Pokemon &pokemon) const;

    [[nodiscard]] virtual Item::Class getClass() const = 0;

    void interact() override;

    void update() override;

    void render() const override;

    explicit operator bool() const;
};
