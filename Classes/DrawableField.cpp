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
DrawableField::createSprite() {
    Rect rect = Rect(0, 0, field->getWidth(), field->getHeight());
    sprite = Sprite::create();
    sprite->setTextureRect(rect);
    sprite->setColor(Color3B::WHITE);
    sprite->setPosition(0, 0);
}

void
DrawableField::prepareOnTouchListener() {
    if (drawNode == NULL) {
        return;
    }

    auto onTouchListener = EventListenerTouchOneByOne::create();
    onTouchListener->onTouchBegan = [this](Touch* touch, Event* event) {
        field->onTouchBegan((int)touch->getLocation().x, (int)touch->getLocation().y);
        return true;
    };

    onTouchListener->onTouchEnded = [this](Touch* touch, Event* event) {
        field->onTouchEnded();
    };

    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(onTouchListener, drawNode);
}

// public methods

DrawableField::DrawableField(Field *in_field) {
    field = in_field;
    //createDrawNode();
    createSprite();
    prepareOnTouchListener();
}

DrawNode*
DrawableField::getDrawNode() {
    return drawNode;
}

Sprite*
DrawableField::getSprite() {
    return sprite;
}


