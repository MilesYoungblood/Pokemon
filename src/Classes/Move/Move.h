//
// Created by miles on 5/5/2022.
//

#pragma once

#include "../../Functions/GeneralFunctions.h"

enum class Type : Uint8 {
    NONE, NORMAL, FIRE, WATER, ELECTRIC, GRASS,
    ICE, FIGHTING, POISON, GROUND, FLYING,
    PSYCHIC, BUG, ROCK, GHOST, DRAGON,
    DARK, STEEL
};

inline SDL_Color typeToColor(Type type) {
    switch (type) {
        case Type::NONE:
            return Constants::Color::WHITE;
        case Type::NORMAL:
            return Constants::Color::LIGHT_GRAY;
        case Type::FIRE:
            return Constants::Color::RED;
        case Type::WATER:
            return Constants::Color::BLUE;
        case Type::ELECTRIC:
            return Constants::Color::YELLOW;
        case Type::GRASS:
            return Constants::Color::GREEN;
        case Type::ICE:
            return Constants::Color::CYAN;
        case Type::FIGHTING:
            return Constants::Color::BROWN;
        case Type::POISON:
            return Constants::Color::PURPLE;
        case Type::GROUND:
            return Constants::Color::BRONZE;
        case Type::FLYING:
            return Constants::Color::SKY_BLUE;
        case Type::PSYCHIC:
            return Constants::Color::HOT_PINK;
        case Type::BUG:
            return Constants::Color::YELLOW_GREEN;
        case Type::ROCK:
            return Constants::Color::SAND;
        case Type::GHOST:
            return Constants::Color::INDIGO;
        case Type::DRAGON:
            return Constants::Color::ROYAL_BLUE;
        case Type::DARK:
            return Constants::Color::DARK_BROWN;
        case Type::STEEL:
            return Constants::Color::PLATINUM;
        default:
            throw std::runtime_error("Unexpected error: function typeToColor\n");
    }
}

class Pokemon;

class Move {
public:
    enum class Id : Uint8 {
        AIR_SLASH,
        AURA_SPHERE,
        DARK_PULSE,
        DRAGON_PULSE,
        EXTRASENSORY,
        FLAMETHROWER,
        FLASH_CANNON,
        FOCUS_BLAST,
        ICE_BEAM,
        IRON_TAIL,
        QUICK_ATTACK,
        SOLAR_BEAM,
        THUNDER,
        VOLT_TACKLE
    };

    enum class Category : Uint8 {
        PHYSICAL, SPECIAL, STATUS
    };

    explicit Move(int pp);

    Move(int pp, int maxPp);

    Move(const Move &) = delete;

    Move(Move &&) noexcept = delete;

    Move &operator=(const Move &) = delete;

    Move &operator=(Move &&rhs) noexcept = delete;

    virtual ~Move() = default;

    void setPp(int amount);

    void setMaxPp(int amount);

    void restore(int amount);

    void use();

    [[nodiscard]] int getPp() const;

    [[nodiscard]] int getMaxPp() const;

    void fillToMax();

    [[nodiscard]] virtual int getDamage() const;

    virtual void action(Pokemon &attacker, Pokemon &defender, bool &skip);

    [[nodiscard]] virtual std::queue<std::string> actionMessage(const Pokemon &attacker, const Pokemon &defender, bool skip) const;

    [[nodiscard]] virtual std::string getName() const = 0;

    [[nodiscard]] virtual const char *getDescription() const = 0;

    [[nodiscard]] virtual int getPower() const = 0;

    [[nodiscard]] virtual int getAccuracy() const;

    [[nodiscard]] virtual double getCritRatio() const;

    [[nodiscard]] virtual Type getType() const = 0;

    [[nodiscard]] virtual Move::Category getCategory() const = 0;

    [[nodiscard]] virtual Move::Id getId() const = 0;

    [[nodiscard]] virtual bool isPriority() const;

    explicit operator bool() const;

protected:
    void resetFlags();

    [[nodiscard]] int getDamageFlag() const;

    [[nodiscard]] double getEffFlag() const;

    [[nodiscard]] double getCritFlag() const;

    void calculateDamage(const Pokemon &attacker, const Pokemon &defender);

private:
    [[nodiscard]] double checkType(const Pokemon &pokemon) const;

    int pp;
    int maxPp;

    int damageFlag{ 0 };
    double effFlag{ 0.0 };
    double critFlag{ 0.0 };
};

inline std::mutex moveMutex;
inline std::unordered_map<Move::Id, std::unique_ptr<Move>(*)()> moveMap;
