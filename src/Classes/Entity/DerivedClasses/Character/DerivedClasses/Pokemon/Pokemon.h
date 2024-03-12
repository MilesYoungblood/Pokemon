//
// Created by miles on 5/5/2022.
//

#pragma once

#include "../../Character.h"
#include "../../../../../Move/Move.h"
#include "../../../../../Ability/Ability.h"
#include "../../../../../../Enums/StatusCondition/StatusCondition.h"

class Pokemon : public Character {
public:
    enum class Id : Uint8 {
        VICTINI, SNIVY, SERVINE, SERPERIOR, TEPIG, PIGNITE, EMBOAR, OSHAWOTT, DEWOTT, SAMUROTT, PATRAT, WATCHOG, LILLIPUP,
        HERDIER, STOUTLAND, PURRLOIN, LIEPARD, PANSAGE, SIMISAGE, PANSEAR, SIMISEAR, PANPOUR, SIMIPOUR, MUNNA, MUSHARNA,
        PIDOVE, TRANQUILL, UNFEZANT, BLITZLE, ZEBSTRIKA, ROGGENROLA, BOLDORE, GIGALITH, WOOBAT, SWOOBAT, DRILBUR, EXCADRILL,
        AUDINO, TIMBURR, GURDURR, CONKELDURR, TYMPOLE, PALPITOAD, SEISMITOAD, THROH, SAWK, SEWADDLE, SWADLOON, LEAVANNY,
        VENIPEDE, WHIRLIPEDE, SCOLIPEDE, COTTONEE, WHIMSICOTT, PETILIL, LILLIGANT, BASCULIN, SANDILE, KROKOROK, KROOKODILE,
        DARUMAKA, DARMANITAN, MARACTUS, DWEBBLE, CRUSTLE, SCRAGGY, SCRAFTY, SIGILYPH, YAMASK, COFAGRIGUS, TIRTOUGA, CARRACOSTA,
        ARCHEN, ARCHEOPS, TRUBBISH, GARBODOR, ZORUA, ZOROARK, MINCCINO, CINCCINO, GOTHITA, GOTHORITA, GOTHITELLE, SOLOSIS,
        DUOSION, REUNICLUS, DUCKLETT, SWANNA, VANILLITE, VANILLISH, VANILLUXE, DEERLING, SAWSBUCK, EMOLGA, KARRABLAST,
        ESCAVALIER, FOONGUS, AMOONGUSS, FRILLISH, JELLICENT, ALOMOMOLA, JOLTIK, GALVANTULA, FERROSEED, FERROTHORN, KLINK,
        KLANG, KLINKLANG, TYNAMO, EELEKTRIK, EELEKTROSS, ELGYEM, BEHEEYEM, LITWICK, LAMPENT, CHANDELURE, AXEW, FRAXURE,
        HAXORUS, CUBCHOO, BEARTIC, CRYOGONAL, SHELMET, ACCELGOR, STUNFISK, MIENFOO, MIENSHAO, DRUDDIGON, GOLETT, GOLURK,
        PAWNIARD, BISHARP, BOUFFALANT, RUFFLET, BRAVIARY, VULLABY, MANDIBUZZ, HEATMOR, DURANT, DEINO, ZWEILOUS, HYDREIGON,
        LARVESTA, VOLCARONA, COBALION, TERRAKION, VIRIZION, TORNADUS, THUNDURUS, RESHIRAM, ZEKROM, LANDORUS, KYUREM,
        KELDEO, MELOETTA, GENESECT
    };

    enum class Gender : Uint8 {
        MALE, FEMALE, GENDERLESS
    };

    enum class Stat : Uint8 {
        ATTACK, DEFENSE, SP_ATTACK, SP_DEFENSE, SPEED, ACCURACY, EVASIVENESS
    };

    enum : Uint8 {
        MAX_NUM_MOVES = 4
    };

    Pokemon(Ability::Id ability, int level, int hp, double attack, double defense, double spAttack, double spDefense, double speed);

    Pokemon(Ability::Id ability, double pMale, int level, int hp, double attack, double defense, double spAttack, double spDefense, double speed);

    Pokemon(const Pokemon &) = delete;

    Pokemon(Pokemon &&) noexcept = default;

    Pokemon &operator=(const Pokemon &) = delete;

    Pokemon &operator=(Pokemon &&) noexcept = delete;

    ~Pokemon() override = default;

    [[nodiscard]] int numMoves() const;

    void addMove(const std::string &id);

    void deleteMove(int index);

    void tryActivateAbility(int battleFlag, Pokemon &opponent, bool isAttacking);

    void restoreHp(int amount);

    void takeDamage(int amount);

    [[nodiscard]] int getHp() const;

    [[nodiscard]] int getMaxHp() const;

    void initStatMods();

    void raiseStatMod(Pokemon::Stat stat, int amount);

    void lowerStatMod(Pokemon::Stat stat, int amount);

    [[nodiscard]] int getStatMod(Pokemon::Stat stat) const;

    [[nodiscard]] double getBaseStat(Pokemon::Stat stat) const;

    void setStatus(StatusCondition newStatus);

    [[nodiscard]] StatusCondition getStatus() const;

    void levelUp();

    [[nodiscard]] int getLevel() const;

    [[nodiscard]] std::string getName() const override = 0;

    void setNickName(const char *nickname);

    [[nodiscard]] std::string getNickName() const;

    virtual std::string getSpecies() const = 0;

    void setGender(Pokemon::Gender newGender);

    Pokemon::Gender getGender() const;

    void setAbility(std::unique_ptr<Ability> newAbility);

    Ability &getAbility();

    const Ability &getAbility() const;

    virtual Type getType1() const = 0;

    virtual Type getType2() const;

    virtual double getHeight() const = 0;

    virtual double getWeight() const = 0;

    virtual int getCatchRate() const = 0;

    virtual Pokemon::Id getId() const = 0;

    [[nodiscard]] bool isFainted() const;

    [[nodiscard]] bool isFullHp() const;

    [[nodiscard]] bool isFasterThan(const Pokemon &pokemon) const;

    [[nodiscard]] bool rivalsInSpeed(const Pokemon &pokemon) const;

    [[nodiscard]] bool isAfflicted() const;

    [[nodiscard]] bool canAttack() const;

    [[nodiscard]] std::string hpEmptyMessage() const;

    [[nodiscard]] std::string hpFullMessage() const;

    Move &operator[](int index);

    std::vector<std::unique_ptr<Move>>::iterator begin();

    std::vector<std::unique_ptr<Move>>::iterator end();

private:
    Pokemon(Pokemon::Gender gender, Ability::Id ability, int level, int hp, double attack, double defense, double spAttack, double spDefense, double speed);

    int maxHp;
    int currentHp;

    std::unordered_map<Pokemon::Stat, double> baseStats;
    std::unordered_map<Pokemon::Stat, int> statModifiers;

    int level;

    std::vector<std::unique_ptr<Move>> moveSet;
    std::unique_ptr<Ability> ability;

    Pokemon::Gender gender;
    StatusCondition status{ StatusCondition::NONE };

    double getStat(Pokemon::Stat stat) const;
};

inline std::mutex pokemonMutex;
inline std::unordered_map<std::string, std::unique_ptr<Pokemon>(*)()> pokemonMap;
