//
// Created by miles on 5/5/2022.
//

#pragma once

#include "../Enums/Type/Type.h"
#include "../Component/Resource/Resource.h"

class Pokemon;

class Move {
public:
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

    Component::Resource &getPp();

    [[nodiscard]] Component::Resource getPp() const;

    virtual void action(Pokemon &attacker, Pokemon &defender, bool &skip);

    [[nodiscard]] virtual std::vector<std::string> actionMessage(const Pokemon &attacker, const Pokemon &defender,
                                                                  bool skip) const;

    [[nodiscard]] virtual std::string getName() const = 0;

    [[nodiscard]] virtual std::string getDescription() const = 0;

    [[nodiscard]] virtual int getPower(const Pokemon &attacker, const Pokemon &defender) const = 0;

    [[nodiscard]] virtual int getAccuracy() const;

    [[nodiscard]] virtual double getCritRatio() const;

    [[nodiscard]] virtual Type getType() const = 0;

    [[nodiscard]] virtual Category getCategory() const = 0;

    [[nodiscard]] virtual bool isPriority() const;

    [[nodiscard]] bool canUse() const;

protected:
    void resetFlags();

    [[nodiscard]] int getDamageFlag() const;

    [[nodiscard]] double getEffFlag() const;

    [[nodiscard]] double getCritFlag() const;

    void calculateDamage(const Pokemon &attacker, const Pokemon &defender);

private:
    [[nodiscard]] double checkType(const Pokemon &pokemon) const;

    Component::Resource pp;

    int damageFlag{ 0 };
    double effFlag{ 0.0 };
    double critFlag{ 0.0 };
};

inline std::mutex moveMutex;
inline std::unordered_map<std::string, std::unique_ptr<Move>(*)()> moveMap;
