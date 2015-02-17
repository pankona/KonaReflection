#include "DrawableField.h"
#include <array>

DrawableField::DrawableField(Field *in_field) {
    field = in_field;
}

DrawNode*
DrawableField::getDrawNode() {
    return this->drawNode;
}

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

