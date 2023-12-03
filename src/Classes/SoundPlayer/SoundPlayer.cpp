//
// Created by Miles on 11/28/2023.
//

#include "SoundPlayer.h"

SoundPlayer &SoundPlayer::getInstance() {
    static SoundPlayer soundPlayer;
    return soundPlayer;
}

SoundPlayer::~SoundPlayer() {
    Mix_FreeChunk(this->soundBoard[SoundPlayer::SoundId::SELECTION]);
    Mix_FreeChunk(this->soundBoard[SoundPlayer::SoundId::ACCEPT]);
}

void SoundPlayer::playSound(SoundPlayer::SoundId id) {
    Mix_PlayChannel(-1, this->soundBoard.at(id), 0);
    Mix_ChannelFinished(nullptr);
}

SoundPlayer::SoundPlayer() {
    this->loadSound(SoundPlayer::SoundId::SELECTION, "selection");
    this->loadSound(SoundPlayer::SoundId::ACCEPT, "accept");
}

void SoundPlayer::loadSound(const SoundPlayer::SoundId id, const std::string &path) {
    this->soundBoard.insert(std::make_pair(id, Mix_LoadWAV(
            std::string_view("../assets/audio/sfx/" + path + ".wav").data())));
    if (this->soundBoard.at(id) == nullptr) {
        std::clog << "Error loading sound: " << SDL_GetError() << '\n';
        SDL_ClearError();
        std::terminate();
    }
}
