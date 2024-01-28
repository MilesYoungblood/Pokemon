//
// Created by Miles on 11/6/2023.
//

#pragma once

#include "../../Singleton.h"

class Mixer : public Singleton<Mixer> {
public:
    Mixer(const Mixer &) = delete;

    Mixer(Mixer &&) noexcept = delete;

    Mixer &operator=(const Mixer &) = delete;

    Mixer &operator=(Mixer &&) noexcept = delete;

    ~Mixer() override;

    void playSound(const char *name);

    void playMusic(const char *name);

private:
    std::unordered_map<std::string, Mix_Chunk *> soundboard;
    std::unordered_map<std::string, Mix_Music *> playlist;

    friend class Singleton<Mixer>;

    Mixer();
};
