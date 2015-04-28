#include "DrawableTitle.h"
#include "Position.h"

// private methods

void
DrawableTitle::createSprite(int in_width, int in_height) {
    Rect rect = Rect(0, 0, in_width, in_height);
    sprite = Sprite::create();
    sprite->setTextureRect(rect);
    sprite->setColor(Color3B::WHITE);
    sprite->setPosition(in_width / 2, in_height / 2);
}

// public methods

DrawableTitle::DrawableTitle(int in_width, int in_height) {
    createSprite(in_width, in_height);
}

Node*
DrawableTitle::getNode() {
    return sprite;
}


