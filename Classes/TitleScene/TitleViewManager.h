#ifndef __TITLEVIEWMANAGER_H__
#define __TITLEVIEWMANAGER_H__

#include "cocos2d.h"
#include "ViewEventListener.h"
#include "ViewManagerEventListener.h"
#include "DrawableTitle.h"

USING_NS_CC;

class TitleViewManager : public ViewEventListener {
private:    
    std::vector<ViewManagerEventListener*> listeners;
    Scene* baseScene;
    void eventNotify(ViewManagerEventListener::ViewManagerEvent, void*);
    DrawableTitle *dTitle;

public:
    void initialize(Scene* baseScene);
    void initializeTitle(int, int);
    void addViewManagerEventListener(ViewManagerEventListener*);
    void removeViewManagerEventListener(ViewManagerEventListener*);
    void onTouchBegan(Position);
    void onTouchMoved(Position);
    void onTouchEnded();
};

#endif // __TITLEVIEWMANAGER_H__
