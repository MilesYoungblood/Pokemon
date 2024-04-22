//
// Created by Miles Youngblood on 12/5/2023.
//

#pragma once

class Graphic {
public:
    explicit Graphic(SDL_Rect dest);

    Graphic(const Graphic &) = default;

    Graphic(Graphic &&) noexcept = default;

    Graphic &operator=(const Graphic &) = default;

    Graphic &operator=(Graphic &&) noexcept = default;

    virtual ~Graphic() = default;

    virtual void update() = 0;

    virtual void render() const = 0;

    void setDest(SDL_Rect x);

    void setX(int x);

    void setY(int y);

    void setW(int w);

    void setH(int h);

    [[nodiscard]] SDL_Rect getDest() const;

    [[nodiscard]] int getX() const;

    [[nodiscard]] int getY() const;

    [[nodiscard]] int getW() const;

    [[nodiscard]] int getH() const;

    void deactivate();

    [[nodiscard]] bool isActive() const;

    Graphic() = default;

private:
    SDL_Rect dest{};
    bool active{ true };
};
