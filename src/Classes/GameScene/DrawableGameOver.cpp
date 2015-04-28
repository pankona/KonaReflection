#include "DrawableGameOver.h"

// private methods

void
DrawableGameOver::createBaseLayer(int in_width, int in_height) {
    baseLayer = Layer::create();
    baseLayer->setPosition(0, 0);

    Size size(0,0);
    baseLayer->setContentSize(size);
}

// public methods

DrawableGameOver::DrawableGameOver(int in_width, int in_height) {
    createBaseLayer(in_width, in_height);

    // Label for game over 
    Position position;
    position.x = in_width / 2;
    position.y = in_height * 7 / 10;
    dGameOverLabel = new DrawableLabel(position, "Game Over");
    baseLayer->addChild(dGameOverLabel->getNode());

    // Label for Retry same stage
    position.x = in_width / 2;
    position.y = in_height * 5 / 10;
    dRetryLabel = new DrawableLabel(position, "Retry");
    baseLayer->addChild(dRetryLabel->getNode());

    // Label for back to title
    position.x = in_width / 2;
    position.y = in_height * 4 / 10;
    dBackToTitleLabel = new DrawableLabel(position, "End Game");
    dBackToTitleLabel->addViewEventListener(this);
    baseLayer->addChild(dBackToTitleLabel->getNode());
}

Node*
DrawableGameOver::getNode() {
    return baseLayer;
}

void
DrawableGameOver::onTouchBegan(Node *in_node, Position in_position, void* in_arg) {

    int eventShouldReturn;
    if (in_node == dBackToTitleLabel->getNode()) {
        eventShouldReturn = GameOverEvent::BACK_TO_TITLE;
    } else if (in_node == dRetryLabel->getNode()) {
        eventShouldReturn = GameOverEvent::RETRY;
    } else {
        log ("[%s] from = unknown.", __FILE__);
        return;
    }

    for (ViewEventListener* listener : listeners) {
        listener->onTouchBegan(getNode(), in_position, &eventShouldReturn);
    }
}

void
DrawableGameOver::onTouchMoved(Node* in_node, Position in_position, void* in_arg) {
    for (ViewEventListener* listener : listeners) {
        listener->onTouchMoved(getNode(), in_position, NULL);
    }
}

void
DrawableGameOver::onTouchEnded(Node* in_node, void* in_arg) {
    for (ViewEventListener* listener : listeners) {
        listener->onTouchEnded(getNode(), NULL);
    }
}
