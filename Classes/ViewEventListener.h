#ifndef __VIEWEVENTLISTENER_H__
#define __VIEWEVENTLISTENER_H__

class ViewEventListener {
public:
    enum EventTag {
        ON_TOUCH_BEGAN,
        ON_TOUCH_MOVED,
        ON_TOUCH_ENDED
    };
    virtual void onEvent(EventTag) = 0;
};

#endif /* __EVENTLISTENER_H__ */
