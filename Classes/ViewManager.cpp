#include "ViewManager.h"
#include <stdio.h>

// public methods

void
ViewManager::initialize(Scene* baseScene) {

}

void
ViewManager::initializeBar(int in_width, int in_height, Position in_initialPosition) {
    // bar configuration
    dBar = new DrawableBar(in_width, in_height, in_initialPosition);
    baseScene->addChild(dBar->getSprite());
}

void
ViewManager::initializeField(int in_width, int in_height, Position in_initialPosition) {
    // field configuration
    dField = new DrawableField(in_width, in_height, in_initialPosition);
    dField->setOnTouchCallback();
    baseScene->addChild(dField->getSprite());
}

void
ViewManager::initializeBall(int in_radius, Position in_initialPosition) {
    // ball configuration
    dBall = new DrawableBall(in_radius, in_initialPosition);
    baseScene->addChild(dBall->getSprite());
}

void
ViewManager::updateView() {
    Rect ballRect = dBall->getSprite()->getBoundingBox();
    Rect barRect = dBar->getSprite()->getBoundingBox();
    if (ballRect.intersectsRect(barRect)) {
        // ToDo: notify to game controller
        log ("ball and bar collistion detected.");
    }
}

void
ViewManager::setBallPosition(Position p) {
    dBall->setPosition(p);
}

void
ViewManager::setBarPosition(Position p) {
    dBar->setPosition(p);
}

void
ViewManager::onTouchBegan(int tag, Event* event, int, int) {
    log ("[VM] onTouchBegan.");
}

void
ViewManager::onTouchMoved(int tag, Event* event, int, int) {
    log ("[VM] onTouchMoved.");
}

void
ViewManager::onTouchEnded(int tag, Event* event) {
    log ("[VM] onTouchEnded.");
}
