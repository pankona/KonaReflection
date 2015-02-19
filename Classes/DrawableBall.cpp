#include "DrawableBall.h"
#include <array>

// private methods

void
DrawableBall::createSprite() {
    Rect rect = Rect(0, 0, ball->getRadius(), ball->getRadius());
    sprite = Sprite::create();
    sprite->setTextureRect(rect);
    sprite->setColor(Color3B::RED);
    Position position = ball->getPosition();
    sprite->setPosition(position.x, position.y);
}

// public methods

DrawableBall::DrawableBall() {
    ball = new Ball();
    createSprite();
}

Ball*
DrawableBall::getBall() {
    return ball;
}

Sprite*
DrawableBall::getSprite() {
    return sprite;
}

void
DrawableBall::updatePosition() {
    Position new_position = ball->getPosition();
    sprite->setPosition(new_position.x, new_position.y);
}

