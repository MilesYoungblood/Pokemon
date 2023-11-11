//
// Created by Miles Youngblood on 10/25/2023.
//

#include "Game.h"

void Game::handleBattleEvents() {
    if (Game::event.type == SDL_QUIT) {
        Game::isRunning = false;
    }
}

void Game::updateBattle() {

}

void Game::renderTextWithOutline(const char *message, int x, int y, SDL_Color textColor) {
    SDL_Surface *textSurface = TTF_RenderUTF8_Solid(Game::font, message, textColor);
    if (textSurface == nullptr) {
        std::clog << "Error loading surface: " << SDL_GetError() << '\n';
        SDL_ClearError();
        Game::isRunning = false;
        return;
    }

    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(Game::renderer, textSurface);
    if (textTexture == nullptr) {
        std::clog << "Error loading texture: " << SDL_GetError() << '\n';
        SDL_ClearError();
        Game::isRunning = false;

        SDL_FreeSurface(textSurface);
        return;
    }

    // Render text with outline by rendering text multiple times with slight offsets
    SDL_Rect destRect(x, y, textSurface->w, textSurface->h);

    // Draw the outline first
    SDL_SetTextureColorMod(textTexture, 0, 0, 0);
    for (int dx = -1; dx <= 1; ++dx) {
        for (int dy = -1; dy <= 1; ++dy) {
            destRect.x = x + dx;
            destRect.y = y + dy;
            SDL_RenderCopy(Game::renderer, textTexture, nullptr, &destRect);
        }
    }

    // Reset color modulation for the actual text
    SDL_SetTextureColorMod(textTexture, textColor.r, textColor.g, textColor.b);
    destRect.x = x;
    destRect.y = y;
    SDL_RenderCopy(Game::renderer, textTexture, nullptr, &destRect);

    SDL_DestroyTexture(textTexture);
    SDL_FreeSurface(textSurface);
}

void Game::renderTextWithOutline(std::string_view message, int x, int y, SDL_Color textColor) {
    SDL_Surface *textSurface = TTF_RenderUTF8_Solid(Game::font, message.data(), textColor);
    if (textSurface == nullptr) {
        std::clog << "Error loading surface: " << SDL_GetError() << '\n';
        SDL_ClearError();
        Game::isRunning = false;
        return;
    }

    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(Game::renderer, textSurface);
    if (textTexture == nullptr) {
        std::clog << "Error loading texture: " << SDL_GetError() << '\n';
        SDL_ClearError();
        Game::isRunning = false;

        SDL_FreeSurface(textSurface);
        return;
    }

    // Render text with outline by rendering text multiple times with slight offsets
    SDL_Rect destRect(x, y, textSurface->w, textSurface->h);

    // Draw the outline first
    SDL_SetTextureColorMod(textTexture, 0, 0, 0);
    for (int dx = -1; dx <= 1; ++dx) {
        for (int dy = -1; dy <= 1; ++dy) {
            destRect.x = x + dx;
            destRect.y = y + dy;
            SDL_RenderCopy(Game::renderer, textTexture, nullptr, &destRect);
        }
    }

    // Reset color modulation for the actual text
    SDL_SetTextureColorMod(textTexture, textColor.r, textColor.g, textColor.b);
    destRect.x = x;
    destRect.y = y;
    SDL_RenderCopy(Game::renderer, textTexture, nullptr, &destRect);

    SDL_DestroyTexture(textTexture);
    SDL_FreeSurface(textSurface);
}

void Game::renderBattle() {
    int width;      // stores the text width
    int height;     // stores the text height

    SDL_Rect button{
            WINDOW_WIDTH - TILE_SIZE / 10 - WINDOW_WIDTH / 4 + TILE_SIZE / 5,
            WINDOW_HEIGHT - TILE_SIZE / 2 - TILE_SIZE / 2,
            WINDOW_WIDTH / 4 - TILE_SIZE / 2,
            TILE_SIZE / 2
    };

    const int border_size = (WINDOW_WIDTH / 2 - (TILE_SIZE * 2 - TILE_SIZE / 2)) / (TILE_SIZE * 3 / 10) / 5;

    // RUN
    TextureManager::getInstance().drawRectWithOutline(button, { 0, 0, 255 }, { 0, 0, 0 }, border_size);

    // draw text
    TTF_SizeUTF8(Game::font, "Run", &width, &height);
    Game::renderTextWithOutline("Run", button.x + button.w / 2 - width / 2, button.y + button.h / 2 - height / 2,
                                { 255, 255, 255 });

    // BAG
    // update button position
    button.y = button.y - button.h - static_cast<int>(button.y * 0.025);

    TextureManager::getInstance().drawRectWithOutline(button, { 255, 255, 0 }, { 0, 0, 0 }, border_size);

    // draw text
    TTF_SizeUTF8(Game::font, "Bag", &width, &height);
    Game::renderTextWithOutline("Bag", button.x + button.w / 2 - width / 2, button.y + button.h / 2 - height / 2,
                                { 255, 255, 255 });

    // FIGHT
    // update button position
    button.x = button.x - button.w - static_cast<int>(button.x * 0.025);

    TextureManager::getInstance().drawRectWithOutline(button, { 255, 0, 0 }, { 0, 0, 0 }, border_size);

    TTF_SizeUTF8(Game::font, "Fight", &width, &height);
    Game::renderTextWithOutline("Fight", button.x + button.w / 2 - width / 2, button.y + button.h / 2 - height / 2,
                                { 255, 255, 255 });

    // POKEMON
    // update button position
    button.y = WINDOW_HEIGHT - TILE_SIZE / 2 - TILE_SIZE / 2;

    TextureManager::getInstance().drawRectWithOutline(button, { 0, 255, 0 }, { 0, 0, 0 }, border_size);

    TTF_SizeUTF8(Game::font, "Pokemon", &width, &height);
    Game::renderTextWithOutline("Pokemon", button.x + button.w / 2 - width / 2, button.y + button.h / 2 - height / 2,
                                { 255, 255, 255 });

    SDL_SetRenderDrawColor(Game::renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
}
