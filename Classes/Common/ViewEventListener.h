#ifndef __VIEWEVENTLISTENER_H__
#define __VIEWEVENTLISTENER_H__

#include "cocos2d.h"
#include "Position.h"

USING_NS_CC;

class ViewEventListener {
public:
    virtual void onTouchBegan(Node*, Position, void*) = 0;
    virtual void onTouchMoved(Node*, Position, void*) = 0;
    virtual void onTouchEnded(Node*, void*) = 0;
};

#endif /* __VIEWEVENTLISTENER_H__ */
