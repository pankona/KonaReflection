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
DrawableField::addViewEventListener(ViewEventListener* in_listener) {

    listeners.push_back(in_listener);

    auto onTouchListener = EventListenerTouchOneByOne::create();
    onTouchListener->onTouchBegan = [this](Touch* touch, Event* event) {
        Position p;
        p.x = (int) touch->getLocation().x;
        p.y = (int) touch->getLocation().y;
        for (ViewEventListener* listener : listeners) {
            listener->onTouchBegan(event->getCurrentTarget(), p);
        }
        return true;
    };

    onTouchListener->onTouchMoved = [this](Touch* touch, Event* event) {
        Position p;
        p.x = (int) touch->getLocation().x;
        p.y = (int) touch->getLocation().y;
        for (ViewEventListener* listener : listeners) {
            listener->onTouchMoved(event->getCurrentTarget(), p);
        }
    };

    onTouchListener->onTouchEnded = [this](Touch* touch, Event* event) {
        for (ViewEventListener* listener : listeners) {
            listener->onTouchEnded(event->getCurrentTarget());
        }
    };

    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(onTouchListener, sprite);
}

void
DrawableField::removeViewEventListener(ViewEventListener* in_listener) {
    auto it = std::find(listeners.begin(), listeners.end(), in_listener);
    if (it != listeners.end()) {
        listeners.erase(it);
    }
}


