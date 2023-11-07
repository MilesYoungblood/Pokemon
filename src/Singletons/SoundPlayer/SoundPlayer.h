//
// Created by Miles on 11/6/2023.
//

#pragma once

enum SoundId {
    ACCEPT
};

class SoundPlayer {
private:
    std::unordered_map<SoundId, Mix_Chunk *> soundBoard;

    void loadSound(SoundId id, const char *path) {
        this->soundBoard[id] = Mix_LoadWAV(std::string_view(PROJECT_PATH + "\\sfx\\" + path).data());
        if (this->soundBoard.at(id) != nullptr) {
            std::cout << "Sound loaded!\n";
        }
        else {
            std::cerr << "Error loading sound: " << SDL_GetError() << '\n';
            SDL_ClearError();
        }
    }

    SoundPlayer() {
        loadSound(SoundId::ACCEPT, "selection.wav");
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
        Mix_FreeChunk(this->soundBoard[SoundId::ACCEPT]);
    }

    void playSound(SoundId id) {
        Mix_PlayChannel(-1, this->soundBoard.at(id), 0);
        Mix_ChannelFinished(nullptr);
    }
};