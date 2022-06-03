#include <iostream>
#include <vector>
#include <unistd.h>
#include "main.h"
#include "Pokemon.h"
#include "Moves.h"

using namespace std;

int main() {
    Pokemon Greninja("Greninja", 300);
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

    vector<Pokemon> userParty = {Greninja, Pikachu}, userFaintedParty;
    vector<Pokemon> opponentParty = {Charizard}, opponentFaintedParty;

    srand(time(nullptr));

    cout << "A wild " << opponentParty.at(0).GetName() << " appeared!" << endl;
    sleep(2);

    cout << "Go " << userParty.at(0).GetName() << "!" << endl << endl;
    sleep(2);

    while (true) {
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// USER'S TURN
        bool skip = false;
        char userChoice;
        int userMove, opponentMove = rand() % 4;
        DisplayHP(userParty, opponentParty);
        DisplayChoices(userParty);
        cin >> userChoice;

        if (userChoice == 'f') {
            DisplayMoves(userParty.at(0).GetMoves());
            cin >> userMove;
            if (userMove <= 4 && userMove >= 1) {
                if (userParty.at(0).GetMoves().at(userMove - 1).GetPP() > 0) {
                    Attack(opponentParty.at(0), userParty.at(0).GetMoves().at(userMove - 1));
                    AttackMessage(userParty, userParty.at(0).GetMoves(), userMove - 1);

                    if (opponentParty.at(0).GetHP() <= 0) {
                        Faint(opponentParty, opponentFaintedParty);
                        FaintMessage(opponentParty);
                        if (opponentParty.empty()) {
                            cout << "You won!" << endl;
                            break;
                        }
                    }

                }
                else {
                    cout << "That move is out of power points! Please select another move!" << endl;
                    cin >> userMove;
                    while (userParty.at(0).GetMoves().at(userMove - 1).GetPP() <= 0 && userMove != 0) {
                        cout << "That move is out of power points! Please select another move!" << endl;
                        cin >> userMove;
                    }
                    if (userMove == 0) {
                        skip = true;
                    }
                }
            }

            else if (userMove == 0) {
                skip = true;
            }

            else {
                cout << "You didn't choose one of the available options. Please try again." << endl;
                sleep(2);
                skip = true;
            }
        }
<<<<<<< Updated upstream
        // TODO: ADD BAG
        else if (userChoice == 'b') {
            cout << "bag function not yet implemented" << endl << endl;
            sleep(2);
            skip = true;
=======

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
>>>>>>> Stashed changes
        }

        else if (userChoice == 'r') {
            bool runSuccess = false;
            Run(runSuccess);
            RunMessage(runSuccess);
            if (runSuccess) {
                break;
            }
        }

        else if (userChoice == 's') {
            int userSwitch;
            if (userParty.size() == 1) {
                cout << "Cannot switch with only one Pokemon in the userParty" << endl;
                sleep(2);
                skip = true;
            }
            else {
                DisplayPokemon(userParty, userFaintedParty);
                cin >> userSwitch;

                if (userSwitch >= 1 && userSwitch <= 5 && userSwitch < userParty.size()) {
                    if (userParty.at(userSwitch).GetHP() > 0) {
                        Switch(userParty, userSwitch);
                        SwitchMessage(userParty);
                    }
                    else {
                        cout << "That Pokemon's HP is 0. Choose another Pokemon" << endl;
                        sleep(2);
                        skip = true;
                    }
                }

                else if (userSwitch == 0) {
                    skip = true;
                }

                else {
                    cout << "You didn't choose one of the available options. Please choose again" << endl;
                    sleep(2);
                    skip = true;
                }
            }
        }

        else {
            cout << "You didn't choose one of the available options. Please try again." << endl;
            sleep(2);
            skip = true;
        }
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// OPPONENT'S TURN
        if (!skip) {
            if (opponentParty.at(0).GetMoves().at(opponentMove).GetPP() > 0) {
                Attack(userParty.at(0), opponentParty.at(0).GetMoves().at(opponentMove));
                AttackMessage(opponentParty, opponentParty.at(0).GetMoves(), opponentMove);

                if (userParty.at(0).GetHP() <= 0) {
                    Faint(userParty, userFaintedParty);
                    FaintMessage(userParty);
                    if (userParty.empty()) {
                        cout << "You've run out of usable Pokemon!" << endl;
                        sleep(2);
                        cout << "You blacked out!" << endl;
                        break;
                    }
                }
            }
        }
    }
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// END OF BATTLE
    return 0;
}