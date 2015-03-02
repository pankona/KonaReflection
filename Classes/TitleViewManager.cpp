#include "TitleViewManager.h"
#include "ViewManagerEventListener.h"
#include <stdio.h>

// private methods

void
TitleViewManager::eventNotify(ViewManagerEventListener::ViewManagerEvent in_event, void* arg) {
    for (ViewManagerEventListener* listener : listeners) {
        listener->onViewManagerEvent(in_event, arg);
    }
}

// public methods

void
TitleViewManager::initialize(Scene* in_baseScene) {
    baseScene = in_baseScene;
}

void
TitleViewManager::initializeTitle(int in_width, int in_height) {
    dTitle = new DrawableTitle(in_width, in_height);    
    dTitle->addViewEventListener(this);
    baseScene->addChild(dTitle->getSprite());
}

void
TitleViewManager::onTouchBegan(Position in_position) {
    eventNotify(ViewManagerEventListener::ViewManagerEvent::TOUCH_BEGAN, &in_position);
}

void
TitleViewManager::onTouchMoved(Position in_position) {
    eventNotify(ViewManagerEventListener::ViewManagerEvent::TOUCH_MOVED, &in_position);
}

void
TitleViewManager::onTouchEnded() {
    eventNotify(ViewManagerEventListener::ViewManagerEvent::TOUCH_ENDED, NULL);
}

void
TitleViewManager::addViewManagerEventListener(ViewManagerEventListener* in_listener) {
    listeners.push_back(in_listener);
}

void
TitleViewManager::removeViewManagerEventListener(ViewManagerEventListener* in_listener) {
    auto it = std::find(listeners.begin(), listeners.end(), in_listener);
    if (it != listeners.end()) {
        listeners.erase(it);
    }
}

