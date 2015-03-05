#include "ViewManager.h"
#include "ViewManagerEventListener.h"
#include <stdio.h>

// private methods

void
ViewManager::eventNotify(ViewManagerEventListener::ViewManagerEvent in_event, void* arg) {
    for (ViewManagerEventListener* listener : listeners) {
        listener->onViewManagerEvent(in_event, arg);
    }
}

// public methods

void
ViewManager::initialize(Scene* in_baseScene) {
    baseScene = in_baseScene;
}

void
ViewManager::initializeBar(int in_width, int in_height, Position in_initialPosition) {
    // bar configuration
    dBar = new DrawableBar(in_width, in_height, in_initialPosition);
    baseScene->addChild(dBar->getSprite());
}

void
ViewManager::initializeField(int in_width, int in_height) {
    // field configuration
    dField = new DrawableField(in_width, in_height);
    dField->addViewEventListener(this);
    baseScene->addChild(dField->getSprite());
}

void
ViewManager::initializeBall(int in_radius, Position in_initialPosition) {
    // ball configuration
    dBall = new DrawableBall(in_radius, in_initialPosition);
    baseScene->addChild(dBall->getSprite(), 100);
}

void
ViewManager::updateView() {
    if (dBall == NULL) {
        return;
    }

    Rect ballRect = dBall->getSprite()->getBoundingBox();
    Rect barRect = dBar->getSprite()->getBoundingBox();
    if (ballRect.intersectsRect(barRect)) {
        eventNotify(ViewManagerEventListener::ViewManagerEvent::BALL_AND_BAR_COLLISION, NULL);
    }

    int blockNum = dBlocks.size();
    for (int i = 0; i < blockNum; i++) {
        DrawableBlock* block = dBlocks.at(i);
        if (!block->isStillAlive()) {
            continue;
        }
        Rect blockRect = block->getSprite()->getBoundingBox();
        if (ballRect.intersectsRect(blockRect)) {
            eventNotify(ViewManagerEventListener::ViewManagerEvent::BALL_AND_BLOCK_COLLISION, &i);
        }
    }
}

void
ViewManager::setBallPosition(Position p) {
    if (dBall == NULL) {
        return;
    }
    dBall->setPosition(p);
}

void
ViewManager::setBarPosition(Position p) {
    dBar->setPosition(p);
}

void
ViewManager::onTouchBegan(Position in_position) {
    eventNotify(ViewManagerEventListener::ViewManagerEvent::TOUCH_BEGAN, &in_position);
}

void
ViewManager::onTouchMoved(Position in_position) {
    eventNotify(ViewManagerEventListener::ViewManagerEvent::TOUCH_MOVED, &in_position);
}

void
ViewManager::onTouchEnded() {
    eventNotify(ViewManagerEventListener::ViewManagerEvent::TOUCH_ENDED, NULL);
}

void
ViewManager::addViewManagerEventListener(ViewManagerEventListener* in_listener) {
    listeners.push_back(in_listener);
}

void
ViewManager::removeViewManagerEventListener(ViewManagerEventListener* in_listener) {
    auto it = std::find(listeners.begin(), listeners.end(), in_listener);
    if (it != listeners.end()) {
        listeners.erase(it);
    }
}

void
ViewManager::addBlock(int in_width, int in_height, Position in_position) {
    DrawableBlock* dBlock = new DrawableBlock(in_width, in_height, in_position);
    baseScene->addChild(dBlock->getSprite());
    dBlocks.push_back(dBlock);
}

void
ViewManager::setBlockColor(int index, Color3B in_color) {
    DrawableBlock* dBlock = dBlocks.at(index);
    if (dBlock == NULL) {
        return;
    }
    dBlock->setColor(in_color);
}

void
ViewManager::markBlockAsKilled(int in_index) {
    DrawableBlock *dBlock = dBlocks.at(in_index);
    dBlock->markAsKilled();
}

void
ViewManager::removeBall() {
    baseScene->removeChild(dBall->getSprite());
    dBall = NULL;
}

void
ViewManager::setTimer(int in_delay, int in_event_desc) {
    SelfTimer* timer = new SelfTimer(in_delay, in_event_desc);
    timer->addSelfTimerListener(this);
    timers.push_back(timer);
    baseScene->addChild(timer->getNode());
    timer->run();
}

void
ViewManager::onTimerExpired(int in_eventDescriptor) {
    eventNotify(ViewManagerEventListener::ViewManagerEvent::TIMER_EXPIRED, &in_eventDescriptor);
}

void
ViewManager::showConguratulation(Position in_p) {
    dCongurat = new DrawableCongurat(in_p.x, in_p.y);
    baseScene->addChild(dCongurat->getLayer());
    // ToDo: free dCongurat
}
