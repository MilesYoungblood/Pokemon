//
// Created by miles on 5/25/2022.
//

#pragma once

#include "../Character/Pokemon/Pokemon.h"

class Item : public Entity {
public:
    Item(const char *id, int n);

    Item(const char *id, int n, int x, int y);

    Item(const Item &) = default;

    Item(Item &&) noexcept = default;

    Item &operator=(const Item &) = default;

    Item &operator=(Item &&) noexcept = default;

    ~Item() override = default;

    [[nodiscard]] int getQuantity() const;

    void add(int n);

    void use();

    [[nodiscard]] virtual std::string useMessage() const;

    [[nodiscard]] std::string noEffectMessage(const Pokemon &pokemon) const;

    [[nodiscard]] virtual std::string getEffect() const;

    [[nodiscard]] virtual std::size_t getClass() const = 0;

    [[nodiscard]] std::string getSpriteKey() const override;

    void interact() override;

    void update() override;

    void render(SDL_Texture *sprite) const override;

    [[nodiscard]] bool canUse() const;

private:
    int quantity;
};

inline std::mutex itemMutex;
inline std::unordered_map<std::string, std::unique_ptr<Item> (*)(int)> itemMap;
