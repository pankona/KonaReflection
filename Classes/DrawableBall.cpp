#include "DrawableBall.h"

// private methods

void
DrawableBall::createSprite(int in_radius) {
    Rect rect = Rect(0, 0, in_radius, in_radius);
    sprite = Sprite::create();
    sprite->setTextureRect(rect);
    sprite->setColor(Color3B::RED);
    sprite->setPosition(0, 0);
}

// public methods

DrawableBall::DrawableBall(int in_radius) {
    createSprite(in_radius);
}

Sprite*
DrawableBall::getSprite() {
    return sprite;
}

void
DrawableBall::setPosition(Position p) {
    sprite->setPosition(p.x, p.y);
}

