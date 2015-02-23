#include "DrawableBar.h"

// private methods

void
DrawableBar::createSprite(int in_width, int in_height, Position in_initPosition) {
    Rect rect = Rect(0, 0, in_width, in_height);
    sprite = Sprite::create();
    sprite->setTextureRect(rect);
    sprite->setColor(Color3B::GREEN);
    sprite->setPosition(in_initPosition.x, in_initPosition.y);
}
// public methods

DrawableBar::DrawableBar(int in_width, int in_height, Position in_initPosition) {
    createSprite(in_width, in_height, in_initPosition);
}

Sprite*
DrawableBar::getSprite() {
    return sprite;
}

void
DrawableBar::setPosition(Position p) {
    sprite->setPosition(p.x, p.y);
}
