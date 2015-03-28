#include "DrawableCongrat.h"

// private methods

void
DrawableCongrat::createBaseLayer(int in_width, int in_height) {
    baseLayer = Layer::create();
    baseLayer->setPosition(0, 0);
}

// public methods

DrawableCongrat::DrawableCongrat(int in_width, int in_height) {
    createBaseLayer(in_width, in_height);

    // Label for congratulation
    Position position;
    position.x = in_width / 2;
    position.y = in_height * 7 / 10;
    dCongLabel = new DrawableLabel(position, "Congratulation!");
    baseLayer->addChild(dCongLabel->getLabel());

    // Label for next stage
    position.x = in_width / 2;
    position.y = in_height * 5 / 10;
    dNextStageLabel = new DrawableLabel(position, "Continue");
    baseLayer->addChild(dNextStageLabel->getLabel());

    // Label for back to title
    position.x = in_width / 2;
    position.y = in_height * 4 / 10;
    dBackToTitleLabel = new DrawableLabel(position, "End Game");
    dBackToTitleLabel->addViewEventListener(this);
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

    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(onTouchListener, baseLayer);
}

void
DrawableCongrat::removeViewEventListener(ViewEventListener* in_listener) {
    auto it = std::find(listeners.begin(), listeners.end(), in_listener);
    if (it != listeners.end()) {
        listeners.erase(it);
    }
}

void
DrawableCongrat::onTouchBegan(Node *in_node, Position in_position, void* in_arg) {
    // ToDo: need to distinguish from which label this event come.
    for (ViewEventListener* listener : listeners) {
        listener->onTouchBegan(in_node, in_position, NULL);
    }
}

void
DrawableCongrat::onTouchMoved(Node* in_node, Position in_position, void* in_arg) {
    // ToDo: need to distinguish from which label this event come.
    for (ViewEventListener* listener : listeners) {
        listener->onTouchMoved(in_node, in_position, NULL);
    }
}

void
DrawableCongrat::onTouchEnded(Node* in_node, void* in_arg) {
    // ToDo: need to distinguish from which label this event come.
    for (ViewEventListener* listener : listeners) {
        listener->onTouchEnded(in_node, NULL);
    }
}
