//
// Created by Miles Youngblood on 10/25/2023.
//

#include "Game.h"

void Game::updateBattle() {

}

void Game::renderBattle() {
    int width;      // stores the text width
    int height;     // stores the text height

    static const int box_width = Constants::TILE_SIZE * 7;
    static const int box_height = Constants::TILE_SIZE * 2;
    static const SDL_Rect text_box{
            box_width / (Constants::TILE_SIZE / 10) / 2,
            this->WINDOW_HEIGHT - box_height,
            box_width / 2,
            box_height - Constants::TILE_SIZE / 2
    };

    TextureManager::getInstance().drawRect(text_box, { 0, 0, 0 }, text_box.h / (Constants::TILE_SIZE * 3 / 10));

    SDL_Rect button{
            WINDOW_WIDTH - Constants::TILE_SIZE / 10 - WINDOW_WIDTH / 4 + Constants::TILE_SIZE / 5,
            WINDOW_HEIGHT - Constants::TILE_SIZE / 2 - Constants::TILE_SIZE / 2,
            WINDOW_WIDTH / 4 - Constants::TILE_SIZE / 2,
            Constants::TILE_SIZE / 2
    };

    const int border_size = (WINDOW_WIDTH / 2 - (Constants::TILE_SIZE * 2 - Constants::TILE_SIZE / 2)) /
                            (Constants::TILE_SIZE * 3 / 10) / 5;

    // RUN
    TextureManager::getInstance().drawRect(button, { 0, 0, 255 }, { 0, 0, 0 }, border_size);

    // draw text
    TTF_SizeUTF8(this->font, "Run", &width, &height);
    TextureManager::getInstance().drawBorderedText("Run", button.x + button.w / 2 - width / 2,
                                                   button.y + button.h / 2 - height / 2, 2, { 255, 255, 255 },
                                                   { 0, 0, 0 }, this->font);

    // BAG
    // update button position
    button.y = button.y - button.h - static_cast<int>(button.y * 0.025);

    TextureManager::getInstance().drawRect(button, { 255, 255, 0 }, { 0, 0, 0 }, border_size);

    // draw text
    TTF_SizeUTF8(this->font, "Bag", &width, &height);
    TextureManager::getInstance().drawBorderedText("Bag", button.x + button.w / 2 - width / 2,
                                                   button.y + button.h / 2 - height / 2, 2, { 255, 255, 255 },
                                                   { 0, 0, 0 }, this->font);

    // FIGHT
    // update button position
    button.x = button.x - button.w - static_cast<int>(button.x * 0.025);

    TextureManager::getInstance().drawRect(button, { 255, 0, 0 }, { 0, 0, 0 }, border_size);

    TTF_SizeUTF8(this->font, "Fight", &width, &height);
    TextureManager::getInstance().drawBorderedText("Fight", button.x + button.w / 2 - width / 2,
                                                   button.y + button.h / 2 - height / 2, 2, { 255, 255, 255 },
                                                   { 0, 0, 0 }, this->font);

    // POKEMON
    // update button position
    button.y = WINDOW_HEIGHT - Constants::TILE_SIZE / 2 - Constants::TILE_SIZE / 2;

    TextureManager::getInstance().drawRect(button, { 0, 255, 0 }, { 0, 0, 0 }, border_size);

    TTF_SizeUTF8(this->font, "Pokemon", &width, &height);
    TextureManager::getInstance().drawBorderedText("Pokemon", button.x + button.w / 2 - width / 2,
                                                   button.y + button.h / 2 - height / 2, 2, { 255, 255, 255 },
                                                   { 0, 0, 0 }, this->font);

    SDL_SetRenderDrawColor(this->renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
}
