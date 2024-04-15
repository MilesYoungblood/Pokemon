//
// Created by Miles on 11/28/2023.
//

#include "../../../Singleton/DerivedClasses/Game/Game.h"
#include "Camera.h"

Camera::Camera() : view(0, 0, Game::WINDOW_WIDTH, Game::WINDOW_HEIGHT) {}

bool Camera::isInView(SDL_Rect rect) const {
    return SDL_HasIntersection(&rect, &this->view) == SDL_bool::SDL_TRUE;
}

void Camera::lockOnPlayer(Map &map) const {
    // x-distance of the player from the center of the screen
    const int x_from_center = ((this->view.w - Map::TILE_SIZE) / 2) -
                              Player::getPlayer().getMapPosition().getX() * Map::TILE_SIZE;
    // y-distance of the player from the center of the screen
    const int y_from_center = ((this->view.h - Map::TILE_SIZE) / 2) -
                              Player::getPlayer().getMapPosition().getY() * Map::TILE_SIZE;

    Player::getPlayer().getScreenPosition().translateX(x_from_center);
    Player::getPlayer().getScreenPosition().translateY(y_from_center);

    map.shiftHorizontally(x_from_center);
    map.shiftVertically(y_from_center);
}
