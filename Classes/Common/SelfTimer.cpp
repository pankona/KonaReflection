#include "SelfTimer.h"

// private methods

void
SelfTimer::eventNotify() {
    for (SelfTimerListener* listener : listeners) {
        listener->onTimerExpired(eventDescriptor);
    }
}


// public methods

SelfTimer::SelfTimer(int in_delayTime, int in_eventDescriptor) {
    node = Node::create();
    delayTime = in_delayTime;
    eventDescriptor = in_eventDescriptor;
}

void
SelfTimer::run() {
    node->runAction(Sequence::create(DelayTime::create(delayTime),
                    CallFunc::create([this]() {
                        eventNotify();
                    }), NULL));
    
}

void
SelfTimer::addSelfTimerListener(SelfTimerListener* in_listener) {
    listeners.push_back(in_listener);
}

