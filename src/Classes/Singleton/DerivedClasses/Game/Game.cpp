//
// Created by Miles on 10/2/2023.
//

#include "../Mixer/Mixer.h"
#include "../KeyManager/KeyManager.h"
#include "../Pokedex/Pokedex.h"
#include "Game.h"

Game::Game() {
    // initialize subsystems
    if (SDL_InitSubSystem(SDL_INIT_TIMER | SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0) {
        std::clog << "Error initializing subsystems: " << SDL_GetError() << '\n';
        SDL_ClearError();
        return;
    }

    // create window
    this->window = SDL_CreateWindow("Pokémon", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                    Game::WINDOW_WIDTH, Game::WINDOW_HEIGHT, 0);
    if (this->window == nullptr) {
        std::clog << "Error creating window: " << SDL_GetError() << '\n';
        SDL_ClearError();
        return;
    }

    // initialize image subsystems
    if (IMG_Init(IMG_InitFlags::IMG_INIT_PNG) == 0) {
        std::clog << "Error initializing image subsystems: " << SDL_GetError() << '\n';
        SDL_ClearError();
        return;
    }

    // load window icon
    SDL_Surface *pokeball = IMG_Load("../assets/images/pokeball.png");
    if (pokeball == nullptr) {
        std::clog << "Error loading icon: " << SDL_GetError() << '\n';
        SDL_ClearError();
        return;
    }

    // set the window icon
    SDL_SetWindowIcon(this->window, pokeball);
    SDL_FreeSurface(pokeball);

    // create renderer
    this->renderer = SDL_CreateRenderer(this->window, -1, 0);
    if (this->renderer == nullptr) {
        std::clog << "Error creating renderer: " << SDL_GetError() << '\n';
        SDL_ClearError();
        return;
    }
    SDL_SetRenderDrawColor(this->renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

    // initialize true type font subsystems
    if (TTF_Init() == -1) {
        std::clog << "Error initializing TTF subsystems: " << SDL_GetError() << '\n';
        SDL_ClearError();
        return;
    }

    // initialize TextureManager
    if (not TextureManager::getInstance().init(this->renderer)) {
        return;
    }

    // initialize audio
    if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096) == -1) {
        std::clog << "Error opening the default audio device: " << SDL_GetError() << '\n';
        SDL_ClearError();
        return;
    }

    Mixer::getInstance().playMusic("TitleScreen");

    // instantiate KeyManager
    KeyManager::getInstance();

    this->running = true;
}

Game::~Game() {
    Mix_HaltMusic();
    Mix_HookMusicFinished(nullptr);
    Mix_CloseAudio();

    TextureManager::getInstance().clean();
    TTF_Quit();

    IMG_Quit();

    if (this->renderer != nullptr) {
        SDL_DestroyRenderer(this->renderer);
        if (strlen(SDL_GetError()) > 0) {
            std::clog << "Unable to destroy renderer: " << SDL_GetError() << '\n';
            SDL_ClearError();
        }
    }
    if (this->window != nullptr) {
        SDL_DestroyWindow(this->window);
        if (strlen(SDL_GetError()) > 0) {
            std::clog << "Unable to destroy window: " << SDL_GetError() << '\n';
            SDL_ClearError();
        }
    }
    SDL_Quit();
}

void Game::handleEvents() {
    this->currentScene->handleEvents();
}

void Game::update() {
    this->currentScene->update();
}

void Game::render() const {
    SDL_RenderClear(this->renderer);
    this->currentScene->render();
    SDL_RenderPresent(this->renderer);
}

void Game::terminate() {
    this->running = false;
}

int Game::getFps() const {
    return this->currentFps;
}

bool Game::isRunning() const {
    return this->running;
}

void Game::setRenderColor(SDL_Color color) {
    SDL_SetRenderDrawColor(this->renderer, color.r, color.g, color.b, color.a);
}

void Game::changeScene(Scene::Id id) {
    this->currentScene = this->scenes.at(static_cast<std::size_t>(id));
}
