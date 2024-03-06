//
// Created by Miles Youngblood on 12/3/2023.
//

#pragma once

class Pokemon;

// TODO currently unused code; ignore it
class A {
public:
    A() = delete;

    A(const A &) = delete;

    A(A &&) noexcept = delete;

    A &operator=(const A &) = delete;

    A &operator=(A &&) noexcept = delete;

    ~A() = delete;

    enum class Id : Uint8 {
        ADAPTABILITY, AFTERMATH, AIR_LOCK, ANGER_POINT, ARENA_TRAP,
        BATTLE_ARMOR, BIG_PECKS, BLAZE, CHLOROPHYLL, CLEAR_BODY,
        CLOUD_NINE, COLOR_CHANGE, COMPOUND_EYES, CONTRARY, CUTE_CHARM,
        DAMP, DOWNLOAD, DRIZZLE, DROUGHT, DRY_SKIN,
        EARLY_BIRD, EFFECT_SPORE, FILTER, FLAME_BODY, FLASH_FIRE,
        FORECAST, FOREWARN, FRIEND_GUARD, FRISK, GLUTTONY,
        GUTS, HARVEST, HEALER, HEATPROOF, HEAVY_METAL,
        HONEY_GATHER, HUGE_POWER, HUSTLE, HYDRATION, HYPER_CUTTER,
        ICE_BODY, ILLUMINATE, IMMUNITY, INNER_FOCUS, INSOMNIA,
        INTIMIDATE, IRON_BARBS, IRON_FIST, JUSTIFIED, KEEN_EYE,
        KLUTZ, LEAF_GUARD, LEVITATE, LIGHT_METAL, LIGHTNING_ROD,
        LIMBER, LIQUID_OOZE, MAGIC_BOUNCE, MAGIC_GUARD, MAGMA_ARMOR,
        MAGNET_PULL, MARVEL_SCALE, MINUS, MOLD_BREAKER, MOODY,
        MOTOR_DRIVE, MOXIE, MULTI_SCALE, MULTI_TYPE, MUMMY,
        NATURAL_CURE, NO_GUARD, NORMALIZE, OBLIVIOUS, OVERGROW,
        OWN_TEMPO, PICKUP, PLUS, POISON_HEAL, POISON_POINT,
        POISON_TOUCH, PRANKSTER, PRESSURE, PURE_POWER, QUICK_FEET,
        RAIN_DISH, RECKLESS, REGENERATOR, RIVALRY, ROCK_HEAD,
        ROUGH_SKIN, RUN_AWAY, SAND_FORCE, SAND_RUSH, SAND_STREAM,
        SAND_VEIL, SAP_SIPPER, SCRAPPY, SERENE_GRACE, SHADOW_TAG,
        SHED_SKIN, SHEER_FORCE, SHELL_ARMOR, SHIELD_DUST, SIMPLE,
        SKILL_LINK, SLOW_START, SNIPER, SNOW_CLOAK, SNOW_WARNING,
        SOLAR_POWER, SOLID_ROCK, SOUNDPROOF, SPEED_BOOST, STATIC,
        STEADFAST, STENCH, STICKY_HOLD, STORM_DRAIN, STURDY,
        SUCTION_CUPS, SUPER_LUCK, SWARM, SWIFT_SWIM, SYNCHRONIZE,
        TANGLED_FEET, TECHNICIAN, TELEPATHY, TERAVOLT, THICK_FAT,
        TINTED_LENS, TORRENT, TOXIC_BOOST, TRACE, TRUANT,
        TURBOBLAZE, UNAWARE, UNBURDEN, UNNERVE, VICTORY_STAR,
        VITAL_SPIRIT, VOLT_ABSORB, WATER_ABSORB, WATER_VEIL, WEAK_ARMOR,
        WHITE_SMOKE, WONDER_GUARD, WONDER_SKIN
    };

    static void activate(A::Id id, Pokemon &attacker, Pokemon &defender) {
        A::actions[static_cast<std::size_t>(id)](attacker, defender);
    }

    static void getMessages(A::Id id, const Pokemon &attacker, const Pokemon &defender) {
        A::messageFunctions[static_cast<std::size_t>(id)](attacker, defender);
    }

    static void addActionFunction(A::Id id, void (*f)(Pokemon &, Pokemon &)) {
        A::actions[static_cast<std::size_t>(id)] = f;
    }

    static void incCounter() {
        ++A::count;
    }

    static bool isInit() {
        return A::count == A::NUM_ABILITIES;
    }

    static void addMessageFunction(A::Id id, std::vector<std::string> (*f)(const Pokemon &, const Pokemon &)) {
        A::messageFunctions[static_cast<std::size_t>(id)] = f;
    }

private:
    static const int NUM_ABILITIES{ 148 };

