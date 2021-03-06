#include "Bar.h"
#include <iostream>

// public methods

Bar::Bar() {
    position.x = 100;
    position.y = 100;
    width = 100;
    height = 10;
    direction = BarDirection::NONE;
    speed = 10;
    angle = 0;
    currentPivot = LEFT;
    is_swinging = false;
}

void
Bar::setPosition(Position in_position) {
    position.x = in_position.x;
    position.y = in_position.y;
}

void
Bar::setPosition(int in_x, int in_y) {
    position.x = in_x;
    position.y = in_y;
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

void
Bar::setSpeed(int in_speed) {
    speed = in_speed;
}

int
Bar::getSpeed() {
    return speed;
}

void
Bar::setDirection(BarDirection in_direction) {
    direction = (int) in_direction;
}

BarDirection
Bar::getDirection() {
    return (BarDirection) direction;
}


void
Bar::setAngle(int in_angle) {
    angle = in_angle;
}

int
Bar::getAngle() {
    return angle;
}

void
Bar::setPivot(Pivot in_pivot) {
    currentPivot = in_pivot;
}

Bar::Pivot
Bar::getPivot() {
    return currentPivot;
}

bool
Bar::isSwinging() {
    return is_swinging;
}

void
Bar::startSwinging() {
    is_swinging = true;
}

void
Bar::endSwinging() {
    is_swinging = false;
    angle = 0;
}

Kona::Vector2D
Bar::getVector2DOfBarSide(SIDE in_barSide) {
    // ToDo: implement
    return Kona::Vector2D();
}

Kona::Vector2D
Bar::getVector2DOfBar() {
    Kona::Point startPosition;
    Kona::Point TerminalPosition;

    if (currentPivot == LEFT) {
        startPosition = Kona::Point(position.x - width / 2, position.y);
        return Kona::Vector2D(Kona::Vector(width, angle), startPosition);
    } else if (currentPivot == RIGHT) {
    } else {
    }
    std::cout << "[" << __func__ << "][" << __LINE__ << "] should not reach here!" << std::endl;
    return Kona::Vector2D();
}

