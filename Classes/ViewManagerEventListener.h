#ifndef __VIEWMANAGEREVENTLISTERN_H__
#define __VIEWMANAGEREVENTLISTERN_H__

class ViewManagerEventListener {
public:
     enum ViewManagerEvent {
        TOUCH_BEGAN,
        TOUCH_MOVED,
        TOUCH_ENDED,
        BAR_AND_BALL_COLLISION
    };

   virtual void onViewManagerEvent(ViewManagerEvent, void*) = 0;
};

#endif /* __VIEWMANAGEREVENTLISTERN_H__ */
