//
// Created by Miles on 10/2/2023.
//

#include "Game.h"

const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;

const int SCROLL_SPEED = 300;

SDL_Texture *playerText;

Game::Game() : maps() {
    this->player = nullptr;
    this->currentMap = nullptr;
    this->currentMapIndex = 0;

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        std::cout << "Subsystems initialized!" << std::endl;

        this->window = SDL_CreateWindow("Pokemon", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
        if (this->window) {
            std::cout << "Window created!" << std::endl;
        }

        this->renderer = SDL_CreateRenderer(this->window, -1, 0);
        if (this->renderer) {
            std::cout << "Renderer created!" << std::endl;
        }

        this->isRunning = true;
    }
    else {
        this->isRunning = false;
    }

    SDL_Surface *surface = IMG_Load(R"(C:\Users\Miles\Documents\GitHub\PokemonBattle\pokeball.png)");
    if (not surface) {
        std::cerr << "Error creating surface: " << SDL_GetError();
        SDL_DestroyRenderer(this->renderer);
        SDL_DestroyWindow(this->window);
        SDL_Quit();
        exit(1);
    }
    playerText = SDL_CreateTextureFromSurface(this->renderer, surface);

    SDL_SetWindowIcon(this->window, surface);

    SDL_FreeSurface(surface);

}

void Game::handleEvents() {
    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type) {
        case SDL_QUIT:
            this->isRunning = false;
            break;
        default:
            break;
    }
}

void Game::update() {

}

void Game::render() {
    SDL_RenderClear(this->renderer);

    // add stuff to render
    SDL_RenderCopy(this->renderer, playerText, nullptr, nullptr);


    SDL_RenderPresent(this->renderer);
}

void Game::clean() {
    SDL_DestroyWindow(this->window);
    SDL_DestroyRenderer(this->renderer);
    SDL_Quit();

    std::cout << "Game cleaned!" << std::endl;
}

void Game::saveData() {
    bool desktop = true;
    const char *saveFilePath = desktop ?
                               R"(C:\Users\Miles\Documents\GitHub\PokemonBattle\src\Data\SaveData.txt)" :
                               R"(C:\Users\Miles Youngblood\OneDrive\Documents\GitHub\PokemonBattle\src\Data\SaveData.txt)";
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

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < maps[i]->numNPCs(); ++i) {
            saveFile << '\n' << i << j << (*maps)[i][j].partySize();
            saveFile << (*maps)[i][j].getDirection();
        }
    }

    saveFile.close();
}

void Game::loadData() {

}

void Game::eraseData() {

}

Game::operator bool() const {
    return this->isRunning;
}
