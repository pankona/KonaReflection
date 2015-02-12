#include "Ball.h"

Ball::Ball() {
    this->position.x = 50;
    this->position.y = 50;
    this->direction = 0;
    this->speed = 0;
    this->radius = 50;
}

void
Ball::setPosition(Position in_position) {
    this->position.x = in_position.x;
    this->position.y = in_position.y;
}

Position
Ball::getPosition() {
    return this->position;
}

void
Ball::setDirection(int direction) {
    this->direction = direction;
}

int
Ball::getDirection() {
    return this->direction;
}

void
Ball::setSpeed(int in_speed) {
    this->speed = in_speed;
}

int
Ball::getSpeed() {
    return this->speed;
}

void
Ball::setRadius(int in_radius) {
    this->radius = in_radius;
}

int
Ball::getRadius() {
    return this->radius;
}

