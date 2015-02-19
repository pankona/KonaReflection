#include "DrawableBar.h"
#include <array>

// private methods

void
DrawableBar::createSprite() {
    Rect rect = Rect(0, 0, bar->getWidth(), bar->getHeight());
    sprite = Sprite::create();
    sprite->setTextureRect(rect);
    sprite->setColor(Color3B::GREEN);
    Position position = bar->getPosition();
    sprite->setPosition(position.x, position.y);
}
// public methods

DrawableBar::DrawableBar() {
    bar = new Bar();
    createSprite();
}

Bar*
DrawableBar::getBar() {
    return bar;
}

Sprite*
DrawableBar::getSprite() {
    return sprite;
}

void
DrawableBar::updatePosition() {
    Position position = bar->getPosition();
    sprite->setPosition(position.x, position.y);
}
