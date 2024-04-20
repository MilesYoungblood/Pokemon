//
// Created by Miles on 11/6/2023.
//

#pragma once

#include "../Singleton.h"

class Mixer final : public Singleton<Mixer> {
public:
    Mixer(const Mixer &) = delete;

    Mixer(Mixer &&) noexcept = delete;

    Mixer &operator=(const Mixer &) = delete;

    Mixer &operator=(Mixer &&) noexcept = delete;

    ~Mixer() override;

    void playSound(const char *id) const;

    void playMusic(const std::string &id);

private:
    std::unordered_map<std::string, Mix_Chunk *> soundboard;
    Mix_Music *music{ nullptr };

    friend class Singleton;

    Mixer();
};
