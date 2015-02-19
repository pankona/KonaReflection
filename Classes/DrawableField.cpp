#include "DrawableField.h"
#include <array>

#include <stdio.h>

// private methods

void
DrawableField::createSprite() {
    Rect rect = Rect(0, 0, field->getWidth(), field->getHeight());
    sprite = Sprite::create();
    sprite->setTextureRect(rect);
    sprite->setColor(Color3B::WHITE);
    sprite->setPosition(field->getWidth() / 2 , field->getHeight() / 2);
}

void
DrawableField::prepareOnTouchListener() {
    if (sprite == NULL) {
        return;
    }

    auto onTouchListener = EventListenerTouchOneByOne::create();
    onTouchListener->onTouchBegan = [this](Touch* touch, Event* event) {
        log ("x = %d, y = %d", (int)touch->getLocation().x, (int)touch->getLocation().y);
        field->onTouchBegan((int)touch->getLocation().x, (int)touch->getLocation().y);
        return true;
    };

    onTouchListener->onTouchEnded = [this](Touch* touch, Event* event) {
        field->onTouchEnded();
    };

    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(onTouchListener, sprite);
}

// public methods

DrawableField::DrawableField(Field *in_field) {
    field = in_field;
    createSprite();
    prepareOnTouchListener();
}

Sprite*
DrawableField::getSprite() {
    return sprite;
}


