#include "main.h"
#include "AttackFunctions.h"
#include "ItemFunctions.h"
#include "MoveList.h"

int main() {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(0, 3); // generates a number from 0 to 3 inclusive

    Pokemon Greninja("Greninja", "water", "dark", 36);
    Greninja.setBaseStats(500, 95, 67, 103, 71, 122);
        WaterShuriken WS;
        Moves DarkPulse("Dark Pulse", "dark", "special", 15, 80, 100);
        Moves IceBeam("Ice Beam", "ice", "special", 10, 90, 100);
        Moves Extrasensory("Extrasensory", "psychic", "special", 15, 90, 100);

    Pokemon Charizard("Charizard", "fire", "flying", 32);
    Charizard.setBaseStats(300, 84, 78, 109, 85, 100);
        Moves Flamethrower("Flamethrower", "fire", "special", 15, 90, 100);
        Moves AirSlash("Air Slash", "flying", "special", 15, 75, 95);
        Moves DragonPulse("Dragon Pulse", "dragon", "special", 10, 85, 100);
        Moves SolarBeam("Solar Beam", "grass", "special", 10, 120, 100);

    Pokemon Pikachu("Pikachu", "electric", 300);
        Moves Thunder("Thunder", "electric", "special", 10, 110, 70);
        Moves QuickAttack("Quick getDamage", "normal", "physical", 30, 40, 100);
        Moves IronTail("Iron Tail", "steel", "physical", 15, 100, 75);
        Moves VoltTackle("Volt Tackle", "electric", "physical", 15, 120, 100);

    Pokemon Lucario("Lucario", "fighting", "steel", 300);
        Moves AuraSphere("Aura Sphere", "fighting", "special", 20, 80, 100);
        Moves FlashCannon("Flash Cannon", "steel", "special", 10, 80, 100);
        const Moves& Dragon_Pulse(DragonPulse);
        const Moves& Dark_Pulse(DarkPulse);

    std::vector<Pokemon> userParty = {Greninja, Pikachu, Lucario};
    std::vector<Pokemon> opponentParty = {Charizard};

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
    std::vector<StatusItems> userStatusItems = {ParalyzeHeal, BurnHeal, IceHeal, Antidote};
    std::vector<PokeBalls> userPokeBalls = {PokeBall, GreatBall, UltraBall};
    std::vector<BattleItems> userBattleItems = {XAttack, XSpeed};

    int userMonsFainted = 0, opponentMonsFainted = 0;

    introMessage(userParty.at(0).getName(), opponentParty.at(0).getName());

    bool battleOver = false;
    while (true) {
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// USER SELECTIONS
        bool skip = false, runAway = false;
        char userChoice;
        int userMove, userItem, pokemon, opponentMove = dist(mt);
        displayHP(userParty, opponentParty);
        displayChoices(userParty.at(0));
        std::cin >> userChoice;

        while (userChoice != 'f' and userChoice != 'b' and userChoice != 'r' and userChoice != 'p') {
            std::cin >> userChoice;
        }

        if (userChoice == 'f' and isalpha(userChoice)) { // trainer chose fight
            displayMoves(userParty.at(0));
            std::cin >> userMove;

            while (userMove < 0 or NUM_MOVES < userMove) { // bounds checking
                std::cin >> userMove;
            }

            if (1 <= userMove and userMove <= NUM_MOVES) { // trainer chose in-bounds option
                if (userParty.at(0).getMove(userMove - 1).getPP() <= 0) { // if move chosen is out of PP...
                    attackErrorMessage();
                    skip = true;
                }
            }

            else if (userMove == 0) {
                skip = true;
            }
        }

        else if (userChoice == 'b' and isalpha(userChoice)) { // trainer chose bag
            displayBag();
            std::cin >> userItem;

            while (userItem < 0 or 4 < userItem) { // bounds checking
                std::cin >> userItem;
            }

            if (userItem == 1) { // trainer chose HP/PP items
                displayItems(userRestoreItems);
                std::cin >> userItem;

                if (1 <= userItem and userItem <= userRestoreItems.size()) { // if trainer chooses in-bounds option...
                    displayPokemon(userParty);
                    std::cin >> pokemon;

                    while (pokemon < 0 or userParty.size() < pokemon) { // bounds checking
                        std::cin >> pokemon;
                    }

                    if (1 <= pokemon and pokemon <= userParty.size()) { // if trainer chooses in bounds option...
                        if (userParty.at(pokemon - 1).getHP() < userParty.at(pokemon - 1).getMaxHp() and
                                userParty.at(pokemon - 2).getHP() > 0) { // if Pokémon selected doesn't have full HP...
                            if (userRestoreItems.at(userItem - 1).getQuantity() > 0) { // if trainer has at least 1 of the item selected...
                                if (userRestoreItems.at(userItem - 1).getRestoreType() == "HP") { // if item selected restores HP
                                    restore(userParty.at(pokemon - 1), userRestoreItems.at(userItem - 1).getAmount());
                                    restoreMessage(userParty.at(pokemon - 1),
                                                   userRestoreItems.at(userItem - 1).getAmount());
                                    Items::useItem(userRestoreItems.at(userItem - 1));
                                }
                                else if (userRestoreItems.at(userItem - 1).getRestoreType() == "PP") {
                                    displayMoves(userParty.at(pokemon - 1));
                                    std::cin >> userMove;

                                    while (userMove < 0 or NUM_MOVES < userMove) {
                                        std::cin >> userMove;
                                    }

                                    if (1 <= userMove and userMove <= NUM_MOVES) {
                                        restore(userParty.at(pokemon - 1).getMove(userMove - 1),
                                                userRestoreItems.at(userItem - 1).getAmount());
                                        restoreMessage(userParty.at(pokemon - 1).getMove(userMove - 1),
                                                       userRestoreItems.at(userItem - 1).getAmount());
                                        Items::useItem(userRestoreItems.at(userItem - 1));
                                    }
                                    else if (userMove == 0) {
                                        skip = true;
                                    }
                                }
                            }
                            else { // item has 0 PP
                                itemErrorMessage(userRestoreItems.at(userItem - 1).getName());
                                skip = true;
                            }
                        }
                        else { // Pokémon's HP is already full
                            hpFullMessage(userParty.at(pokemon - 1));
                            skip = true;
                        }
                    }

                    else if (pokemon == 0) {
                        skip = true;
                    }
                }

                else if (userItem == 0) {
                    skip = true;
                }
            }

            else if (userItem == 2) { // trainer chose status items
                displayItems(userStatusItems);
                std::cin >> userItem;

                while (userItem < 0 or userStatusItems.size() < userItem) { // bounds checking
                    std::cin >> userItem;
                }

                if (userItem >= 1 and userItem <= userStatusItems.size()) { // if trainer chose in-bounds option...
                    displayPokemon(userParty);
                    std::cin >> pokemon;

                    while (pokemon < 0 or userParty.size() < pokemon) { // bounds checking
                        std::cin >> pokemon;
                    }

                    if (1 <= pokemon and pokemon <= userParty.size()) { // if trainer chose in-bounds option...
                        if (userParty.at(pokemon - 1).getHP() > 0) { // if Pokémon is not fainted...
                            if (userParty.at(pokemon - 1).getStatus() != "No status") { // if Pokémon has status condition...
                                if (userStatusItems.at(userItem - 1).getQuantity() > 0) { // if trainer has at least 1 of the item selected...
                                    cure(userParty.at(pokemon - 1), userStatusItems.at(userItem - 1));
                                    cureMessage(userParty.at(pokemon - 1),
                                                userStatusItems.at(userItem - 1).getRestoreType());
                                    Items::useItem(userStatusItems.at(userItem - 1));
                                }
                                else { // trainer is out of selected item
                                    itemErrorMessage(userStatusItems.at(userItem - 1).getName());
                                    skip = true;
                                }
                            }
                            else { // Pokémon did not have a status condition
                                Items::useItem(userStatusItems.at(userItem - 1));
                                std::cout << userStatusItems.at(userItem - 1).getName() << " had no effect on "
                                          << userParty.at(pokemon - 1).getName() << '.' << std::endl;
                                sleep(2);
                            }
                        }
                        else { // Pokémon is fainted
                            hpEmptyMessage(userParty.at(pokemon - 1));
                            skip = true;
                        }
                    }

                    else if (pokemon == 0) {
                        skip = true;
                    }
                }

                else if (userItem == 0) {
                    skip = true;
                }
            }

            else if (userItem == 3) { // trainer chose Poké Balls
                displayItems(userPokeBalls);
                std::cin >> userItem;

                while (userItem < 0 or userPokeBalls.size() < userItem) { // bounds checking
                    std::cin >> userItem;
                }

                if (1 <= userItem and userItem <= userPokeBalls.size()) { // if trainer chose in-bounds option...
                    //TODO ADD POKÉ BALL FUNCTIONALITY
                }

                else if (userItem == 0) {
                    skip = true;
                }
            }

            else if (userItem == 4) { // trainer chose battle items
                displayItems(userBattleItems);
                std::cin >> userItem;

                while (userItem < 0 or userBattleItems.size() < userItem) { // bounds checking
                    std::cin >> userItem;
                }

                if (1 <= userItem and userItem <= userBattleItems.size()) { // if trainer chose in-bounds option...
                    if (userBattleItems.at(userItem - 1).getQuantity() > 0) { // if trainer has at least 1 of the item selected...
                        bool limitReached = false;
                        Items::useItem(userBattleItems.at(userItem - 1));
                        useItemMessage(userBattleItems.at(userItem - 1).getName());
                        boostStat(userBattleItems.at(userItem - 1), userParty.at(0), 1, limitReached);
                        boostMessage(userParty.at(0), userBattleItems.at(userItem - 1).getStat(), 1, limitReached);
                    }
                    else {
                        itemErrorMessage(userBattleItems.at(userItem - 2).getName());
                        skip = true;
                    }
                }

                else if (userItem == 0) {
                    skip = true;
                }
            }

            else if (userItem == 0) {
                skip = true;
            }
        }

        else if (userChoice == 'r' and isalpha(userChoice)) { // trainer chose run
            run(runAway);
            runMessage(runAway);
            if (runAway) {
                break;
            }
        }

        else if (userChoice == 'p') { // trainer chose Pokémon
            displayPokemon(userParty);
            std::cin >> pokemon;

            while (pokemon < 0 or userParty.size() < pokemon) { // bounds checking
                std::cin >> pokemon;
            }

            if (pokemon == 0) {
                skip = true;
            }

            if (!skip) {
                pokemonPrompt();
                std::cin >> userChoice;

                while (userChoice != 'c' and userChoice != 's' and userChoice != '0') {
                    std::cin >> userChoice;
                }

                if (userChoice == 'c') {
                    displayMoves(userParty.at(pokemon - 1));
                    std::cin >> userMove;

                    while (userMove != 0) {
                        // TODO ADD FUNCTIONALITY FOR CHECKING MOVE SUMMARY
                        std::cin >> userMove;
                    }

                    if (userMove == 0) {
                        skip = true;
                    }
                }
                else if (userChoice == 's') {
                    if (userMonsFainted == userParty.size() - 1) { // trainer has only one healthy Pokémon
                        switchOutErrorMessage();
                        skip = true;
                    }
                    else {
                        if (1 < pokemon and pokemon <= userParty.size()) { // user chose in-bounds option
                            if (userParty.at(pokemon - 1).getHP() > 0) { // Pokémon chosen is not fainted
                                switchOut(userParty, pokemon - 1);
                                switchOutMessage(userParty, pokemon - 1);
                            } else { // Pokémon chosen is fainted
                                hpEmptyMessage(userParty.at(pokemon - 1));
                                skip = true;
                            }
                        }
                        else if (pokemon == 1) {
                            std::cout << userParty.at(0).getName() << " is already in battle!" << std::endl;
                            sleep(2);

                            skip = true;
                        }
                    }
                }
                else if (userChoice == '0') {
                    skip = true;
                }
            }
        }
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// OPPONENT SELECTIONS
        if (!skip) {
            while (opponentParty.at(0).getMove(opponentMove).getPP() <= 0) { // re-selects opponent move if it's out of PP
                opponentMove = (int)dist(mt);
            }
        }
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// BATTLE PHASE
        if (!skip) {
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
                    std::uniform_int_distribution<int> coinFlip(1, 2);
                    int flip = coinFlip(mt);
                    if (flip == 1) {
                        userAttack(userParty, opponentParty, userMove, opponentMonsFainted, battleOver);
                        if (battleOver) {
                            break;
                        }
                        opponentAttack(opponentParty, userParty, opponentMove, userMonsFainted, battleOver);
                        if (battleOver) {
                            break;
                        }
                    }
                    else if (flip == 2) {
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
        }
    }
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// END OF BATTLE
    return 0;
}