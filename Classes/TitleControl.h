#ifndef __TITLECONTROL_H__
#define __TITLECONTROL_H__

#include "cocos2d.h"
#include "TitleViewManager.h"
#include "ViewManagerEventListener.h"

USING_NS_CC;

class TitleControl : public ViewManagerEventListener {
private:
    TitleViewManager tvm;
public:
    void initialize(Scene*);
    void onViewManagerEvent(ViewManagerEventListener::ViewManagerEvent, void*);
};

#endif // __TITLECONTROL_H__
