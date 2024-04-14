//
// Created by Miles on 1/28/2024.
//

#pragma once

#include "../../Scene.h"
#include "../../../../../Stopwatch/Stopwatch.h"
#include "../../../../../Map/Map.h"

inline Stopwatch keyDelay;
inline bool momentum;

inline std::atomic_int entitiesUpdating = 0;

class Overworld : public Scene {
private:
    std::unique_ptr<Map> currentMap;

    std::mutex mutex;
    std::condition_variable cv;

    friend class Scene;

    Overworld() = default;

public:
    Overworld(const Overworld &) = delete;

    Overworld(Overworld &&) noexcept = delete;

    Overworld &operator=(const Overworld &) = delete;

    Overworld &operator=(Overworld &&) noexcept = delete;

    ~Overworld() override = default;

    void init();

    void handleEvents() override;

    void update() override;

    void render() override;

    void save();

    void changeMap(const std::tuple<int, int, std::string> &data);

    [[nodiscard]] Map &getCurrentMap() const;

    static void createTextBox(const std::string &message, const std::function<void()> &function = nullptr);

    static void createTextBox(const std::vector<std::string> &dialogue);

    void handleEscape();
};
