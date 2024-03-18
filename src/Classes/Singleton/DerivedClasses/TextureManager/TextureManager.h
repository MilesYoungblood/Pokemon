//
// Created by Miles Youngblood on 10/8/2023.
//

#pragma once

#include "../../Singleton.h"

/// \brief responsible for creating textures and drawing to the renderer
class TextureManager : public Singleton<TextureManager> {
private:
    SDL_Renderer *textureRenderer{ nullptr };

    TTF_Font *font{ nullptr };

    bool isInitialized{ false };

    friend class Singleton<TextureManager>;

    TextureManager() = default;

public:
    enum : Uint8 {
        FONT_SIZE = 20
    };

    TextureManager(const TextureManager &) = default;

    TextureManager(TextureManager &&) noexcept = default;

    TextureManager &operator=(const TextureManager &) = default;

    TextureManager &operator=(TextureManager &&) noexcept = default;

    ~TextureManager() override;

    /// \brief initializes the class
    /// \param renderer the renderer of the Game class
    /// \return true upon successful initialization and false otherwise
    bool init(SDL_Renderer *renderer);

    /// \brief destructs the class
    void clean();

    /// \brief Loads a texture.
    /// \param path path of the image in the project
    /// \return a pointer to an SDL_Texture, or nullptr on error
    SDL_Texture *loadTexture(const std::string &path);

    /// \brief Loads a texture, as well as the dimensions of it
    /// \param path path of the image in the project
    /// \return a tuple containing SDL_Texture (nullptr on error), and two Uint8's representing the height and width respectively
    std::tuple<SDL_Texture *, Uint32, Uint32> loadTextureData(const std::string &path);

    std::tuple<SDL_Texture *, int, int> loadTextData(std::string_view text, SDL_Color fg, int wLength);

    /// \brief Loads a texture as a text.
    /// \param text text to load
    /// \param fg color of text
    /// \return a pointer to an SDL_Texture, or nullptr on error
    SDL_Texture *loadText(const char *text, SDL_Color fg);

    /// \brief Loads a texture as a text.
    /// \param text text to load
    /// \param fg color of text
    /// \return a pointer to an SDL_Texture
    SDL_Texture *loadText(std::string_view text, SDL_Color fg);

    /// \brief Draws a texture to the renderer.
    /// \param texture texture to be drawn
    /// \param dest destination on the screen
    void draw(SDL_Texture *texture, const SDL_Rect &dest);

    /// \brief Draws a frame of a sprite sheet to the renderer.
    /// \param texture texture to be drawn
    /// \param dest destination on the screen
    /// \param col current column
    /// \param row current row
    void drawFrame(SDL_Texture *texture, const SDL_Rect &dest, int col, int row);

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
    void drawBorderedText(const char *text, int x, int y, int pt, SDL_Color fg, SDL_Color bg);

    /// \brief Draws outlined text to the renderer.
    /// \param text text to draw
    /// \param x x position of the text (top left corner)
    /// \param y y position of the text (top left corner)
    /// \param pt size of the border
    /// \param fg text color
    /// \param bg border color
    void drawBorderedText(std::string_view text, int x, int y, std::optional<int> maxW, std::optional<int> maxH, int pt, SDL_Color fg, SDL_Color bg);

    /// \brief returns the class's font.
    /// \return returns a pointer to the class's font.
    [[nodiscard]] TTF_Font *getFont() const;

    explicit operator bool() const;
};
