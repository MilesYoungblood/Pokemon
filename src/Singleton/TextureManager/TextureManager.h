//
// Created by Miles Youngblood on 10/8/2023.
//

#pragma once

#include "../../Graphic/Texture/Texture.h"

/// \brief responsible for creating textures and drawing to the renderer
class TextureManager {
public:
    enum : Uint8 {
        FONT_SIZE = 20
    };

    TextureManager(const TextureManager &) = default;

    TextureManager(TextureManager &&) noexcept = default;

    TextureManager &operator=(const TextureManager &) = default;

    TextureManager &operator=(TextureManager &&) noexcept = default;

    ~TextureManager();

    /// \brief Getter for Singleton instance
    /// \return the TextureManager instance
    static TextureManager &getInstance();

    /// \brief Initializes the class
    /// \param renderer the renderer of the Game class
    /// \return true upon successful initialization and false otherwise
    bool init(SDL_Renderer *renderer);

    /// \brief Destructs the class
    void clean();

    /// \brief Loads a texture
    /// \param path path of the image in the project
    /// \return a pointer to an SDL_Texture, or nullptr on error
    [[nodiscard]] SDL_Texture *loadTexture(const std::string &path) const;

    /// \brief Loads a texture as wrapped text
    /// \param text text to load
    /// \param fg color of text
    /// \param wLength wrap length
    /// \return a point to an SDL_Texture
    [[nodiscard]] SDL_Texture *loadWrappedText(const std::string &text, SDL_Color fg, int wLength) const;

    /// \brief Loads a texture as a text
    /// \param text text to load
    /// \param fg color of text
    /// \return a pointer to an SDL_Texture
    [[nodiscard]] SDL_Texture *loadText(const std::string &text, SDL_Color fg) const;

    /// \brief Draws a texture to the renderer
    /// \param texture texture to be drawn
    /// \param dest destination on the screen
    void draw(SDL_Texture *texture, SDL_Rect dest) const;

    /// \brief Draws a frame of a sprite sheet to the renderer
    /// \param texture texture to be drawn
    /// \param dest destination on the screen
    /// \param col current column
    /// \param row current row
    void drawFrame(SDL_Texture *texture, SDL_Rect dest, int col, int row) const;

    /// \brief Draws an empty rectangle to the renderer
    /// \param dest destination on the screen
    /// \param fg color of the lines
    /// \param pt border size
    void drawRect(SDL_Rect dest, SDL_Color fg, int pt) const;

    /// \brief Draws a filled rectangle with a border to the renderer
    /// \param dest destination on the screen
    /// \param fg inner color
    /// \param bg color of the lines
    /// \param pt border size
    void drawRect(SDL_Rect dest, SDL_Color fg, SDL_Color bg, int pt) const;

    /// \brief Draws outlined text to the renderer
    /// \param text text to draw
    /// \param pt size of the border
    /// \param fg text color
    /// \param bg border color
    void drawBorderedText(const Texture &text, int pt, SDL_Color fg, SDL_Color bg) const;

    /// \brief Draws the black screen to the renderer
    void drawScreen() const;

    /// \brief Darkens the screen
    void darken();

    /// \brief Brightens the screen
    void brighten();

    /// \brief Setter for screen color
    /// \param r red
    /// \param g green
    /// \param b blue
    void setScreenColor(Uint8 r, Uint8 g, Uint8 b);

    /// \brief Setter for screen opacity
    /// \param alpha alpha level
    void setScreenOpacity(Uint8 alpha);

    /// \brief Checker for full screen opaqueness
    /// \return true if the screen is fully opaque
    [[nodiscard]] bool isScreenOpaque() const;

    /// \brief Checker for full screen transparency
    /// \return true if the screen in fully transparent
    [[nodiscard]] bool isScreenTransparent() const;

    explicit operator bool() const;

private:
    SDL_Renderer *textureRenderer{ nullptr };

    TTF_Font *font{ nullptr };

    SDL_Color screenColor{ 0, 0, 0, SDL_ALPHA_TRANSPARENT };

    bool isInitialized{ false };

    TextureManager() = default;
};
