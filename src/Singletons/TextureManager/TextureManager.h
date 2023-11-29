//
// Created by Miles Youngblood on 10/8/2023.
//

#pragma once

#include <SDL_image.h>
#include <SDL_ttf.h>

// responsible for creating textures and drawing to the renderer
class TextureManager {
private:
    SDL_Renderer *textureRenderer{ nullptr };

    bool isInitialized{ false };

    TextureManager() = default;

public:
    static TextureManager &getInstance();

    void init(SDL_Renderer *renderer);

    /// \brief Loads a texture.
    /// \param path path of the image in the project
    /// \return a pointer to an SDL_Texture, or nullptr on error
    SDL_Texture *loadTexture(const char *path);

    /// \brief Loads a texture as a text.
    /// \param font font of text
    /// \param text text to load
    /// \param fg color of text
    /// \return a pointer to an SDL_Texture, or nullptr on error
    SDL_Texture *loadText(TTF_Font *font, const char *text, SDL_Color fg);

    /// \brief Loads a texture as a text.
    /// \param font font of text
    /// \param text text to load
    /// \param fg color of text
    /// \return a pointer to an SDL_Texture
    SDL_Texture *loadText(TTF_Font *font, std::string_view text, SDL_Color fg);

    /// \brief Draws a texture to the renderer.
    /// \param texture texture to be drawn
    /// \param dest destination on the screen
    void draw(SDL_Texture *texture, const SDL_Rect &dest);

    /// \brief Draws a frame of a sprite sheet to the renderer.
    /// \param texture texture to be drawn
    /// \param dest destination on the screen
    /// \param frame current frame
    /// \param row current row
    void drawFrame(SDL_Texture *texture, const SDL_Rect &dest, int frame, int row);

    /// \brief Draws an empty rectangle to the renderer.
    /// \param dest destination on the screen
    /// \param fg color of the lines
    /// \param pt border size
    void drawRect(const SDL_Rect &dest, SDL_Color fg, int pt);

    /// \brief Draws a filled rectangle with a border to the renderer.
    /// \param dest destination on the screen
    /// \param fg inner color
    /// \param bg color of the lines
    /// \param pt border size
    void drawRect(const SDL_Rect &dest, SDL_Color fg, SDL_Color bg, int pt);

    /// \brief Draws bordered text to the renderer.
    /// \param text text to draw
    /// \param x x position of the text (top left corner)
    /// \param y y position of the text (top left corner)
    /// \param pt size of the border
    /// \param fg text color
    /// \param bg border color
    /// \param font text font
    void drawBorderedText(const char *text, int x, int y, int pt, SDL_Color fg, SDL_Color bg, TTF_Font *font);

    /// \brief Draws outlined text to the renderer.
    /// \param text text to draw
    /// \param x x position of the text (top left corner)
    /// \param y y position of the text (top left corner)
    /// \param pt size of the border
    /// \param fg text color
    /// \param bg border color
    /// \param font text font
    void drawBorderedText(std::string_view text, int x, int y, int pt, SDL_Color fg, SDL_Color bg, TTF_Font *font);

    explicit operator bool() const;
};
