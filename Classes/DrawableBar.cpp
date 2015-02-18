#include "DrawableBar.h"
#include <array>

// private methods

void
DrawableBar::createDrawNode() {

    drawNode = DrawNode::create();
    Position position = bar->getPosition();
    drawNode->setPosition(position.x, position.y);

    std::array<Point, 4> vertexes = {
        Point(0, 0),
        Point(bar->getWidth(), 0),
        Point(bar->getWidth(), bar->getHeight()),
        Point(0, bar->getHeight()),
    };
    float weight = 1.0f;
    drawNode->drawPolygon(vertexes.data(), vertexes.size(), Color4F::GREEN, weight, Color4F::GREEN);
}

void
DrawableBar::createSprite() {
    Rect rect = Rect(0, 0, bar->getWidth(), bar->getHeight());
    sprite = Sprite::create();
    sprite->setTextureRect(rect);
    sprite->setColor(Color3B::GREEN);
    Position position = bar->getPosition();
    sprite->setPosition(position.x, position.y);
}
// public methods

DrawableBar::DrawableBar() {
    bar = new Bar();
    //createDrawNode();
    createSprite();
}

Bar*
DrawableBar::getBar() {
    return bar;
}

DrawNode*
DrawableBar::getDrawNode() {
    return drawNode;
}

Sprite*
DrawableBar::getSprite() {
    return sprite;
}

void
DrawableBar::updatePosition() {
    Position position = bar->getPosition();
    drawNode->setPosition(position.x, position.y);
}
