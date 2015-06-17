#include "ViewManager.h"
#include "ViewManagerEventListener.h"

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
    baseScene->addChild(dField->getNode());
}

void
ViewManager::initializeBall(int in_radius, Position in_initialPosition) {
    // ball configuration
    dBall = new DrawableBall(in_radius, in_initialPosition, "ball.png");
    baseScene->addChild(dBall->getSprite(), 100);
}

bool
ViewManager::hasCollisionWhileBarSwinging(DrawableBar* in_dBar, DrawableBall* in_dBall) {
    if (!isBarSwinging) {
        return false;
    }

    // FIXME: make function to calculate distance
    Position barPosition;
    barPosition.x = (int) in_dBar->getSprite()->getPosition().x;
    barPosition.y = (int) in_dBar->getSprite()->getPosition().y;

    Position ballPosition;
    ballPosition.x = (int) in_dBall->getSprite()->getPosition().x;
    ballPosition.y = (int) in_dBall->getSprite()->getPosition().y;

    int delta_x = std::abs(barPosition.x - ballPosition.x);
    int delta_y = std::abs(barPosition.y - ballPosition.y);

    int distance = std::sqrt(delta_x * delta_x + delta_y * delta_y);

    if (distance < in_dBar->getWidth() + in_dBall->getRadius()) {
        return true;
    }

    return false;

}

void
ViewManager::updateView() {
    if (dBall == NULL) {
        return;
    }

    Rect ballRect = dBall->getSprite()->getBoundingBox();
    Rect barRect = dBar->getSprite()->getBoundingBox();
    if (hasCollisionWhileBarSwinging(dBar, dBall)) {
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
ViewManager::onTouchBegan(Node *in_node, Position in_position, void* in_arg) {
    int* event = (int*) in_arg;

    if (dCongrat && in_node == dCongrat->getNode()) {

        switch (*event) {
            case DrawableCongrat::CongratEvent::BACK_TO_TITLE:
                eventNotify(ViewManagerEventListener::ViewManagerEvent::BACK_TO_TITLE, NULL);
                break;
            case DrawableCongrat::CongratEvent::GO_TO_NEXT_STAGE:
                eventNotify(ViewManagerEventListener::ViewManagerEvent::GO_TO_NEXT_STAGE, NULL);
                break;
            default:
                log ("[%s] event = unknonw.\n", __FILE__);
                break;
        }

        return;

    } else if (dGameOver && in_node == dGameOver->getNode()) {

        switch (*event) {
            case DrawableGameOver::GameOverEvent::BACK_TO_TITLE:
                eventNotify(ViewManagerEventListener::ViewManagerEvent::BACK_TO_TITLE, NULL);
                break;
            case DrawableGameOver::GameOverEvent::RETRY:
                eventNotify(ViewManagerEventListener::ViewManagerEvent::RETRY, NULL);
                break;
            default:
                log ("[%s] event = unknonw.\n", __FILE__);
                break;
        }

        return;

    }

    eventNotify(ViewManagerEventListener::ViewManagerEvent::TOUCH_BEGAN, &in_position);
}

void
ViewManager::onTouchMoved(Node* in_node, Position in_position, void* in_arg) {
    eventNotify(ViewManagerEventListener::ViewManagerEvent::TOUCH_MOVED, &in_position);
}

void
ViewManager::onTouchEnded(Node* in_node, void* in_arg) {
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
    if (dBall == NULL) {
        return;
    }
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
ViewManager::showCongratulation(int in_width, int in_height) {
    dCongrat = new DrawableCongrat(in_width, in_height);
    dCongrat->addViewEventListener(this);
    baseScene->addChild(dCongrat->getNode());
    // ToDo: free dCongrat
}

void
ViewManager::showGameOver(int in_width, int in_height) {
    dGameOver = new DrawableGameOver(in_width, in_height);
    dGameOver->addViewEventListener(this);
    baseScene->addChild(dGameOver->getNode());
    // ToDo: free dGameOver
}

void
ViewManager::setVerticalDrawDelta(int in_angle) {
    // TODO: Change pivot according to touched position
    dBar->setPivotLeft();
    dBar->setRotation(-1 * in_angle);
}

void
ViewManager::setIsBarSwinging(bool in_isBarSwinging) {
    isBarSwinging = in_isBarSwinging;
}
