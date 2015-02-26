#include "Ball.h"

Ball::Ball() {
    position.x = 100;
    position.y = 100;
    radius = 25;
    direction = 60;
    speed = 10;
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
    direction = in_direction;
}

int
Ball::getDirection() {
    return direction;
}

void
Ball::setSpeed(int in_speed) {
    speed = in_speed;
}

int
Ball::getSpeed() {
    return speed;
}

void
Ball::setRadius(int in_radius) {
    radius = in_radius;
}

int
Ball::getRadius() {
    return radius;
}

