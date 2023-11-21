//
// Created by miles on 5/5/2022.
//

#pragma once

#include "../../Entity.h"
#include "../../../Move/Move.h"

enum class Status {
    NONE, BURN, PARALYSIS, FREEZE, POISON, SLEEP
};

/// \inherit Entity
class Pokemon : public Entity {
public:
    enum class Id {
        VICTINI,
        SNIVY,
        SERVINE,
        SERPERIOR,
        TEPIG,
        PIGNITE,
        EMBOAR,
        OSHAWOTT,
        DEWOTT,
        SAMUROTT,
        PATRAT,
        WATCHOG,
        LILLIPUP,
        HERDIER,
        STOUTLAND,
        PURRLOIN,
        LIEPARD,
        PANSAGE,
        SIMISAGE,
        PANSEAR,
        SIMISEAR,
        PANPOUR,
        SIMIPOUR,
        MUNNA,
        MUSHARNA,
        PIDOVE,
        TRANQUILL,
        UNFEZANT,
        BLITZLE,
        ZEBSTRIKA,
        ROGGENROLA,
        BOLDORE,
        GIGALITH,
        WOOBAT,
        SWOOBAT,
        DRILBUR,
        EXCADRILL,
        AUDINO,
        TIMBURR,
        GURDURR,
        CONKELDURR,
        TYMPOLE,
        PALPITOAD,
        SEISMITOAD,
        THROH,
        SAWK,
        SEWADDLE,
        SWADLOON,
        LEAVANNY,
        VENIPEDE,
        WHIRLIPEDE,
        SCOLIPEDE,
        COTTONEE,
        WHIMSICOTT,
        PETILIL,
        LILLIGANT,
        BASCULIN,
        SANDILE,
        KROKOROK,
        KROOKODILE,
        DARUMAKA,
        DARMANITAN,
        MARACTUS,
        DWEBBLE,
        CRUSTLE,
        SCRAGGY,
        SCRAFTY,
        SIGILYPH,
        YAMASK,
        COFAGRIGUS,
        TIRTOUGA,
        CARRACOSTA,
        ARCHEN,
        ARCHEOPS,
        TRUBBISH,
        GARBODOR,
        ZORUA,
        ZOROARK,
        MINCCINO,
        CINCCINO,
        GOTHITA,
        GOTHORITA,
        GOTHITELLE,
        SOLOSIS,
        DUOSION,
        REUNICLUS,
        DUCKLETT,
        SWANNA,
        VANILLITE,
        VANILLISH,
        VANILLUXE,
        DEERLING,
        SAWSBUCK,
        EMOLGA,
        KARRABLAST,
        ESCAVALIER,
        FOONGUS,
        AMOONGUSS,
        FRILLISH,
        JELLICENT,
        ALOMONOLA,
        JOLTIK,
        GALVANTULA,
        FERROSEED,
        FERROTHORN,
        KLINK,
        KLANG,
        KLINKLANG,
        TYNAMO,
        EELEKTRIK,
        ELEKTROSS,
        ELGYEM,
        BEHEEYEM,
        LITWICK,
        LAMPENT,
        CHANDELURE,
        AXEW,
        FRAXURE,
        HAXORUS,
        CUBCHOO,
        BEARTIC,
        CRYOGONAL,
        SHELMET,
        ACCELGOR,
        STUNFISH,
        MIENFOO,
        MINESHAO,
        DRUDDIGON,
        GOLETT,
        GOLURK,
        PAWNIARD,
        BISHARP,
        BOUFFALANT,
        RUFFLET,
        BRAVIARY,
        VULLABY,
        MANDIBUZZ,
        HEATMOR,
        DURANT,
        DEINO,
        ZWEILOUS,
        HYDREIGON,
        LARVESTA,
        VOLCARONA,
        COBALION,
        TERRAKION,
        VIRIZION,
        TORNADUS,
        THUNDURUS,
        RESHIRAM,
        ZEKROM,
        LANDORUS,
        KYUREM,
        KELDEO,
        MELOETTA,
        GENESECT
    };

    enum class Stat {
        ATTACK, DEFENSE, SP_ATTACK, SP_DEFENSE, SPEED, ACCURACY, EVASIVENESS
    };

    Pokemon(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed);

    Pokemon(const Pokemon &) = delete;

    Pokemon(Pokemon &&toMove) noexcept;

    Pokemon &operator=(const Pokemon &) = delete;

    Pokemon &operator=(Pokemon &&) noexcept = delete;

    ~Pokemon() override = default;

    [[nodiscard]] std::string getName() const override = 0;

    [[nodiscard]] int numMoves() const;

    void addMove(std::unique_ptr<Move> toAdd);

    template<typename M>
    void addMove() {
        if (this->moveSet.size() == Pokemon::MAX_NUM_MOVES) {
            return;
        }

        this->moveSet.push_back(std::make_unique<M>());
    }

    void deleteMove(int index);

    void setHp(int amount);

    void restoreHp(int amount);

    void takeDamage(int amount);

    [[nodiscard]] int getHp() const;

    [[nodiscard]] int getMaxHp() const;

    void resetStatMods();

    void raiseStatMod(Pokemon::Stat stat, int amount);

    void lowerStatMod(Pokemon::Stat stat, int amount);

    [[nodiscard]] int getStatMod(Pokemon::Stat stat) const;

    [[nodiscard]] int getBaseStat(Pokemon::Stat stat) const;

    [[nodiscard]] virtual Type getType(bool type1) const = 0;

    void setStatus(Status newStatus);

    [[nodiscard]] Status getStatus() const;

    [[nodiscard]] const char *getStatusAsString() const;

    void levelUp();

    [[nodiscard]] int getLevel() const;

    [[nodiscard]] virtual int getCatchRate() const = 0;

    [[nodiscard]] virtual Pokemon::Id getId() const = 0;

    [[nodiscard]] bool isFainted() const;

    [[nodiscard]] bool isFullHp() const;

    [[nodiscard]] bool isFasterThan(const Pokemon &pokemon) const;

    [[nodiscard]] bool isAfflicted() const;

    [[nodiscard]] bool canAttack() const;

    void hpEmptyMessage() const;

    void hpFullMessage() const;

    Move &operator[](int index);

    const Move &operator[](int index) const;

private:
    const static int MAX_NUM_MOVES{ 4 };

    int maxHp;
    int currentHp{ 0 };

    std::unordered_map<Pokemon::Stat, int> statModifiers;
    std::unordered_map<Pokemon::Stat, int> baseStats;

    int level;

    std::vector<std::unique_ptr<Move>> moveSet;
    Status status{ Status::NONE };

    double getStat(Pokemon::Stat stat) const;
};
