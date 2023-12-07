//
// Created by Miles on 11/6/2023.
//

#pragma once

class SoundPlayer {
public:
    static SoundPlayer &getInstance();

    SoundPlayer(const SoundPlayer &) = delete;

    SoundPlayer(SoundPlayer &&) noexcept = delete;

    SoundPlayer &operator=(const SoundPlayer &) = delete;

    SoundPlayer &operator=(SoundPlayer &&) noexcept = delete;

    ~SoundPlayer();

    void playSound(const char *name);

    void setFinishedCallback(void (*f)(int));

private:
    std::unordered_map<std::string, Mix_Chunk *> soundBoard;

    void (*finishedPlaying)(int){ nullptr };

    SoundPlayer();

    /// \brief Adds a sound to the soundboard.
    /// \name name of the sound
    void loadSound(const char *name);
};