    inline static int count{ 0 };

    inline static std::array<void (*)(Pokemon &, Pokemon &), NUM_ABILITIES> actions;
    inline static std::array<std::vector<std::string> (*)(const Pokemon &, const Pokemon &), NUM_ABILITIES> messageFunctions;
};

struct Ability {
    enum class Id : Uint8 {
        ADAPTABILITY, AFTERMATH, AIR_LOCK, ANGER_POINT, ARENA_TRAP,
        BATTLE_ARMOR, BIG_PECKS, BLAZE, CHLOROPHYLL, CLEAR_BODY,
        CLOUD_NINE, COLOR_CHANGE, COMPOUND_EYES, CONTRARY, CUTE_CHARM,
        DAMP, DOWNLOAD, DRIZZLE, DROUGHT, DRY_SKIN,
        EARLY_BIRD, EFFECT_SPORE, FILTER, FLAME_BODY, FLASH_FIRE,
        FORECAST, FOREWARN, FRIEND_GUARD, FRISK, GLUTTONY,
        GUTS, HARVEST, HEALER, HEATPROOF, HEAVY_METAL,
        HONEY_GATHER, HUGE_POWER, HUSTLE, HYDRATION, HYPER_CUTTER,
        ICE_BODY, ILLUMINATE, IMMUNITY, INNER_FOCUS, INSOMNIA,
        INTIMIDATE, IRON_BARBS, IRON_FIST, JUSTIFIED, KEEN_EYE,
        KLUTZ, LEAF_GUARD, LEVITATE, LIGHT_METAL, LIGHTNING_ROD,
        LIMBER, LIQUID_OOZE, MAGIC_BOUNCE, MAGIC_GUARD, MAGMA_ARMOR,
        MAGNET_PULL, MARVEL_SCALE, MINUS, MOLD_BREAKER, MOODY,
        MOTOR_DRIVE, MOXIE, MULTI_SCALE, MULTI_TYPE, MUMMY,
        NATURAL_CURE, NO_GUARD, NORMALIZE, OBLIVIOUS, OVERGROW,
        OWN_TEMPO, PICKUP, PLUS, POISON_HEAL, POISON_POINT,
        POISON_TOUCH, PRANKSTER, PRESSURE, PURE_POWER, QUICK_FEET,
        RAIN_DISH, RECKLESS, REGENERATOR, RIVALRY, ROCK_HEAD,
        ROUGH_SKIN, RUN_AWAY, SAND_FORCE, SAND_RUSH, SAND_STREAM,
        SAND_VEIL, SAP_SIPPER, SCRAPPY, SERENE_GRACE, SHADOW_TAG,
        SHED_SKIN, SHEER_FORCE, SHELL_ARMOR, SHIELD_DUST, SIMPLE,
        SKILL_LINK, SLOW_START, SNIPER, SNOW_CLOAK, SNOW_WARNING,
        SOLAR_POWER, SOLID_ROCK, SOUNDPROOF, SPEED_BOOST, STATIC,
        STEADFAST, STENCH, STICKY_HOLD, STORM_DRAIN, STURDY,
        SUCTION_CUPS, SUPER_LUCK, SWARM, SWIFT_SWIM, SYNCHRONIZE,
        TANGLED_FEET, TECHNICIAN, TELEPATHY, TERAVOLT, THICK_FAT,
        TINTED_LENS, TORRENT, TOXIC_BOOST, TRACE, TRUANT,
        TURBOBLAZE, UNAWARE, UNBURDEN, UNNERVE, VICTORY_STAR,
        VITAL_SPIRIT, VOLT_ABSORB, WATER_ABSORB, WATER_VEIL, WEAK_ARMOR,
        WHITE_SMOKE, WONDER_GUARD, WONDER_SKIN
    };

    Ability() = default;

    Ability(const Ability &) = delete;

    Ability(Ability &&) noexcept = default;

    Ability &operator=(const Ability &) = delete;

    Ability &operator=(Ability &&) noexcept = delete;

    virtual ~Ability() = default;

    virtual void action(Pokemon &attacker, Pokemon &defender) = 0;

    [[nodiscard]] virtual std::queue<std::string> actionMessage(const Pokemon &attacker, const Pokemon &defender) const;

    [[nodiscard]] virtual int getFlag() const = 0;

    [[nodiscard]] virtual Ability::Id getId() const = 0;

    [[nodiscard]] virtual bool isBattle() const;
};

inline std::mutex abilityMutex;
inline std::unordered_map<Ability::Id, std::unique_ptr<Ability>(*)()> abilityMap;
