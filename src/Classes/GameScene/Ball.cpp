#include "Ball.h"

Ball::Ball() : vector(Kona::Vector(0, 0), Kona::Point(0, 0)), radius(12) {
}

void
Ball::setPosition(Position in_position) {
    vector.setStartPosition(Kona::Point(in_position.x,
                                        in_position.y));
}

void
Ball::setPosition(float in_x, float in_y) {
    vector.setStartPosition(Kona::Point(in_x, in_y));
}

Position
Ball::getPosition() {
    Position p;
    p.x = vector.getStartPosition().x;
    p.y = vector.getStartPosition().y;
    return p;
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
    vector.setVector(vector.getVector() + in_vector);
}

float
Ball::getSpeedX() {
    return vector.getVector().getTerminal().x;
}

float
Ball::getSpeedY() {
    return vector.getVector().getTerminal().y;
}

Kona::Vector
Ball::getVector() {
    return vector.getVector();
}

Kona::Vector2D
Ball::getVector2D() {
    return vector;
}

void
Ball::setVector(Kona::Vector in_vector) {
    vector.setVector(in_vector);
}

bool
Ball::isTowardRight() {
    return vector.isTowardRight();
}

bool
Ball::isTowardLeft() {
    return vector.isTowardLeft();
}

bool
Ball::isTowardUp() {
    return vector.isTowardUp();
}

bool
Ball::isTowardDown() {
    return vector.isTowardDown();
}

Kona::Vector2D
Ball::getVector2DFromCircumference(DIRECTION in_direction) {
    Kona::Point startPosition;

    switch (in_direction) {
        case UP:
            startPosition.x = vector.getStartPosition().x;
            startPosition.y = vector.getStartPosition().y + radius;
            break;
        case DOWN:
            startPosition.x = vector.getStartPosition().x;
            startPosition.y = vector.getStartPosition().y - radius;
            break;
        case RIGHT:
            startPosition.x = vector.getStartPosition().x + radius;
            startPosition.y = vector.getStartPosition().y;
            break;
        case LEFT:
            startPosition.x = vector.getStartPosition().x - radius;
            startPosition.y = vector.getStartPosition().y;
            break;
        default:
            break;
    }

    return Kona::Vector2D(vector.getVector(), startPosition);
}

