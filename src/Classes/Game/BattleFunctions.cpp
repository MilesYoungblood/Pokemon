//
// Created by Miles Youngblood on 10/25/2023.
//

#include "Game.h"

void Game::handleBattleEvents() {
    if (Game::event.type == SDL_EventType::SDL_QUIT) {
        Game::isRunning = false;
    }
}

void Game::updateBattle() {

}

void Game::renderBattle() {
    int width;      // stores the text width
    int height;     // stores the text height

    const static int box_width = TILE_SIZE * 7;
    const static int box_height = TILE_SIZE * 2;
    const static SDL_Rect text_box{
            box_width / (TILE_SIZE / 10) / 2,
            Game::WINDOW_HEIGHT - box_height,
            box_width / 2,
            box_height - TILE_SIZE / 2
    };

    TextureManager::getInstance().drawRect(text_box, { 0, 0, 0 }, text_box.h / (TILE_SIZE * 3 / 10));

    SDL_Rect button{
            WINDOW_WIDTH - TILE_SIZE / 10 - WINDOW_WIDTH / 4 + TILE_SIZE / 5,
            WINDOW_HEIGHT - TILE_SIZE / 2 - TILE_SIZE / 2,
            WINDOW_WIDTH / 4 - TILE_SIZE / 2,
            TILE_SIZE / 2
    };

    const int border_size = (WINDOW_WIDTH / 2 - (TILE_SIZE * 2 - TILE_SIZE / 2)) / (TILE_SIZE * 3 / 10) / 5;

    // RUN
    TextureManager::getInstance().drawRect(button, { 0, 0, 255 }, { 0, 0, 0 }, border_size);

    // draw text
    TTF_SizeUTF8(Game::font, "Run", &width, &height);
    TextureManager::getInstance().drawBorderedText("Run", button.x + button.w / 2 - width / 2,
                                                   button.y + button.h / 2 - height / 2, 2, { 255, 255, 255 },
                                                   { 0, 0, 0 }, Game::font);

    // BAG
    // update button position
    button.y = button.y - button.h - static_cast<int>(button.y * 0.025);

    TextureManager::getInstance().drawRect(button, { 255, 255, 0 }, { 0, 0, 0 }, border_size);

    // draw text
    TTF_SizeUTF8(Game::font, "Bag", &width, &height);
    TextureManager::getInstance().drawBorderedText("Bag", button.x + button.w / 2 - width / 2,
                                                   button.y + button.h / 2 - height / 2, 2, { 255, 255, 255 },
                                                   { 0, 0, 0 }, Game::font);

    // FIGHT
    // update button position
    button.x = button.x - button.w - static_cast<int>(button.x * 0.025);

    TextureManager::getInstance().drawRect(button, { 255, 0, 0 }, { 0, 0, 0 }, border_size);

    TTF_SizeUTF8(Game::font, "Fight", &width, &height);
    TextureManager::getInstance().drawBorderedText("Fight", button.x + button.w / 2 - width / 2,
                                                   button.y + button.h / 2 - height / 2, 2, { 255, 255, 255 },
                                                   { 0, 0, 0 }, Game::font);

    // POKEMON
    // update button position
    button.y = WINDOW_HEIGHT - TILE_SIZE / 2 - TILE_SIZE / 2;

    TextureManager::getInstance().drawRect(button, { 0, 255, 0 }, { 0, 0, 0 }, border_size);

    TTF_SizeUTF8(Game::font, "Pokemon", &width, &height);
    TextureManager::getInstance().drawBorderedText("Pokemon", button.x + button.w / 2 - width / 2,
                                                   button.y + button.h / 2 - height / 2, 2, { 255, 255, 255 },
                                                   { 0, 0, 0 }, Game::font);

    SDL_SetRenderDrawColor(Game::renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
}
