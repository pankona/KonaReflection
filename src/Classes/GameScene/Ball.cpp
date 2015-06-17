#include "Ball.h"

Ball::Ball() {
    position.x = 100;
    position.y = 100;
    radius = 12;
    vector.setAngle(60);
    vector.setLength(0);
}

void
Ball::setPosition(Position in_position) {
    position.x = in_position.x;
    position.y = in_position.y;
}

void
Ball::setPosition(int in_x, int in_y) {
    position.x = in_x;
    position.y = in_y;
}

Position
Ball::getPosition() {
    return position;
}

void
Ball::setDirection(int in_direction) {
    vector.setAngle(in_direction);
}

int
Ball::getDirection() {
    return vector.getAngle();
}

void
Ball::setSpeed(int in_speed) {
    vector.setLength(in_speed);
}

int
Ball::getSpeed() {
    return vector.getLength();
}

void
Ball::setRadius(int in_radius) {
    radius = in_radius;
}

int
Ball::getRadius() {
    return radius;
}

void
Ball::addVector(Kona::Vector in_vector) {
    vector += in_vector;
}

float
Ball::getSpeedX() {
    return vector.getTerminal().x;
}

float
Ball::getSpeedY() {
    return vector.getTerminal().y;
}

Kona::Vector&
Ball::getVector() {
    return vector;
}
