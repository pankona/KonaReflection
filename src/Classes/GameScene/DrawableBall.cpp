#include "DrawableBall.h"

// private methods

void
DrawableBall::createSprite(int in_radius, Position in_initPosition, std::string in_imageResourcePath) {
    radius = in_radius;
    if (in_imageResourcePath == "") {
        sprite = Sprite::create();
        Rect rect = Rect(0, 0, in_radius * 2, in_radius * 2);
        sprite->setColor(Color3B::RED);
        sprite->setTextureRect(rect);
    } else {
        sprite = Sprite::create(in_imageResourcePath);
        Size img_size = sprite->getContentSize();
        sprite->setScale((in_radius * 2) / img_size.width, (in_radius * 2) / img_size.height);
    }
    sprite->setPosition(in_initPosition.x, in_initPosition.y);
}

// public methods

DrawableBall::DrawableBall(int in_radius, Position in_initPosition) {
    createSprite(in_radius, in_initPosition, "");
}

DrawableBall::DrawableBall(int in_radius, Position in_initPosition, std::string in_imageResourcePath) {
    createSprite(in_radius, in_initPosition, in_imageResourcePath);
}

Sprite*
DrawableBall::getSprite() {
    return sprite;
}

void
DrawableBall::setPosition(Position p) {
    sprite->setPosition(p.x, p.y);
}

int
DrawableBall::getRadius() {
    return radius;
}
