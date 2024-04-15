//
// Created by Miles on 11/28/2023.
//

#include "../../../Singleton/DerivedClasses/Game/Game.h"
#include "Camera.h"

bool Camera::isInView(const SDL_Rect rect) const {
    return SDL_HasIntersection(&rect, &this->view) == SDL_TRUE;
}

void Camera::lockOnPlayer(Map &map) const {
    // x-distance of the player from the center of the screen
    const int xFromCenter = ((this->view.w - Map::TILE_SIZE) / 2) -
                              Player::getPlayer().getMapPosition().getX() * Map::TILE_SIZE;
    // y-distance of the player from the center of the screen
    const int yFromCenter = ((this->view.h - Map::TILE_SIZE) / 2) -
                              Player::getPlayer().getMapPosition().getY() * Map::TILE_SIZE;

    Player::getPlayer().getScreenPosition().translateX(xFromCenter);
    Player::getPlayer().getScreenPosition().translateY(yFromCenter);

    map.shiftHorizontally(xFromCenter);
    map.shiftVertically(yFromCenter);
}

Camera::Camera() : view(0, 0, Game::WINDOW_WIDTH, Game::WINDOW_HEIGHT) {}
