#include "DrawableCongrat.h"

// private methods

void
DrawableCongrat::createBaseLayer(int in_width, int in_height) {
    Rect rect = Rect(0, 0, in_width, in_height);
    baseLayer = Layer::create();
    //baseLayer->setTextureRect(rect);
    //baseLayer->setColor(Color3B::BLACK);
    baseLayer->setPosition(in_width / 2, in_height / 2);
}

// public methods

DrawableCongrat::DrawableCongrat(int in_width, int in_height) {
    createBaseLayer(in_width, in_height);

    Position congPosition;
    congPosition.x = in_width / 2;
    congPosition.y = in_height * 2 / 3;
    dCongLabel = new DrawableLabel(congPosition, "Congratulation!");
    baseLayer->addChild(dCongLabel->getLabel());
}

Layer*
DrawableCongrat::getLayer() {
    return baseLayer;
}

void
DrawableCongrat::addViewEventListener(ViewEventListener* in_listener) {

    listeners.push_back(in_listener);

    auto onTouchListener = EventListenerTouchOneByOne::create();
    onTouchListener->onTouchBegan = [this](Touch* touch, Event* event) {
        Position p;
        p.x = touch->getLocation().x;
        p.y = touch->getLocation().y;
        for (ViewEventListener* listener : listeners) {
            listener->onTouchBegan(p);
        }
        return true;
    };

    onTouchListener->onTouchMoved = [this](Touch* touch, Event* event) {
        Position p;
        p.x = touch->getLocation().x;
        p.y = touch->getLocation().y;
        for (ViewEventListener* listener : listeners) {
            listener->onTouchMoved(p);
        }
    };

    onTouchListener->onTouchEnded = [this](Touch* touch, Event* event) {
        for (ViewEventListener* listener : listeners) {
            listener->onTouchEnded();
        }
    };

    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(onTouchListener, baseLayer);
}

void
DrawableCongrat::removeViewEventListener(ViewEventListener* in_listener) {
    auto it = std::find(listeners.begin(), listeners.end(), in_listener);
    if (it != listeners.end()) {
        listeners.erase(it);
    }
}


