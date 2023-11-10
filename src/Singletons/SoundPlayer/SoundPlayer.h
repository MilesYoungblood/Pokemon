//
// Created by Miles on 11/6/2023.
//

#pragma once

class SoundPlayer {
public:
    enum class SoundId {
        SELECTION, ACCEPT
    };

private:
    std::unordered_map<SoundPlayer::SoundId, Mix_Chunk *> soundBoard;

    void loadSound(SoundPlayer::SoundId id, const char *path) {
        this->soundBoard[id] = Mix_LoadWAV(std::string_view(PROJECT_PATH + "\\sfx\\" + path + ".wav").data());
        if (this->soundBoard.at(id) != nullptr) {
            std::cout << '\"' << path << "\" loaded!\n";
        }
        else {
            std::clog << "Error loading sound: " << SDL_GetError() << '\n';
            SDL_ClearError();
        }
    }

    SoundPlayer() {
        this->loadSound(SoundPlayer::SoundId::SELECTION, "selection");
        this->loadSound(SoundPlayer::SoundId::ACCEPT, "accept");
    }

public:
    static SoundPlayer &getInstance() {
        static SoundPlayer soundPlayer;
        return soundPlayer;
    }

    SoundPlayer(const SoundPlayer &) = delete;

    SoundPlayer(SoundPlayer &&) = delete;

    SoundPlayer &operator=(const SoundPlayer &) = delete;

    SoundPlayer &operator=(SoundPlayer &&) = delete;

    ~SoundPlayer() {
        Mix_FreeChunk(this->soundBoard[SoundPlayer::SoundId::SELECTION]);
        Mix_FreeChunk(this->soundBoard[SoundPlayer::SoundId::ACCEPT]);
    }

    void playSound(SoundPlayer::SoundId id) {
        Mix_PlayChannel(-1, this->soundBoard.at(id), 0);
        Mix_ChannelFinished(nullptr);
    }
};