//
// Created by miles on 5/5/2022.
//

#pragma once

#include "../Entity/Entity.h"
#include "../Move/Move.h"

#include <array>

enum class Status { NONE, BURN, PARALYSIS, FREEZE, POISON, SLEEP };

enum PokemonID {
    VENASAUR,
    CHARIZARD,
    PIKACHU,
    LUCARIO,
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
    GENESECT,
    GRENINJA
};

class Pokemon : public Entity {
private:
    const static int MAX_NUM_MOVES = 4;
    const static int MAX_NUM_TYPES = 2;

    const char *name;

    int maxHP;
    int currentHP{0};
    int attack{0};
    int defense{0};
    int spAttack{0};
    int spDefense{0};
    int speed{0};
    int accuracy{0};
    int evasiveness{0};

    int baseAttack;
    int baseDefense;
    int baseSpAttack;
    int baseSpDefense;
    int baseSpeed;
    int level;

    int catchRate;

    std::vector<Move *> moveSet;
    std::array<Type, Pokemon::MAX_NUM_TYPES> types;
    Status status{Status::NONE};
    
    int moveCounter{0};

    static void raiseStat(int &stat, int amount);
    static void lowerStat(int &stat, int amount);

    static auto getStatMod(int stat) -> double;

public:
    Pokemon(const char *name, Type type, int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed, int catchRate);
    Pokemon(const char *name, Type type1, Type type2, int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed, int catchRate);
    Pokemon(const char *name, Type type, int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed, int catchRate, const std::initializer_list<Move*> &moves);
    Pokemon(const char *name, Type type1, Type type2, int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed, int catchRate, const std::initializer_list<Move*> &moves);
    Pokemon(const Pokemon &) = delete;
    auto operator=(const Pokemon &) -> Pokemon& = delete;
    Pokemon(const Pokemon &&) = delete;
    auto operator=(const Pokemon &&) -> Pokemon& = delete;
    virtual ~Pokemon();

    virtual auto getID() -> PokemonID = 0;

    [[nodiscard]] auto numMoves() const -> int;

    void addMove(Move *move);
    void deleteMove(int index);
    void setMoves(const std::initializer_list<Move *> &moves);

    void setHP(int newHP);
    void restoreHP(int newHP);
    void takeDamage(int amount);

    void resetStatMods();

    void raiseAttack(int amount);
    void raiseDefense(int amount);
    void raiseSpAttack(int amount);
    void raiseSpDefense(int amount);
    void raiseSpeed(int amount);
    void raiseAccuracy(int amount);
    void raiseEvasiveness(int amount);

    void lowerAttack(int amount);
    void lowerDefense(int amount);
    void lowerSpAttack(int amount);
    void lowerSpDefense(int amount);
    void lowerSpeed(int amount);
    void lowerAccuracy(int amount);
    void lowerEvasiveness(int amount);

    [[nodiscard]] auto getHP() const -> int;
    [[nodiscard]] auto getAttack() const -> int;
    [[nodiscard]] auto getDefense() const -> int;
    [[nodiscard]] auto getSpAttack() const -> int;
    [[nodiscard]] auto getSpDefense() const -> int;
    [[nodiscard]] auto getSpeed() const -> int;
    [[nodiscard]] auto getAccuracy() const -> int;
    [[nodiscard]] auto getEvasiveness() const -> int;

    [[nodiscard]] auto getMaxHp() const -> int;
    [[nodiscard]] auto getBaseAttack() const -> int;
    [[nodiscard]] auto getBaseDefense() const -> int;
    [[nodiscard]] auto getBaseSpAttack() const -> int;
    [[nodiscard]] auto getBaseSpDefense() const -> int;
    [[nodiscard]] auto getBaseSpeed() const -> int;

    [[nodiscard]] auto getName() const -> std::string;

    [[nodiscard]] auto getType(bool type_1) const -> Type;

    void setStatus(Status newStatus);
    [[nodiscard]] auto getStatus() const -> Status;
    [[nodiscard]] auto getStatusAsString() const -> const char *;

    [[nodiscard]] auto getLevel() const -> int;
    [[nodiscard]] auto getCatchRate() const -> int;

    [[nodiscard]] auto isFainted() const -> bool;
    [[nodiscard]] auto isFullHP() const -> bool;
    [[nodiscard]] auto isFasterThan(const Pokemon &pokemon) const -> bool;
    [[nodiscard]] auto isAfflicted() const -> bool;
    [[nodiscard]] auto canAttack() const -> bool;

    void hpEmptyMessage() const;
    void hpFullMessage() const;

    auto operator[](int index) -> Move&;
    auto operator[](int index) const -> const Move&;

    friend auto operator<<(std::ostream &out, const Pokemon &pokemon) -> std::ostream&;
};
