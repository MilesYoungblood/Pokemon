//
// Created by Miles Youngblood on 12/12/2023.
//

#pragma once

#include "../Graphic.h"

class Texture : public Graphic {
public:
    Texture() = default;

    Texture(const std::string &path, SDL_Rect dest);

    Texture(const std::string &text, SDL_Color fg, SDL_Rect dest);

    Texture(SDL_Texture *texture, SDL_Rect dest);

    Texture(const Texture &) = delete;

    Texture(Texture &&toMove) noexcept;

    Texture &operator=(const Texture &) = delete;

    Texture &operator=(Texture &&rhs) noexcept;

    ~Texture() override;

    void update() override;

    void render() const override;

    void clear();

    explicit operator SDL_Texture *&();

    explicit operator SDL_Texture *() const;

protected:
    explicit Texture(SDL_Rect dest);

private:
    SDL_Texture *texture{ nullptr };
};
