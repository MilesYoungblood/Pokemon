//
// Created by Miles on 11/6/2023.
//

#pragma once

#include <SDL_mixer.h>

class SoundPlayer {
public:
    enum class SoundId {
        SELECTION, ACCEPT
    };

    static SoundPlayer &getInstance();

    SoundPlayer(const SoundPlayer &) = delete;

    SoundPlayer(SoundPlayer &&) noexcept = delete;

    SoundPlayer &operator=(const SoundPlayer &) = delete;

    SoundPlayer &operator=(SoundPlayer &&) noexcept = delete;

    ~SoundPlayer();

    void playSound(SoundPlayer::SoundId id);

private:
    std::unordered_map<SoundPlayer::SoundId, Mix_Chunk *> soundBoard;

    SoundPlayer();

    /// \brief Adds a sound to the soundboard.
    /// \param id id of the sound
    /// \param path path of the sound
    void loadSound(const SoundPlayer::SoundId id, const std::string &path);
};
