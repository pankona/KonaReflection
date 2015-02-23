#include "DrawableBar.h"

// private methods

void
DrawableBar::createSprite(int in_width, int in_height) {
    Rect rect = Rect(0, 0, in_width, in_height);
    sprite = Sprite::create();
    sprite->setTextureRect(rect);
    sprite->setColor(Color3B::GREEN);
    sprite->setPosition(0, 0);
}
// public methods

DrawableBar::DrawableBar(int in_width, int in_height) {
    createSprite(in_width, in_height);
}

Sprite*
DrawableBar::getSprite() {
    return sprite;
}

void
DrawableBar::setPosition(Position p) {
    sprite->setPosition(p.x, p.y);
}
