#include "DrawableCongrat.h"

// private methods

void
DrawableCongrat::createBaseLayer(int in_width, int in_height) {
    baseLayer = Layer::create();
    baseLayer->setPosition(0, 0);

    Size size(0,0);
    baseLayer->setContentSize(size);
}

// public methods

DrawableCongrat::DrawableCongrat(int in_width, int in_height) {
    createBaseLayer(in_width, in_height);

    // Label for congratulation
    Position position;
    position.x = in_width / 2;
    position.y = in_height * 7 / 10;
    dCongLabel = new DrawableLabel(position, "Congratulation!");
    baseLayer->addChild(dCongLabel->getNode());

    // Label for next stage
    position.x = in_width / 2;
    position.y = in_height * 5 / 10;
    dNextStageLabel = new DrawableLabel(position, "Continue");
    baseLayer->addChild(dNextStageLabel->getNode());

    // Label for back to title
    position.x = in_width / 2;
    position.y = in_height * 4 / 10;
    dBackToTitleLabel = new DrawableLabel(position, "End Game");
    dBackToTitleLabel->addViewEventListener(this);
    baseLayer->addChild(dBackToTitleLabel->getNode());
}

Node*
DrawableCongrat::getNode() {
    return baseLayer;
}

void
DrawableCongrat::onTouchBegan(Node *in_node, Position in_position, void* in_arg) {

    int eventShouldReturn;
    if (in_node == dBackToTitleLabel->getNode()) {
        eventShouldReturn = CongratEvent::BACK_TO_TITLE;
    } else if (in_node == dNextStageLabel->getNode()) {
        eventShouldReturn = CongratEvent::GO_TO_NEXT_STAGE;
    } else {
        log ("[%s] from = unknown.", __FILE__);
        return;
    }

    for (ViewEventListener* listener : listeners) {
        listener->onTouchBegan(getNode(), in_position, &eventShouldReturn);
    }
}

void
DrawableCongrat::onTouchMoved(Node* in_node, Position in_position, void* in_arg) {
    for (ViewEventListener* listener : listeners) {
        listener->onTouchMoved(getNode(), in_position, NULL);
    }
}

void
DrawableCongrat::onTouchEnded(Node* in_node, void* in_arg) {
    for (ViewEventListener* listener : listeners) {
        listener->onTouchEnded(getNode(), NULL);
    }
}
