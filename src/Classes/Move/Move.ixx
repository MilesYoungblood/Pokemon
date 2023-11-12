//
// Created by Miles Youngblood on 11/12/2023.
//

export module Move;

import <string>;

import GeneralFunctions;

enum class Type {
    NONE, NORMAL, FIRE, WATER, ELECTRIC, GRASS,
    ICE, FIGHTING, POISON, GROUND, FLYING,
    PSYCHIC, BUG, ROCK, GHOST, DRAGON,
    DARK, STEEL, FAIRY
};

class P;

export class M {
private:
    int pp;
    int maxPp;

public:
    enum Id {
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
        VOLT_TACKLE,
        WATER_SHURIKEN
    };

    enum class Category {
        PHYSICAL, SPECIAL, STATUS
    };

    explicit M(int pp) : pp(pp), maxPp(pp) {}

    M(const M &) = delete;

    M(M &&) = delete;

    M &operator=(const M &) = delete;

    M &operator=(M &&) = delete;

    virtual ~M() = default;

    [[nodiscard]] virtual int getDamage() const {
        return generateInteger(1, 100) <= this->getAccuracy() ? this->getPower() : -1;

    }

    virtual void action(P &attackingPokemon, P &defendingPokemon, int damage, bool &skip) {}

    virtual void actionMessage(const P &attackingPokemon, const P &defendingPokemon, int damage, bool skipTurn, bool criticalHit, double typeEff) {}

    void use() {
        this->pp = std::max(this->pp - 1, 0);
    }

    void setPP(int newPP) {
        this->pp = newPP;

        // PP cannot be set lower than 0
        if (this->pp < 0) {
            this->pp = 0;
        }
            // PP cannot be set higher than max PP
        else if (this->pp > this->maxPp) {
            this->pp = this->maxPp;
        }
    }

    void fillToMax() {
        this->pp = this->maxPp;
    }

    [[nodiscard]] int getPP() const {
        return this->pp;
    }

    [[nodiscard]] int getMaxPP() const {
        return this->maxPp;
    }

    [[nodiscard]] virtual int getPower() const = 0;

    [[nodiscard]] virtual int getAccuracy() const {
        return 100;
    }

    [[nodiscard]] virtual Type getType() const = 0;

    [[nodiscard]] virtual M::Category getCategory() const = 0;

    [[nodiscard]] virtual M::Id getId() const = 0;

    [[nodiscard]] virtual std::string getName() const = 0;

    [[nodiscard]] virtual const char *getDescription() const = 0;

    [[nodiscard]] virtual bool isPriority() const {
        return false;
    }

    explicit operator bool() const {
        return this->pp > 0;
    }
};
