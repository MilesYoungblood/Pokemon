//
// Created by Miles on 11/28/2023.
//

#include "Mixer.h"

Mixer::~Mixer() {
    for (auto &mapping : this->soundboard) {
        Mix_FreeChunk(this->soundboard.at(mapping.first));
    }
    for (auto &mapping : this->playlist) {
        Mix_FreeMusic(this->playlist.at(mapping.first));
    }
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
    try {
        Mix_PlayMusic(this->playlist.at(name), -1);
    }
    catch (const std::exception &e) {
        std::clog << "Error playing music: " << e.what() << '\n';
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
    for (const auto &entry : std::filesystem::recursive_directory_iterator("../assets/audio/music/")) {
        name = entry.path();
        this->playlist.insert(std::make_pair(name.stem().string(), Mix_LoadMUS(name.string().c_str())));
        if (this->playlist.at(name.stem().string()) == nullptr) {
            std::clog << "Error loading music: " << SDL_GetError() << '\n';
            SDL_ClearError();
        }
    }
}
