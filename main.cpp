#include "main.h"
#include "Pokemon.h"
#include "Moves.h"
#include "Items.h"


int main() {
    Pokemon Greninja("Greninja", 300);\
    Greninja.SetBaseStats(95, 67, 103, 71, 122);
        Moves WaterShuriken("Water Shuriken", "water", 20, 15);
        Moves DarkPulse("Dark Pulse", "dark", 20, 50);
        Moves IceBeam("Ice Beam", "ice", 15, 60);
        Moves Extrasensory("Extrasensory", "psychic", 15, 60);

    Pokemon Charizard("Charizard", 300);
        Moves Flamethrower("Flamethrower", "fire", 15, 60);
        Moves AirSlash("Air Slash", "flying", 15, 50);
        Moves DragonPulse("Dragon Pulse", "dragon", 10, 60);
        Moves SolarBeam("Solar Beam", "grass", 10, 70);

    Pokemon Pikachu("Pikachu", 300);


    Greninja.SetMoves(WaterShuriken, DarkPulse, IceBeam, Extrasensory);
    Charizard.SetMoves(Flamethrower, AirSlash, DragonPulse, SolarBeam);

    std::vector<Pokemon> userParty = {Greninja, Pikachu}, userFaintedParty;
    std::vector<Pokemon> opponentParty = {Charizard}, opponentFaintedParty;

    HPItems Potion(2, 20, "Potion");
    PPItems Ether(2, 5, "Ether");

    ParalysisItems ParalyzeHeal(2, "Paralysis Heal");
    BurnItems BurnHeal(3, "Burn Heal");
    FreezeItems IceHeal(2, "Ice Heal");

    std::vector<RestoreItems> userRestoreItems = {Potion, Ether};
    std::vector<StatusItems> userStatusItems = {ParalyzeHeal, BurnHeal, IceHeal};

    srand(time(nullptr));

    IntroMessage(userParty, opponentParty);

    while (true) {
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// USER'S TURN
        bool skip = false, runSuccess = false;
        char userChoice;
        int userMove, userItem, opponentMove = rand() % 4, pokemon;
        DisplayHP(userParty, opponentParty);
        DisplayChoices(userParty);
        GetChoice(userChoice);

        if (userChoice == 'f' && isalpha(userChoice)) {
            DisplayMoves(userParty.at(0));
            std::cin >> userMove;

            if (userMove <= 4 && userMove >= 1) {
                if (userParty.at(0).GetMove(userMove - 1).GetPP() > 0) {
                    Attack(opponentParty.at(0), userParty.at(0), userMove - 1);
                    AttackMessage(userParty, userMove - 1);

                    if (opponentParty.at(0).GetHP() <= 0) {
                        Faint(opponentParty, opponentFaintedParty);
                        FaintMessage(opponentParty);
                        if (opponentParty.empty()) {
                            WinMessage();
                            break;
                        }
                    }
                }

                else {
                    AttackErrorMessage();
                    skip = true;
                }
            }

            else if (userMove == 0) {
                skip = true;
            }

            else {
                InvalidOptionMessage();
                skip = true;
            }
        }

        else if (userChoice == 'b' && isalpha(userChoice)) { // enters the bag
            DisplayBag();
            std::cin >> userItem;

            while (userItem < 0 || userItem > 4) { // bounds checking
                InvalidOptionMessage();
                std::cin >> userItem;
            }

            if (userItem == 1) { // user chose HP/PP items
                DisplayRestoreItems(userRestoreItems);
                std::cin >> userItem;

                if (userItem >= 1 && userItem <= userRestoreItems.size()) {
                    DisplayPokemonHeal(userParty);
                    std::cin >> pokemon;

                    if (pokemon <= 6 && pokemon >= 1) {
                        if (userParty.at(pokemon - 1).GetMaxHP() == userParty.at(pokemon - 1).GetHP()) {
                            std::cout << userParty.at(pokemon - 1).GetName() << "'s HP is full!" << std::endl;
                            sleep(2);
                            skip = true;
                        }
                        else {
                            if (userRestoreItems.at(userItem - 1).GetQuantity() > 0) {
                                Heal(userParty.at(pokemon - 1), userRestoreItems.at(userItem - 1).GetAmount());
                                HealMessage(userParty.at(pokemon - 1), userRestoreItems.at(userItem - 1).GetAmount());
                                Items::UseItem(userRestoreItems.at(userItem - 1));
                            }
                            else {
                                RestoreItems::ItemErrorMessage(userRestoreItems, userItem);
                                skip = true;
                            }
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

            else if (userItem == 2) {
                DisplayStatusItems(userStatusItems);
                std::cin >> userItem;

                if (userItem >= 1 && userItem <= userStatusItems.size()) {
                    DisplayPokemonHeal(userParty);
                    std::cin >> pokemon;

                    if (pokemon <= 6 && pokemon >= 1) {
                        if (userParty.at(pokemon - 1).GetStatus() == "No status") {
                            std::cout << userParty.at(pokemon - 1).GetName() << " has no status condition" << std::endl;
                            sleep(2);
                        }
                        else {
                            if (userStatusItems.at(userItem - 1).GetQuantity() > 0) {
                                //TODO: Add heal virtual heal function
                                //Heal(userStatusItems.at(userItem - 1), userParty.at(pokemon - 1));
                            }
                            else {
                                StatusItems::ItemErrorMessage(userStatusItems, userItem);
                                skip = true;
                            }
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

            else if (userItem == 3) {

            }

            else if (userItem == 0) {
                skip = true;
            }
        }

        else if (userChoice == 'r' && isalpha(userChoice)) {
            Run(runSuccess);
            RunMessage(runSuccess);
            if (runSuccess) {
                break;
            }
        }

        else if (userChoice == 'p' && isalpha(userChoice)) {
            int userSwitch;
            if (userParty.size() == 1) {
                std::cout << "Cannot switch with only one Pokemon in the userParty" << std::endl;
                sleep(2);
                skip = true;
            }
            else {
                DisplayPokemon(userParty, userFaintedParty);
                std::cin >> userSwitch;

                if (userSwitch >= 1 && userSwitch <= 5 && userSwitch < userParty.size()) {
                    if (userParty.at(userSwitch).GetHP() > 0) {
                        Switch(userParty, userSwitch);
                        SwitchMessage(userParty);
                    }
                    else {
                        SwitchErrorMessage();
                        skip = true;
                    }
                }

                else if (userSwitch == 0) {
                    skip = true;
                }

                else {
                    InvalidOptionMessage();
                    skip = true;
                }
            }
        }

        else {
            InvalidOptionMessage();
            skip = true;
        }
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// OPPONENT'S TURN
        if (!skip) {
            if (opponentParty.at(0).GetMove(opponentMove).GetPP() > 0) {
                Attack(userParty.at(0), opponentParty.at(0), opponentMove);
                AttackMessage(opponentParty, opponentMove);

                if (userParty.at(0).GetHP() <= 0) {
                    Faint(userParty, userFaintedParty);
                    FaintMessage(userParty);
                    if (userParty.empty()) {
                        LoseMessage();
                        break;
                    }
                }
            }
        }
    }
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// END OF BATTLE
    return 0;
}