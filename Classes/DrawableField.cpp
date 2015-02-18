#include "DrawableField.h"
#include <array>

// private methods

void
DrawableField::createDrawNode() {
    drawNode = DrawNode::create();
    drawNode->setPosition(0, 0);

    std::array<Point, 4> vertexes = {
        Point(0, 0),
        Point(field->getWidth(), 0),
        Point(field->getWidth(), field->getHeight()),
        Point(0, field->getHeight()),
    };
    float weight = 1.0f;
    drawNode->drawPolygon(vertexes.data(), vertexes.size(), Color4F::WHITE, weight, Color4F::WHITE);
}

void
DrawableField::prepareOnTouchListener() {
    if (drawNode == NULL) {
        return;
    }

    auto onTouchListener = EventListenerTouchOneByOne::create();
    onTouchListener->onTouchBegan = [this](Touch* touch, Event* event) {
        field->onTouch((int)touch->getLocation().x, (int)touch->getLocation().y);
        return true;
    };

    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(onTouchListener, drawNode);
}

// public methods

DrawableField::DrawableField(Field *in_field) {
    field = in_field;
    createDrawNode();
    prepareOnTouchListener();
}

DrawNode*
DrawableField::getDrawNode() {
    return drawNode;
}


