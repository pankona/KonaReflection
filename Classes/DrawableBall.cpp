#include "DrawableBall.h"
#include <array>

// private methods

void
DrawableBall::createDrawNode() {
    drawNode = DrawNode::create();
    Position position = ball->getPosition();
    drawNode->setPosition(position.x, position.y);
    int radius = ball->getRadius();

    std::array<Point, 4> vertexes = {
        Point(0, 0),
        Point(radius, 0),
        Point(radius, radius),
        Point(0, radius),
    };
    float weight = 1.0f;
    drawNode->drawPolygon(vertexes.data(), vertexes.size(), Color4F::WHITE, weight, Color4F::RED);
}

void
DrawableBall::createSprite() {
    Rect rect = Rect(0, 0, ball->getRadius(), ball->getRadius());
    sprite = Sprite::create();
    sprite->setTextureRect(rect);
    sprite->setColor(Color3B::RED);
    Position position = ball->getPosition();
    sprite->setPosition(position.x, position.y);
}

// public methods

DrawableBall::DrawableBall() {
    ball = new Ball();
    //createDrawNode();
    createSprite();
}

Ball*
DrawableBall::getBall() {
    return ball;
}

DrawNode*
DrawableBall::getDrawNode() {
    return drawNode;
}

Sprite*
DrawableBall::getSprite() {
    return sprite;
}

void
DrawableBall::updatePosition() {
    Position new_position = ball->getPosition();
    //drawNode->setPosition(new_position.x, new_position.y);
    sprite->setPosition(new_position.x, new_position.y);
}

