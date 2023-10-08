//
// Created by Miles on 10/7/2023.
//

#pragma once

#include <fstream>

#include "../Classes/Factory/PokemonFactory.h"
#include "../Classes/Factory/MoveFactory.h"

// for me to work between my laptop and desktop
static bool desktop = true;

const char *saveFilePath = desktop ?
                           R"(C:\Users\Miles\Documents\GitHub\PokemonBattle\src\Data\SaveData.txt)" :
                           R"(C:\Users\Miles Youngblood\OneDrive\Documents\GitHub\PokemonBattle\src\Data\SaveData.txt)";

void saveData(Player *player, Map *maps[], int numMaps, int currentMapIndex) {
    std::cout << "Saving please wait...";

    std::ofstream saveFile(saveFilePath);
    if (not saveFile) {
        throw std::runtime_error("Could not open file");
    }

    saveFile << currentMapIndex;
    saveFile << '\n' << player->getX() << player->getY() << player->getDirection();
    saveFile << '\n' << player->partySize();

    for (int i = 0; i < player->partySize(); ++i) {
        saveFile << '\n' << (*player)[i].getID() << ' ';

        const int numMoves = (*player)[i].numMoves();
        saveFile << numMoves << ' ';
        for (int j = 0; j < numMoves; ++j) {
            saveFile << (*player)[i][j].getID() << ' ';
        }
    }

    for (int i = 0; i < numMaps; ++i) {
        for (int j = 0; j < maps[i]->numNPCs(); ++j) {
            saveFile << '\n' << i << j << (*maps)[i][j].partySize();
            saveFile << (*maps)[i][j].getDirection();
        }
    }

    saveFile.close();
}

void loadData(Player *player, Map *maps[], int &currentMapIndex) {
    std::ifstream saveFile(saveFilePath);

    auto loadDirection = [](Entity *entity, int direction) {
        switch (direction) {
            case 0:
                entity->faceNorth();
                break;

            case 1:
                entity->faceEast();
                break;

            case 2:
                entity->faceSouth();
                break;

            case 3:
                entity->faceWest();
                break;

            default:
                throw std::runtime_error("Unexpected error: lambda loadDirection");
        }
    };

    if (saveFile) {
        std::string buffer;

        std::getline(saveFile, buffer);
        currentMapIndex = buffer[0] - '0';

        std::getline(saveFile, buffer);
        player->setCoordinates(buffer[0] - '0', buffer[1] - '0');

        loadDirection(player, buffer[2] - '0');

        std::getline(saveFile, buffer);
        const int partySize = buffer[0] - '0';

        player->clearParty();
        for (int i = 0; i < partySize; ++i) {
            std::getline(saveFile, buffer, ' ');
            player->addPokemon(PokemonFactory::getPokemon(PokemonID(std::stoi(buffer))));

            std::getline(saveFile, buffer, ' ');
            const int numMoves = buffer[0] - '0';

            for (int j = 0; j < numMoves; ++j) {
                std::getline(saveFile, buffer, ' ');
                (*player)[i].addMove(MoveFactory::getMove(MoveID(std::stoi(buffer))));
            }
            std::getline(saveFile, buffer);
        }

        while (std::getline(saveFile, buffer)) {
            const int map = buffer[0] - '0';
            const int trainer = buffer[1] - '0';

            if (buffer[2] == '0') {
                (*maps)[map][trainer].clearParty();
            }
            loadDirection(&(*maps)[map][trainer], buffer[3] - '0');
        }

        saveFile.close();
    }
    else {
        player->addPokemon(new Greninja({ new WaterShuriken, new DarkPulse, new IceBeam, new Extrasensory }));
        player->addPokemon(new Charizard({ new Flamethrower, new AirSlash, new DragonPulse, new SolarBeam }));
        player->addPokemon(new Hydreigon({ new DarkPulse, new DragonPulse, new Flamethrower, new FocusBlast }));
    }
}

void eraseData() {
    std::remove(saveFilePath);
}

// returns true if the player is quitting, false otherwise
bool openMenu(Player *player, Map *maps[], int numMaps, int currentMapIndex) {
    int option = 0;
    bool print = true;

    reprint_1:
    system("cls");
    if (print)
        printMessage("Choose an option\n");
    else
        std::cout << "Choose an option\n";

    option == 0 ? std::cout << "   ->   Pokemon\n" : std::cout << "\tPokemon\n";
    option == 1 ? std::cout << "   ->   Bag\n" : std::cout << "\tBag\n";
    option == 2 ? std::cout << "   ->   Save\n" : std::cout << "\tSave\n";
    option == 3 ? std::cout << "   ->   Quit\n" : std::cout << "\tQuit\n";
    option == 4 ? std::cout <<"\n   ->   Back" : std::cout << "\n\tBack";

    print = false;

    if (not chooseOption(option, 4))
        goto reprint_1;

    switch (option) {
        case 0:
            system("cls");
            std::cerr << "Pokemon option to be implemented...";
            pressEnter();
            return false;

        case 1:
            system("cls");
            std::cerr << "Bag option to be implemented...";
            pressEnter();
            return false;

        case 2:
            option = 0;
            print = true;

        reprint_2:
            system("cls");
            if (print)
                printMessage("Are you ready to save?\n");
            else
                std::cout << "Are you ready to save?\n";

            option == 0 ? std::cout << "   ->   Yes\n" : std::cout << "\tYes\n";
            option == 1 ? std::cout << "   ->   No" : std::cout << "\tNo";

            print = false;

            if (not chooseOption(option, 1))
                goto reprint_2;

            if (option == 0) {
                saveData(player, maps, numMaps, currentMapIndex);
                system("cls");
                printMessage("Save complete!");
                pressEnter();
                return false;
            }
            else {
                option = 0;
                print = true;
                goto reprint_1;
            }

        case 3:
            return true;

        default:
            return false;
    }
}