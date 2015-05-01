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
    currentPivot = Pivot::CENTER;
    width = in_width;
    height = in_height;
}

Sprite*
DrawableBar::getSprite() {
    return sprite;
}

void
DrawableBar::setPosition(Position p) {

    switch (currentPivot) {
        case LEFT:
            sprite->setPosition(p.x - width / 2, p.y);
            break;
        case RIGHT:
            sprite->setPosition(p.x + width / 2, p.y);
            break;
        case CENTER:
        default:
            sprite->setPosition(p.x, p.y);
            break;
    }
}


void
DrawableBar::setPivotLeft() {
    currentPivot = Pivot::LEFT;
    sprite->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
}

void
DrawableBar::setPivotRight() {
    currentPivot = Pivot::RIGHT;
    sprite->setAnchorPoint(Vec2::ANCHOR_MIDDLE_RIGHT);
}

void
DrawableBar::setRotation(int in_angle) {
    sprite->setRotation(in_angle);
}
