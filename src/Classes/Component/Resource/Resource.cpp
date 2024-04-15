//
// Created by Miles Youngblood on 4/14/2024.
//

#include "Resource.h"

Project::Resource::Resource(const int current, const int max) : current(current), max(max) {}

void Project::Resource::raise(const int x) {
    this->current = std::min(this->current + x, this->max);
}

void Project::Resource::lower(const int x) {
    this->current = std::max(0, this->current - x);
}

void Project::Resource::increaseMax(const int x) {
    this->max += x;
}

void Project::Resource::fill() {
    this->current = this->max;
}

int Project::Resource::getCurrent() const {
    return this->current;
}

int Project::Resource::getMax() const {
    return this->max;
}

bool Project::Resource::empty() const {
    return this->current == 0;
}
