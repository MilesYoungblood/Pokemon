//
// Created by Miles Youngblood on 4/14/2024.
//

#include "Resource.h"

Component::Resource::Resource(const int current, const int max) : current(current), max(max) {}

void Component::Resource::raise(const int x) {
    this->current = std::min(this->current + x, this->max);
}

void Component::Resource::lower(const int x) {
    this->current = std::max(0, this->current - x);
}

void Component::Resource::increaseMax(const int x) {
    this->max += x;
}

void Component::Resource::fill() {
    this->current = this->max;
}

int Component::Resource::getCurrent() const {
    return this->current;
}

int Component::Resource::getMax() const {
    return this->max;
}

bool Component::Resource::full() const {
    return this->current == this->max;
}

bool Component::Resource::empty() const {
    return this->current == 0;
}
