#include "DrawableBlock.h"

// private methods

void
DrawableBlock::createSprite(int in_width, int in_height, Position in_initPosition) {
    Rect rect = Rect(0, 0, in_width, in_height);
    sprite = Sprite::create();
    sprite->setTextureRect(rect);
    sprite->setColor(Color3B::BLUE);
    sprite->setPosition(in_initPosition.x, in_initPosition.y);
}

// public methods

DrawableBlock::DrawableBlock(int in_width, int in_height, Position in_initPosition) {
    createSprite(in_width, in_height, in_initPosition);
}

Sprite*
DrawableBlock::getSprite() {
    return sprite;
}

void
DrawableBlock::setPosition(Position p) {
    sprite->setPosition(p.x, p.y);
}

void
DrawableBlock::setColor(Color3B in_color) {
    sprite->setColor(in_color);
}