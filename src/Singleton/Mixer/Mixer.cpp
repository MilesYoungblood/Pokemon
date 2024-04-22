//
// Created by Miles on 11/28/2023.
//

#include "Mixer.h"

#include <chrono>

Mixer::~Mixer() {
    for (const auto &id: this->soundboard | std::views::keys) {
        Mix_FreeChunk(this->soundboard.at(id));
    }
    Mix_FreeMusic(this->music);
}

Mixer & Mixer::getInstance() {
    static Mixer mixer;
    return mixer;
}

void Mixer::playSound(const char *id) const {
    try {
        Mix_PlayChannel(-1, this->soundboard.at(id), 0);
        Mix_ChannelFinished(nullptr);
    }
    catch (const std::exception &e) {
        std::clog << "Error playing sound: " << e.what() << '\n';
    }
}

void Mixer::playMusic(const std::string &id) {
    static std::string lastId;

    if (id == lastId) {
        return;
    }
    lastId = id;

    Mix_FreeMusic(this->music);
    this->music = Mix_LoadMUS(std::string_view("../assets/audio/music/" + id + ".mp3").data());

    if (Mix_PlayMusic(this->music, -1) == -1) {
        std::clog << "Error playing music: " << SDL_GetError() << '\n';
        SDL_ClearError();
    }
}

Mixer::Mixer() {
    for (const auto &entry : std::filesystem::recursive_directory_iterator("../assets/audio/sfx/")) {
        const std::filesystem::path& name = entry.path();
        this->soundboard.insert(std::make_pair(name.stem().string(), Mix_LoadWAV(name.string().c_str())));
        if (this->soundboard.at(name.stem().string()) == nullptr) {
            std::clog << "Error loading sound: " << SDL_GetError() << '\n';
            SDL_ClearError();
        }
    }
}
