#include "DrawableBall.h"

// private methods

void
DrawableBall::createSprite(int in_radius, Position in_initPosition) {
    Rect rect = Rect(0, 0, in_radius * 2, in_radius * 2);
    sprite = Sprite::create();
    sprite->setTextureRect(rect);
    sprite->setColor(Color3B::RED);
    sprite->setPosition(in_initPosition.x, in_initPosition.y);
}

// public methods

DrawableBall::DrawableBall(int in_radius, Position in_initPosition) {
    createSprite(in_radius, in_initPosition);
}

Sprite*
DrawableBall::getSprite() {
    return sprite;
}

void
DrawableBall::setPosition(Position p) {
    sprite->setPosition(p.x, p.y);
}

