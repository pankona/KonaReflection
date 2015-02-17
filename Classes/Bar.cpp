#include "Bar.h"

Bar::Bar() {
    position.x = 100;
    position.y = 100;
    width = 100;
    height = 10;
}

void
Bar::setPosition(Position in_position) {
    position.x = in_position.x;
    position.y = in_position.y;
}

Position
Bar::getPosition() {
    return position;
}

void
Bar::setWidth(int in_width) {
    width = in_width;
}

int
Bar::getWidth() {
    return width;
}

void
Bar::setHeight(int in_height) {
    height = in_height;
}

int
Bar::getHeight() {
    return height;
}