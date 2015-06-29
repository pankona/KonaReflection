#include "Block.h"

Block::Block() {
    width = 0;
    height = 0;
    position.x = 0;
    position.y = 0;
    life = 0;
}

void
Block::setSize(int in_width, int in_height) {
    width = in_width;
    height = in_height;
}

int
Block::getWidth() {
    return width;
}

int
Block::getHeight() {
    return height;
}

void
Block::setPosition(Position in_position) {
    position.x = in_position.x;
    position.y = in_position.y;
}

void
Block::setPosition(int in_x, int in_y) {
    position.x = in_x;
    position.y = in_y;
}

Position
Block::getPosition() {
    return position;
}

void
Block::setLife(int in_life) {
    life = in_life;
}

int
Block::getLife() {
    return life;
}

void
Block::decreaseLife(int in_damage) {
    life -= in_damage;
    if (life < 0) {
        life = 0;
    }
}

bool
Block::stillAlive() {
    if (life == 0) {
        return false;
    }
    return true;
}

Kona::Vector2D
Block::getVector2DOfBlockSide(SIDE in_blockSide) {
    Kona::Point startPosition;
    Kona::Point endPosition;
    switch (in_blockSide) {
        case UPPER:
            startPosition.x = position.x - (width / 2);
            startPosition.y = position.y + (height / 2);
            endPosition.x   = position.x + (width / 2);
            endPosition.y   = position.y + (height / 2);
            break;
        case DOWNER:
            startPosition.x = position.x - (width / 2);
            startPosition.y = position.y - (height / 2);
            endPosition.x   = position.x + (width / 2);
            endPosition.y   = position.y - (height / 2);
            break;
        case RIGHTER:
            startPosition.x = position.x + (width / 2);
            startPosition.y = position.y - (height / 2);
            endPosition.x   = position.x + (width / 2);
            endPosition.y   = position.y + (height / 2);
            break;
        case LEFTER:
            startPosition.x = position.x - (width / 2);
            startPosition.y = position.y - (height / 2);
            endPosition.x   = position.x - (width / 2);
            endPosition.y   = position.y + (height / 2);
            break;
        default:
            break;
    }

    return Kona::Vector2D(startPosition, endPosition);
}

