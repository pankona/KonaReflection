#ifndef __VIEWEVENTLISTENER_H__
#define __VIEWEVENTLISTENER_H__

#include "cocos2d.h"
#include "Position.h"

USING_NS_CC;

class ViewEventListener {
public:
    virtual void onTouchBegan(Node*, Position) = 0;
    virtual void onTouchMoved(Node*, Position) = 0;
    virtual void onTouchEnded(Node*) = 0;
};

#endif /* __EVENTLISTENER_H__ */
