//
// Created by miles on 5/5/2022.
//

#pragma once

#include "../../../AutoThread/AutoThread.h"
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
        ALOMOMOLA,
        JOLTIK,
        GALVANTULA,
        FERROSEED,
        FERROTHORN,
        KLINK,
        KLANG,
        KLINKLANG,
        TYNAMO,
        EELEKTRIK,
        EELEKTROSS,
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
        STUNFISK,
        MIENFOO,
        MIENSHAO,
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

    enum class Gender {
        MALE, FEMALE, GENDERLESS
    };

    enum class Stat {
        ATTACK, DEFENSE, SP_ATTACK, SP_DEFENSE, SPEED, ACCURACY, EVASIVENESS
    };

    Pokemon(int level, int hp, double attack, double defense, double spAttack, double spDefense, double speed);

    Pokemon(double pMale, int level, int hp, double attack, double defense, double spAttack, double spDefense, double speed);

    Pokemon(const Pokemon &) = delete;

    Pokemon(Pokemon &&) noexcept = delete;

    Pokemon &operator=(const Pokemon &) = delete;

    Pokemon &operator=(Pokemon &&) noexcept = delete;

    ~Pokemon() override = default;

    [[nodiscard]] int numMoves() const;

    template<typename ...Args>
    void addMove(Args ...args) {
        if (this->moveSet.size() == Pokemon::MAX_NUM_MOVES) {
            return;
        }

        this->moveSet.push_back(Move(args...));
    }

    void deleteMove(int index);

    void restoreHp(int amount);

    void takeDamage(int amount);

    [[nodiscard]] int getHp() const;

    [[nodiscard]] int getMaxHp() const;

    void initStatMods();

    void raiseStatMod(Pokemon::Stat stat, int amount);

    void lowerStatMod(Pokemon::Stat stat, int amount);

    [[nodiscard]] int getStatMod(Pokemon::Stat stat) const;

    [[nodiscard]] double getBaseStat(Pokemon::Stat stat) const;

    void setStatus(Status newStatus);

    [[nodiscard]] Status getStatus() const;

    [[nodiscard]] const char *getStatusAsString() const;

    void levelUp();

    [[nodiscard]] int getLevel() const;

    std::string getName() const override = 0;

    virtual std::string getSpecies() const = 0;

    void setGender(Pokemon::Gender newGender);

    Pokemon::Gender getGender() const;

    virtual Type getType(bool type1) const = 0;

    virtual double getHeight() const = 0;

    virtual double getWeight() const = 0;

    virtual int getCatchRate() const = 0;

    virtual Pokemon::Id getId() const = 0;

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
    int currentHp;

    std::unordered_map<Pokemon::Stat, double> baseStats;
    std::unordered_map<Pokemon::Stat, int> statModifiers;

    int level;

    std::vector<Move> moveSet;
    Pokemon::Gender gender;
    Status status{ Status::NONE };

    double getStat(Pokemon::Stat stat) const;
};

inline std::unordered_map<Pokemon::Id, std::unique_ptr<Pokemon>(*)()> pokemonLookupTable;
