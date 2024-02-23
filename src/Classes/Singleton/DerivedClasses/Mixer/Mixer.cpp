//
// Created by Miles on 11/28/2023.
//

#include "Mixer.h"

Mixer::~Mixer() {
    for (auto &mapping : this->soundboard) {
        Mix_FreeChunk(this->soundboard.at(mapping.first));
    }
    Mix_FreeMusic(this->music);
}

void Mixer::playSound(const char *name) {
    try {
        Mix_PlayChannel(-1, this->soundboard.at(name), 0);
        Mix_ChannelFinished(nullptr);
    }
    catch (const std::exception &e) {
        std::clog << "Error playing sound: " << e.what() << '\n';
    }
}

void Mixer::playMusic(const std::string &name) {
    Mix_FreeMusic(this->music);
    this->music = Mix_LoadMUS(std::string_view("../assets/audio/music/" + name + ".mp3").data());

    if (Mix_PlayMusic(this->music, -1) == -1) {
        std::clog << "Error playing music: " << SDL_GetError() << '\n';
        SDL_ClearError();
    }
}

Mixer::Mixer() {
    std::filesystem::path name;

    for (const auto &entry : std::filesystem::recursive_directory_iterator("../assets/audio/sfx/")) {
        name = entry.path();
        this->soundboard.insert(std::make_pair(name.stem().string(), Mix_LoadWAV(name.string().c_str())));
        if (this->soundboard.at(name.stem().string()) == nullptr) {
            std::clog << "Error loading sound: " << SDL_GetError() << '\n';
            SDL_ClearError();
        }
    }
}
