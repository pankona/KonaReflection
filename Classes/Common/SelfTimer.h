#ifndef __TIMER_H__
#define __TIMER_H__

#include "cocos2d.h"
#include "SelfTimer.h"
#include "SelfTimerListener.h"

USING_NS_CC;

class SelfTimer {

private:    
    Node* node;
    int delayTime;
    int eventDescriptor;
    std::vector<SelfTimerListener*> listeners;
    void eventNotify();

public:
    SelfTimer(int, int);
    void addSelfTimerListener(SelfTimerListener*);
    void run();
};

#endif // __TIMER_H__
