//
// Created by Miles Youngblood on 12/12/2023.
//

#pragma once

#include "../../Graphic.h"

class Texture : public Graphic {
private:
    SDL_Texture *texture;

public:
    explicit Texture(const std::string &path);

    Texture(const std::string &text, SDL_Color fg);

    Texture(const Texture &) = delete;

    Texture(Texture &&toMove) noexcept;

    Texture &operator=(const Texture &) = delete;

    Texture &operator=(Texture &&rhs) noexcept;

    ~Texture() override;

    void update() override;

    void render() const override;

    [[nodiscard]] SDL_Texture *getTexture() const;
};
