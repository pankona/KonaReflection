#ifndef __VIEWMANAGEREVENTLISTERN_H__
#define __VIEWMANAGEREVENTLISTERN_H__

class ViewManagerEventListener {
public:
     enum ViewManagerEvent {
        TOUCH_BEGAN,
        TOUCH_MOVED,
        TOUCH_ENDED,
        BALL_AND_BAR_COLLISION,
        BALL_AND_BLOCK_COLLISION,
        BACK_TO_TITLE,
        GO_TO_NEXT_STAGE,
        RETRY,
        TIMER_EXPIRED
    };

   virtual void onViewManagerEvent(ViewManagerEvent, void*) = 0;
};

#endif /* __VIEWMANAGEREVENTLISTERN_H__ */
