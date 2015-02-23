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
DrawableField::addViewEventListener(ViewEventListener *in_listener) {

    if (in_listener == NULL || sprite == NULL) {
        return;
    }

    listener = in_listener;

    auto onTouchListener = EventListenerTouchOneByOne::create();
    onTouchListener->onTouchBegan = [this](Touch* touch, Event* event) {
        Position p;
        p.x = touch->getLocation().x;
        p.y = touch->getLocation().y;
        listener->onTouchBegan(p);;
        return true;
    };

    onTouchListener->onTouchMoved = [this](Touch* touch, Event* event) {
        Position p;
        p.x = touch->getLocation().x;
        p.y = touch->getLocation().y;
        listener->onTouchMoved(p);
    };

    onTouchListener->onTouchEnded = [this](Touch* touch, Event* event) {
        listener->onTouchEnded();
    };

    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(onTouchListener, sprite);
}

