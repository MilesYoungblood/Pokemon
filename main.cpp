#include "main.h"

int main() {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(0.0, 4.0); // generates a number from 0 to 3 inclusive

    Pokemon Greninja("Greninja", "water", "dark", 100);
    Greninja.SetBaseStats(95, 67, 103, 71, 122);
        Moves WaterShuriken("Water Shuriken", "water", 20, 15);
        Moves DarkPulse("Dark Pulse", "dark", 20, 50);
        Moves IceBeam("Ice Beam", "ice", 15, 60);
        Moves Extrasensory("Extrasensory", "psychic", 15, 60);

    Pokemon Charizard("Charizard", "fire", "flying", 300);
        Moves Flamethrower("Flamethrower", "fire", 15, 60);
        Moves AirSlash("Air Slash", "flying", 15, 50);
        Moves DragonPulse("Dragon Pulse", "dragon", 10, 60);
        Moves SolarBeam("Solar Beam", "grass", 10, 70);

    Pokemon Pikachu("Pikachu", "electric", 300);
        Moves Thunder("Thunder", "electric", 10, 70);
        Moves QuickAttack("Quick Attack", "normal", 25, 40);
        Moves IronTail("Iron Tail", "steel", 20, 50);
        Moves VoltTackle("Volt Tackle", "electric", 5, 70);

    Pokemon Lucario("Lucario", "fighting", "steel", 300);
        Moves AuraSphere("Aura Sphere", "fighting", 10, 60);
        Moves FlashCannon("Flash Cannon", "steel", 15, 60);
        const Moves& Dragon_Pulse(DragonPulse);
        const Moves& Dark_Pulse(DarkPulse);

    Greninja.SetMoves(WaterShuriken, DarkPulse, IceBeam, Extrasensory);
    Pikachu.SetMoves(Thunder, QuickAttack, IronTail, VoltTackle);
    Lucario.SetMoves(AuraSphere, FlashCannon, Dragon_Pulse, Dark_Pulse);

    Charizard.SetMoves(Flamethrower, AirSlash, DragonPulse, SolarBeam);

    std::vector<Pokemon> userParty = {Greninja, Pikachu, Lucario};
    std::vector<Pokemon> opponentParty = {Charizard};

    RestoreItems Potion(2, 20, "Potion", "HP");
    RestoreItems Ether(2, 5, "Ether", "PP");

    StatusItems ParalyzeHeal(2, "Paralysis Heal", "paralysis");
    StatusItems BurnHeal(3, "Burn Heal", "burn");
    StatusItems IceHeal(2, "Ice Heal", "freeze");
    StatusItems Antidote(3, "Antidote", "poison");
    StatusItems Awakening(4, "Awakening", "sleep");

    PokeBalls PokeBall(5, 1.0, "Poké Ball");
    PokeBalls GreatBall(5, 2.0, "Great Ball");
    PokeBalls UltraBall(5, 3.0, "Ultra Ball");

    std::vector<RestoreItems> userRestoreItems = {Potion, Ether};
    std::vector<StatusItems> userStatusItems = {ParalyzeHeal, BurnHeal, IceHeal, Antidote};
    std::vector<PokeBalls> userPokeBalls = {PokeBall, GreatBall, UltraBall};

    int userMonsFainted = 0, opponentMonsFainted = 0;

    IntroMessage(userParty, opponentParty);

    while (true) {
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// USER'S TURN
        bool skip = false, runSuccess = false;
        char userChoice;
        int userMove, userItem, userSwitch, opponentMove = (int)dist(mt), pokemon;
        DisplayHP(userParty, opponentParty);
        DisplayChoices(userParty);
        std::cin >> userChoice;

        while (userChoice != 'f' and userChoice != 'b' and userChoice != 'r' and userChoice != 'p') {
            std::cin >> userChoice;
        }

        if (userChoice == 'f' and isalpha(userChoice)) { // trainer chose fight
            DisplayMoves(userParty.at(0));
            std::cin >> userMove;

            while (userMove < 0 or NUM_MOVES < userMove) { // bounds checking
                std::cin >> userMove;
            }

            if (1 <= userMove and userMove <= NUM_MOVES) { // trainer chose in-bounds option
                if (userParty.at(0).GetMove(userMove - 1).GetPP() > 0) { // if move chosen has at least 1 PP...
                    Attack(opponentParty.at(0), userParty.at(0), userMove - 1);
                    AttackMessage(userParty, userMove - 1);

                    if (opponentParty.at(0).GetHP() <= 0) { // if Pokémon's HP drops to zero...
                        FaintMessage(opponentParty);
                        Faint(opponentParty.at(0), opponentMonsFainted);
                        if (opponentMonsFainted == opponentParty.size()) {
                            WinMessage();
                            break;
                        }
                    }
                }

                else { // move chosen is out of PP
                    AttackErrorMessage();
                    skip = true;
                }
            }

            else if (userMove == 0) {
                skip = true;
            }
        }

        else if (userChoice == 'b' and isalpha(userChoice)) { // trainer chose bag
            DisplayBag();
            std::cin >> userItem;

            while (userItem < 0 or 4 < userItem) { // bounds checking
                std::cin >> userItem;
            }

            if (userItem == 1) { // trainer chose HP/PP items
                DisplayItems(userRestoreItems);
                std::cin >> userItem;

                if (1 <= userItem and userItem <= userRestoreItems.size()) { // if trainer chooses in-bounds option...
                    DisplayPokemonHeal(userParty);
                    std::cin >> pokemon;

                    while (pokemon < 0 or userParty.size() < pokemon) { // bounds checking
                        std::cin >> pokemon;
                    }

                    if (1 <= pokemon and pokemon <= userParty.size()) { // if trainer chooses in bounds option...
                        if (userParty.at(pokemon - 1).GetHP() < userParty.at(pokemon - 1).GetMaxHP()) { // if Pokémon selected doesn't have full HP...
                            if (userRestoreItems.at(userItem - 1).GetQuantity() > 0) { // if trainer has at least 1 of the item selected...
                                if (userRestoreItems.at(userItem - 1).GetRType() == "HP") { // if item selected restores HP
                                    Restore(userParty.at(pokemon - 1), userRestoreItems.at(userItem - 1).GetAmount());
                                    RestoreMessage(userParty.at(pokemon - 1), userRestoreItems.at(userItem - 1).GetAmount());
                                    Items::UseItem(userRestoreItems.at(userItem - 1));
                                }
                                else if (userRestoreItems.at(userItem - 1).GetRType() == "PP") {
                                    DisplayMoves(userParty.at(pokemon - 1));
                                    std::cin >> userMove;

                                    while (userMove < 0 or NUM_MOVES < userMove) {
                                        std::cin >> userMove;
                                    }

                                    if (1 <= userMove and userMove <= NUM_MOVES) {
                                        Restore(userParty.at(pokemon - 1).GetMove(userMove - 1), userRestoreItems.at(userItem - 1).GetAmount());
                                        RestoreMessage(userParty.at(pokemon - 1).GetMove(userMove - 1), userRestoreItems.at(userItem - 1).GetAmount());
                                        Items::UseItem(userRestoreItems.at(userItem - 1));
                                    }
                                    else if (userMove == 0) {
                                        skip = true;
                                    }
                                }
                            }
                            else { // item has 0 PP
                                ItemErrorMessage(userRestoreItems.at(userItem - 1).GetName());
                                skip = true;
                            }
                        }
                        else { // Pokémon's HP is already full
                            HPFullMessage(userParty.at(pokemon - 1));
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
                DisplayItems(userStatusItems);
                std::cin >> userItem;

                while (userItem < 0 or userStatusItems.size() < userItem) { // bounds checking
                    std::cin >> userItem;
                }

                if (userItem >= 1 and userItem <= userStatusItems.size()) { // if trainer chose in-bounds option...
                    DisplayPokemon(userParty);
                    std::cin >> pokemon;

                    while (pokemon < 0 or userParty.size() < pokemon) { // bounds checking
                        std::cin >> pokemon;
                    }

                    if (1 <= pokemon and pokemon <= userParty.size()) { // if trainer chose in-bounds option...
                        if (userParty.at(pokemon - 1).GetHP() > 0) { // if Pokémon is not fainted...
                            if (userParty.at(pokemon - 1).GetStatus() != "No status") { // if Pokémon has status condition...
                                if (userStatusItems.at(userItem - 1).GetQuantity() > 0) { // if trainer has at least 1 of the item selected...
                                    Cure(userParty.at(pokemon - 1), userStatusItems.at(userItem - 1));
                                    CureMessage(userParty.at(pokemon - 1), userStatusItems.at(userItem - 1).GetRType());
                                    Items::UseItem(userStatusItems.at(userItem - 1));
                                }
                                else {
                                    ItemErrorMessage(userStatusItems.at(userItem - 1).GetName());
                                    skip = true;
                                }
                            }
                            else { // Pokémon did not have a status condition
                                Items::UseItem(userStatusItems.at(userItem - 1));
                                std::cout << userStatusItems.at(userItem - 1).GetName() << " had no effect on "
                                          << userParty.at(pokemon - 1).GetName() << '.' << std::endl;
                                sleep(2);
                            }
                        }
                        else { // Pokémon is fainted
                            HPEmptyMessage(userParty.at(pokemon - 1));
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
                DisplayItems(userPokeBalls);
                std::cin >> userItem;

                while (userItem < 0 or userPokeBalls.size() < userItem) { // bounds checking
                    std::cin >> userItem;
                }

                if (1 <= userItem and userItem <= userPokeBalls.size()) { // trainer chose in-bounds option
                    //TODO ADD POKÉ BALL FUNCTIONALITY
                }

                else if (userItem == 0) {
                    skip = true;
                }
            }

            else if (userItem == 4) {
                //TODO ADD BATTLE ITEM FUNCTIONALITY
            }

            else if (userItem == 0) {
                skip = true;
            }
        }

        else if (userChoice == 'r' and isalpha(userChoice)) { // trainer chose run
            Run(runSuccess);
            RunMessage(runSuccess);
            if (runSuccess) {
                break;
            }
        }

        else if (userChoice == 'p') { // trainer chose Pokémon
            if (userMonsFainted == userParty.size() - 1) { // trainer has only one healthy Pokémon
                SwitchErrorMessage();
                skip = true;
            }
            else {
                DisplayPokemon(userParty);
                std::cin >> userSwitch;

                while (userSwitch < 0 or userParty.size() < userSwitch) { // bounds checking
                    std::cin >> userSwitch;
                }

                if (userSwitch >= 1 and userSwitch < userParty.size()) { // user chose in-bounds option
                    if (userParty.at(userSwitch).GetHP() > 0) { // Pokémon chosen is not fainted
                        Switch(userParty, userSwitch);
                        SwitchMessage(userParty, userSwitch);
                    }
                    else { // Pokémon chosen is fainted
                        HPEmptyMessage(userParty.at(userSwitch));
                        skip = true;
                    }
                }

                else if (userSwitch == 0) {
                    skip = true;
                }
            }
        }
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// OPPONENT'S TURN
        if (!skip) {

            while (opponentParty.at(0).GetMove(opponentMove).GetPP() <= 0) { // re-selects opponent move if it's out of PP
                opponentMove = (int)dist(mt);
            }

            if (opponentParty.at(0).GetMove(opponentMove).GetPP() > 0) {
                Attack(userParty.at(0), opponentParty.at(0), opponentMove);
                AttackMessage(opponentParty, opponentMove);

                if (userParty.at(0).GetHP() <= 0) {
                    Faint(userParty.at(0), userMonsFainted);
                    FaintMessage(userParty);
                    if (userMonsFainted == userParty.size()) {
                        LoseMessage();
                        break;
                    }
                    ForceSwitchPrompt();
                    std::cin >> userChoice;

                    while (userChoice != 'f' and userChoice != 'r') {
                        std::cin >> userChoice;
                    }

                    if (userChoice == 'r') {
                        Run(runSuccess);
                        RunMessage(runSuccess);
                        if (runSuccess) {
                            break;
                        }
                    }

                    if (userMonsFainted < userParty.size() - 1) { // forces switch after Pokémon is fainted
                        DisplayPokemon(userParty);
                        std::cin >> userSwitch;

                        while ((userSwitch < 1 or userParty.size() - 1 < userSwitch) and userParty.at(pokemon).GetHP() <= 0) {
                            if (userParty.at(pokemon).GetHP() <= 0) {
                                HPEmptyMessage(userParty.at(pokemon));
                            }
                            std::cin >> userSwitch;
                        }

                        Switch(userParty, userSwitch);
                    }
                }
            }
        }
    }
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// END OF BATTLE
    return 0;
}