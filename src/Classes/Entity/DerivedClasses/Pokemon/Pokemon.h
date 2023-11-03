//
// Created by miles on 5/5/2022.
//

#pragma once

#include "../../Entity.h"
#include "../../../Move/Move.h"

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

    std::vector<std::unique_ptr<Move>> moveSet;
    std::array<Type, Pokemon::MAX_NUM_TYPES> types;
    Status status{Status::NONE};
    
    int moveCounter{0};

    static void raiseStat(int &stat, int amount);
    static void lowerStat(int &stat, int amount);

    static double getStatMod(int stat);

public:
    Pokemon(const char *name, Type type, int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed, int catchRate);
    Pokemon(const char *name, Type type1, Type type2, int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed, int catchRate);
    Pokemon(const Pokemon &) = delete;
    Pokemon(const Pokemon &&) = delete;
    Pokemon & operator=(const Pokemon &) = delete;
    Pokemon & operator=(const Pokemon &&) = delete;
    virtual ~Pokemon() = default;

    [[nodiscard]] virtual PokemonID getID() const;

    [[nodiscard]] int numMoves() const;

    void addMove(std::unique_ptr<Move> move);

    template<typename M>
    void addMove() {
        try {
            if (this->moveCounter == Pokemon::MAX_NUM_MOVES) {
                return;
            }

            this->moveSet.push_back(std::make_unique<M>());
            ++this->moveCounter;
        }
        catch (const std::exception &e) {
            throw std::runtime_error(std::string("Error adding move: ") + e.what() + '\n');
        }
    }

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

    [[nodiscard]] int getHP() const;
    [[nodiscard]] int getAttack() const;
    [[nodiscard]] int getDefense() const;
    [[nodiscard]] int getSpAttack() const;
    [[nodiscard]] int getSpDefense() const;
    [[nodiscard]] int getSpeed() const;
    [[nodiscard]] int getAccuracy() const;
    [[nodiscard]] int getEvasiveness() const;

    [[nodiscard]] int getMaxHp() const;
    [[nodiscard]] int getBaseAttack() const;
    [[nodiscard]] int getBaseDefense() const;
    [[nodiscard]] int getBaseSpAttack() const;
    [[nodiscard]] int getBaseSpDefense() const;
    [[nodiscard]] int getBaseSpeed() const;

    [[nodiscard]] Type getType(bool type_1) const;

    void setStatus(Status newStatus);
    [[nodiscard]] Status getStatus() const;
    [[nodiscard]] const char * getStatusAsString() const;

    [[nodiscard]] int getLevel() const;
    [[nodiscard]] int getCatchRate() const;

    [[nodiscard]] bool isFainted() const;
    [[nodiscard]] bool isFullHP() const;
    [[nodiscard]] bool isFasterThan(const Pokemon &pokemon) const;
    [[nodiscard]] bool isAfflicted() const;
    [[nodiscard]] bool canAttack() const;

    void hpEmptyMessage() const;
    void hpFullMessage() const;

    Move & operator[](int index);
    const Move & operator[](int index) const;
};
