#ifndef __VIEWEVENTLISTENER_H__
#define __VIEWEVENTLISTENER_H__

#include "Position.h"

class ViewEventListener {
public:
    virtual void onTouchBegan(Position) = 0;
    virtual void onTouchMoved(Position) = 0;
    virtual void onTouchEnded() = 0;
};

#endif /* __EVENTLISTENER_H__ */
