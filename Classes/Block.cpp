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