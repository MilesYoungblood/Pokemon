//
// Created by Miles on 11/28/2023.
//

#include "../../../Map/Map.h"
#include "Camera.h"

void Camera::init(int w, int h) {
    static bool isInitialized = false;
    // only allow this function to be called once
    if (not isInitialized) {
        this->view.w = w;
        this->view.h = h;

        isInitialized = true;
    }
}

bool Camera::isInView(const SDL_Rect &rect) const {
    return SDL_HasIntersection(&rect, &this->view) == SDL_bool::SDL_TRUE;
}

void Camera::lockOnPlayer(Map *map) const {
    // x-distance of the player from the center of the screen
    const int x_from_center = ((this->view.w - Constants::TILE_SIZE) / 2) -
                              Player::getPlayer().getX() * Constants::TILE_SIZE;
    // y-distance of the player from the center of the screen
    const int y_from_center = ((this->view.h - Constants::TILE_SIZE) / 2) -
                              Player::getPlayer().getY() * Constants::TILE_SIZE;

    Player::getPlayer().shiftHorizontally(x_from_center);
    Player::getPlayer().shiftVertically(y_from_center);

    map->shiftHorizontally(x_from_center);
    map->shiftVertically(y_from_center);
}
