#include "Player.h"

// private methods


// public methods

Player::Player() {
    int DEFAULT_LIFE = 3;
    life = DEFAULT_LIFE;
}

Player::Player(int in_initialLife) {
    life = in_initialLife;
}

int
Player::getLife() {
    return life;
}

void
Player::setLife(int in_life) {
    life = in_life;
}

void
Player::DecreaseLife() {
    life--;
}

bool
Player::isStillAlive() {
    if (life <= 0) {
        return true;
    }
    return false;
}


