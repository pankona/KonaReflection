#include "DrawableCongrat.h"

// private methods

void
DrawableCongrat::createBaseLayer(int in_width, int in_height) {
    baseLayer = Layer::create();
    baseLayer->setPosition(in_width / 2, in_height / 2);
}

// public methods

DrawableCongrat::DrawableCongrat(int in_width, int in_height) {
    createBaseLayer(in_width, in_height);

    // Label for congratulation
    Position position;
    position.x = in_width / 2;
    position.y = in_height * 4 / 4;
    dCongLabel = new DrawableLabel(position, "Congratulation!");
    baseLayer->addChild(dCongLabel->getLabel());

    // Label for next stage
    position.x = in_width / 2;
    position.y = in_height * 2 / 4;
    dNextStageLabel = new DrawableLabel(position, "Continue");
    baseLayer->addChild(dNextStageLabel->getLabel());

    // Label for back to title
    position.x = in_width / 2;
    position.y = in_height * 1 / 4;
    dBackToTitleLabel = new DrawableLabel(position, "End Game");
    baseLayer->addChild(dBackToTitleLabel->getLabel());
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


