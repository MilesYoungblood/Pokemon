#include "main.h"
#include "ItemFunctions.h"
#include "MoveList.h"

int main() {
    Pokemon Greninja("Greninja", "water", "dark", 50);
    Greninja.setBaseStats(300, 95, 67, 103, 71, 122);
        WaterShuriken WS;
        Moves DarkPulse("Dark Pulse", "dark", "special", 15, 80, 100);
        Moves IceBeam("Ice Beam", "ice", "special", 10, 90, 100);
        Moves Extrasensory("Extrasensory", "psychic", "special", 15, 90, 100);

    Pokemon Charizard("Charizard", "fire", "flying", 50);
    Charizard.setBaseStats(300, 84, 78, 109, 85, 100);
        Moves Flamethrower("Flamethrower", "fire", "special", 15, 90, 100);
        Moves AirSlash("Air Slash", "flying", "special", 15, 75, 95);
        Moves DragonPulse("Dragon Pulse", "dragon", "special", 10, 85, 100);
        Moves SolarBeam("Solar Beam", "grass", "special", 10, 120, 100);

    Pokemon Hydreigon("Hydreigon", "dark", "dragon", 50);
    Hydreigon.setBaseStats(300, 105, 90, 125, 90, 98);
        const Moves& Dr_Pulse(DragonPulse);
        const Moves& Da_Pulse(DarkPulse);
        const Moves& FThrower(Flamethrower);
        Moves FocusBlast("Focus Blast", "fighting", "special", 5, 120, 70);

    Pokemon Pikachu("Pikachu", "electric", 50);
    Pikachu.setBaseStats(300, 55, 40, 50, 50, 90);
        Moves Thunder("Thunder", "electric", "special", 10, 110, 70);
        Moves QuickAttack("Quick Attack", "normal", "physical", 30, 40, 100);
        Moves IronTail("Iron Tail", "steel", "physical", 15, 100, 75);
        Moves VoltTackle("Volt Tackle", "electric", "physical", 15, 120, 100);

    Pokemon Lucario("Lucario", "fighting", "steel", 50);
    Lucario.setBaseStats(300, 110, 70, 115, 70, 90);
        Moves AuraSphere("Aura Sphere", "fighting", "special", 20, 80, 100);
        Moves FlashCannon("Flash Cannon", "steel", "special", 10, 80, 100);
        const Moves& Dragon_Pulse(DragonPulse);
        const Moves& Dark_Pulse(DarkPulse);

    std::vector<Pokemon> userParty = {Greninja, Pikachu, Lucario};
    std::vector<Pokemon> opponentParty = {Charizard};

    Trainer Miles;
    Miles.setParty(Greninja, Pikachu, Lucario);

    userParty.at(0).setMoves(WS, DarkPulse, IceBeam, Extrasensory);
    userParty.at(1).setMoves(Thunder, QuickAttack, IronTail, VoltTackle);
    userParty.at(2).setMoves(AuraSphere, FlashCannon, Dragon_Pulse, Dark_Pulse);

    opponentParty.at(0).setMoves(Flamethrower, AirSlash, DragonPulse, SolarBeam);

    RestoreItems Potion(2, 20, "Potion", "HP");
    RestoreItems Ether(2, 5, "Ether", "PP");

    StatusItems ParalyzeHeal(2, "Paralysis Heal", "paralysis");
    StatusItems BurnHeal(3, "Burn Heal", "burn");
    StatusItems IceHeal(2, "Ice Heal", "freeze");
    StatusItems Antidote(3, "Antidote", "poison");
    StatusItems Awakening(4, "Awakening", "sleep");

    PokeBalls PokeBall(5, 1.0, "Poke Ball");
    PokeBalls GreatBall(5, 2.0, "Great Ball");
    PokeBalls UltraBall(5, 3.0, "Ultra Ball");

    BattleItems XAttack(10, "X-Attack", "attack");
    BattleItems XSpeed(5, "X-Speed", "speed");

    std::vector<RestoreItems> userRestoreItems = {Potion, Ether};
    std::vector<StatusItems> userStatusItems = {ParalyzeHeal, BurnHeal, IceHeal, Antidote, Awakening};
    std::vector<PokeBalls> userPokeBalls = {PokeBall, GreatBall, UltraBall};
    std::vector<BattleItems> userBattleItems = {XAttack, XSpeed};

    int userMonsFainted = 0;
    int opponentMonsFainted = 0;
    int turn = 1;
    bool battleOver = false;

    introMessage(userParty.at(0).getName(), opponentParty.at(0).getName());

    while (true) { // enters the battle
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// USER SELECTIONS
        int userMove, userItem, pokemon;
        std::cout << "\nTurn " << turn;
        displayHP(userParty.at(0), opponentParty.at(0));
        displayChoices(userParty.at(0).getName());
        char userChoice = getChar();

        if (userChoice == 'f') { // trainer chose fight
            displayMoves(userParty.at(0));
            userMove = getInt(0, NUM_MOVES);

            if (userMove == 0) {
                continue;
            }
            else if (userParty.at(0).getMove(userMove - 1).getPP() <= 0) { // if move chosen is out of PP...
                attackErrorMessage();
                continue;
            }
        }

        else if (userChoice == 'b') { // trainer chose bag
            displayBag();
            userItem = getInt(0, 4);

            if (userItem == 1) { // trainer chose HP/PP items
                displayItems(userRestoreItems);
                userItem = getInt(0, static_cast<int>(userRestoreItems.size()));

                if (userItem == 0) {
                    continue;
                }
                else if (userRestoreItems.at(userItem - 1).getQuantity() > 0) { // if trainer has at least 1 of the item selected...
                    displayPokemon(userParty);
                    pokemon = getInt(0, static_cast<int>(userParty.size()));

                    if (pokemon == 0) {
                        continue;
                    }
                    else if (userParty.at(pokemon - 1).getHP() < userParty.at(pokemon - 1).getMaxHp() and
                        userParty.at(pokemon - 1).getHP() > 0) { // if Pokémon selected doesn't have full HP, but isn't fainted...
                        if (userRestoreItems.at(userItem - 1).getRestoreType() == "HP") { // if item selected restores HP...
                            HP::restore(userParty.at(pokemon - 1),userRestoreItems.at(userItem - 1).getAmount());
                            HP::restoreMessage(userParty.at(pokemon - 1),userRestoreItems.at(userItem - 1).getAmount());
                            useItem(userRestoreItems.at(userItem - 1));
                        }
                        else if (userRestoreItems.at(userItem - 1).getRestoreType() == "PP") { // if item selected restores PP...
                            displayMoves(userParty.at(pokemon - 1));
                            userMove = getInt(0, NUM_MOVES);

                            if (userMove == 0) {
                                continue;
                            }
                            else {
                                PP::restore(userParty.at(pokemon - 1).getMove(userMove - 1),userRestoreItems.at(userItem - 1).getAmount());
                                PP::restoreMessage(userParty.at(pokemon - 1).getMove(userMove - 1),userRestoreItems.at(userItem - 1).getAmount());
                                useItem(userRestoreItems.at(userItem - 1));
                            }
                        }
                    }
                    else { // Pokémon's HP is already full
                        hpFullMessage(userParty.at(pokemon - 1).getName());
                        continue;
                    }
                }
                else { // trainer is out of selected item
                    itemErrorMessage(userRestoreItems.at(userItem - 1).getName());
                    continue;
                }
            }

            else if (userItem == 2) { // trainer chose status items
                displayItems(userStatusItems);
                userItem = getInt(0, static_cast<int>(userStatusItems.size()));

                if (userItem == 0) {
                    continue;
                }
                else if (userStatusItems.at(userItem - 1).getQuantity() > 0) { // if trainer has at least 1 of the item selected...
                    displayPokemon(userParty);
                    pokemon = getInt(0, static_cast<int>(userParty.size()));

                    if (pokemon == 0) {
                        continue;
                    }
                    else if (userParty.at(pokemon - 1).getHP() > 0) { // if Pokémon is not fainted...
                        if (userParty.at(pokemon - 1).getStatus() != "No status") { // if Pokémon has status condition...
                            cure(userParty.at(pokemon - 1), userStatusItems.at(userItem - 1));
                            cureMessage(userParty.at(pokemon - 1),userStatusItems.at(userItem - 1).getRestoreType());
                            useItem(userStatusItems.at(userItem - 1));
                        }
                        else { // Pokémon did not have a status condition
                            useItem(userStatusItems.at(userItem - 1));
                            noEffectMessage(userStatusItems.at(userItem - 1).getName(), userParty.at(pokemon - 1).getName());
                        }
                    }
                    else { // Pokémon is fainted
                        hpEmptyMessage(userParty.at(pokemon - 1).getName());
                        continue;
                    }
                }
                else { // trainer is out of selected item
                    itemErrorMessage(userStatusItems.at(userItem - 1).getName());
                    continue;
                }
            }

            else if (userItem == 3) { // trainer chose Poké Balls
                displayItems(userPokeBalls);
                userItem = getInt(0, static_cast<int>(userPokeBalls.size()));

                if (userItem == 0) {
                    continue;
                }
                else if (userPokeBalls.at(userItem - 1).getQuantity() > 0) { // if trainer has at least one of item selected...
                    //TODO ADD POKÉ BALL FUNCTIONALITY
                    useItem(userPokeBalls.at(userItem - 1));
                    useItemMessage(userPokeBalls.at(userItem - 1).getName());
                }
                else { // trainer is out of selected item
                    itemErrorMessage(userPokeBalls.at(userItem - 1).getName());
                    continue;
                }
            }

            else if (userItem == 4) { // trainer chose battle items
                displayItems(userBattleItems);
                userItem = getInt(0, static_cast<int>(userBattleItems.size()));

                if (userItem == 0) {
                    continue;
                }
                else if (userBattleItems.at(userItem - 1).getQuantity() > 0) { // if trainer has at least 1 of the item selected...
                    bool limitReached = false;
                    useItem(userBattleItems.at(userItem - 1));
                    useItemMessage(userBattleItems.at(userItem - 1).getName());
                    boostStat(userBattleItems.at(userItem - 1), userParty.at(0), 1, limitReached);
                    boostMessage(userParty.at(0), userBattleItems.at(userItem - 1).getStat(), 1, limitReached);
                }
                else {
                    itemErrorMessage(userBattleItems.at(userItem - 2).getName());
                    continue;
                }
            }

            else if (userItem == 0) {
                continue;
            }
        }

        else if (userChoice == 'r') { // trainer chose run
            bool runAway = run();
            runMessage(runAway);
            if (runAway) {
                break;
            }
        }

        else if (userChoice == 'p') { // trainer chose Pokémon
            displayPokemon(userParty);
            pokemon = getInt(0, static_cast<int>(userParty.size()));

            if (pokemon == 0) {
                continue;
            }

            pokemonPrompt();
            std::cin >> userChoice;

            while (userChoice != 'c' and userChoice != 's' and userChoice != '0') {
                std::cin >> userChoice;
            }

            if (userChoice == 'c') {
                displayMoves(userParty.at(pokemon - 1));
                userMove = getInt(0, NUM_MOVES);

                if (userMove == 0) {
                    continue;
                }

                displayMoveSummary(userParty.at(pokemon - 1).getMove(userMove - 1));
                userMove = getInt(0, 0);

                continue;
            }
            else if (userChoice == 's') {
                if (userMonsFainted == userParty.size() - 1) { // trainer has only one healthy Pokémon
                    switchOutErrorMessage();
                    continue;
                }
                else {
                    if (1 < pokemon and pokemon <= userParty.size()) { // user chose in-bounds option
                        if (userParty.at(pokemon - 1).getHP() > 0) { // Pokémon chosen is not fainted
                            switchOut(userParty, pokemon - 1);
                            switchOutMessage(userParty, pokemon - 1);
                        }
                        else { // Pokémon chosen is fainted
                            hpEmptyMessage(userParty.at(pokemon - 1).getName());
                            continue;
                        }
                    }
                    else if (pokemon == 1) { // trainer chose Pokémon currently in battle
                        std::cout << userParty.at(0).getName() << " is already in battle!" << std::endl;
                        sleep(2);

                        continue;
                    }
                }
            }
            else if (userChoice == '0') {
                continue;
            }
        }
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// BATTLE PHASE
        int opponentMove = generateInteger(0, 3);
        while (opponentParty.at(0).getMove(opponentMove).getPP() <= 0) { // re-selects opponent move if it's out of PP
            opponentMove = generateInteger(0, 3);
        }

        if (userChoice == 'f') { // if trainer chose to attack this turn...
            if (userParty.at(0).getBaseSpeed() > opponentParty.at(0).getBaseSpeed()) { // trainer is faster than opponent...
                userAttack(userParty, opponentParty, userMove, opponentMonsFainted, battleOver);
                if (battleOver) {
                    break;
                }
                opponentAttack(opponentParty, userParty, opponentMove, userMonsFainted, battleOver);
                if (battleOver) {
                    break;
                }
            }
            else if (userParty.at(0).getBaseSpeed() < opponentParty.at(0).getBaseSpeed()) { // if opponent is faster than trainer...
                opponentAttack(opponentParty, userParty, opponentMove, userMonsFainted, battleOver);
                if (battleOver) {
                    break;
                }
                userAttack(userParty, opponentParty, userMove, opponentMonsFainted, battleOver);
                if (battleOver) {
                    break;
                }
            }
            else { // trainer and opponent rival in speed
                if (generateInteger(0, 1) == 0) {
                    userAttack(userParty, opponentParty, userMove, opponentMonsFainted, battleOver);
                    if (battleOver) {
                        break;
                    }
                    opponentAttack(opponentParty, userParty, opponentMove, userMonsFainted, battleOver);
                    if (battleOver) {
                        break;
                    }
                }
                else {
                    opponentAttack(opponentParty, userParty, opponentMove, userMonsFainted, battleOver);
                    if (battleOver) {
                        break;
                    }
                    userAttack(userParty, opponentParty, userMove, opponentMonsFainted, battleOver);
                    if (battleOver) {
                        break;
                    }
                }
            }
        }
        else { // trainer chose not to attack this turn
            opponentAttack(opponentParty, userParty, opponentMove, userMonsFainted, battleOver);
            if (battleOver) {
                break;
            }
        }
        ++turn;
    }
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// END OF BATTLE
    return 0;
}