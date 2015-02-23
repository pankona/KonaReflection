#include "DrawableField.h"

// private methods

void
DrawableField::createSprite(int in_width, int in_height) {
    Rect rect = Rect(0, 0, in_width, in_height);
    sprite = Sprite::create();
    sprite->setTextureRect(rect);
    sprite->setColor(Color3B::WHITE);
    sprite->setPosition(in_width / 2, in_height / 2);
}

// public methods

DrawableField::DrawableField(int in_width, int in_height) {
    createSprite(in_width, in_height);
}

Sprite*
DrawableField::getSprite() {
    return sprite;
}

void
DrawableField::setOnTouchCallback() {

    if (sprite == NULL) {
        return;
    }

    // temporary tag
    auto onTouchListener = EventListenerTouchOneByOne::create();
    onTouchListener->onTouchBegan = [this](Touch* touch, Event* event) {
        return true;
    };

    onTouchListener->onTouchMoved = [this](Touch* touch, Event* event) {
    };

    onTouchListener->onTouchEnded = [this](Touch* touch, Event* event) {
    };

    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(onTouchListener, sprite);
}
