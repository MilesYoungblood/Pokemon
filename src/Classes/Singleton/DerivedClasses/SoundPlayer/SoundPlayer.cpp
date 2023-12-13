//
// Created by Miles on 11/28/2023.
//

#include "SoundPlayer.h"

SoundPlayer::~SoundPlayer() {
    Mix_FreeChunk(this->soundBoard["accept"]);
    Mix_FreeChunk(this->soundBoard["bump"]);
    Mix_FreeChunk(this->soundBoard["select"]);
    Mix_FreeChunk(this->soundBoard["spotted"]);
}

void SoundPlayer::playSound(const char *name) {
    try {
        Mix_PlayChannel(-1, this->soundBoard.at(name), 0);
        Mix_ChannelFinished(this->finishedPlaying);
    }
    catch (const std::exception &e) {
        std::clog << "Error playing sound: " << e.what() << '\n';
    }
}

void SoundPlayer::setFinishedCallback(void (*f)(int)) {
    this->finishedPlaying = f;
}

SoundPlayer::SoundPlayer() {
    this->loadSound("accept");
    this->loadSound("bump");
    this->loadSound("select");
    this->loadSound("spotted");
}

void SoundPlayer::loadSound(const char *name) {
    this->soundBoard.insert(std::make_pair(name, Mix_LoadWAV(
            std::string_view(std::string("../assets/audio/sfx/") + name + ".wav").data())));
    if (this->soundBoard.at(name) == nullptr) {
        std::clog << "Error loading sound: " << SDL_GetError() << '\n';
        SDL_ClearError();
    }
}
