#include "DrawableLabel.h"
#include "Position.h"

// private methods

void
DrawableLabel::createLabel(Position in_p, std::string in_text) {
    label = Label::createWithSystemFont(in_text, "HiraKakuProN-W6", 48);
    label->setPosition(in_p.x, in_p.y);
    label->setColor(Color3B::BLACK);
}

// public methods

DrawableLabel::DrawableLabel(Position in_p, std::string in_text) {
    createLabel(in_p, in_text);
}

Label*
DrawableLabel::getLabel() {
    return label;
}

void
DrawableLabel::addViewEventListener(ViewEventListener* in_listener) {

    listeners.push_back(in_listener);

    auto onTouchListener = EventListenerTouchOneByOne::create();
    onTouchListener->onTouchBegan = [this](Touch* touch, Event* event) {
        auto target = (Sprite*)event->getCurrentTarget();
        Rect targetBox = target->getBoundingBox();
        Point touchedPoint;
        touchedPoint = Vec2(touch->getLocation().x, touch->getLocation().y);
        if (!targetBox.containsPoint(touchedPoint)) {
            return false;
        }

        Position p;
        p.x = (int) touch->getLocation().x;
        p.y = (int) touch->getLocation().y;
        for (ViewEventListener* listener : listeners) {
            listener->onTouchBegan(event->getCurrentTarget(), p, NULL);
        }
        return true;
    };

    onTouchListener->onTouchMoved = [this](Touch* touch, Event* event) {
        Position p;
        p.x = (int) touch->getLocation().x;
        p.y = (int) touch->getLocation().y;
        for (ViewEventListener* listener : listeners) {
            listener->onTouchMoved(event->getCurrentTarget(), p, NULL);
        }
    };

    onTouchListener->onTouchEnded = [this](Touch* touch, Event* event) {
        for (ViewEventListener* listener : listeners) {
            listener->onTouchEnded(event->getCurrentTarget(), NULL);
        }
    };

    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(onTouchListener, label);
}

void
DrawableLabel::removeViewEventListener(ViewEventListener* in_listener) {
    auto it = std::find(listeners.begin(), listeners.end(), in_listener);
    if (it != listeners.end()) {
        listeners.erase(it);
    }
}


