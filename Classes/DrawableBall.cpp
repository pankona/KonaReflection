#include "DrawableBall.h"
#include <array>

DrawableBall::DrawableBall() {
    ball = new Ball();
}

Ball*
DrawableBall::getBall() {
    return ball;
}

DrawNode*
DrawableBall::getDrawNode() {
    return this->drawNode;
}

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
DrawableBall::updatePosition() {
    Position new_position = ball->getPosition();
    this->drawNode->setPosition(new_position.x, new_position.y);
}

