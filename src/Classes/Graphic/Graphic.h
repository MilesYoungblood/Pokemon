//
// Created by Miles Youngblood on 12/5/2023.
//

#pragma once

#include "../Singleton/DerivedClasses/TextureManager/TextureManager.h"

class Graphic {
private:
    bool active{ true };

public:
    Graphic() = default;

    Graphic(const Graphic &) = default;

    Graphic(Graphic &&) noexcept = default;

    Graphic &operator=(const Graphic &) = default;

    Graphic &operator=(Graphic &&) noexcept = default;

    virtual ~Graphic() = default;

    virtual void update() = 0;

    virtual void render() const = 0;

    void deactivate();

    [[nodiscard]] bool isActive() const;
};
