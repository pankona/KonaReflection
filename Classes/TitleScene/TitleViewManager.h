#ifndef __TITLEVIEWMANAGER_H__
#define __TITLEVIEWMANAGER_H__

#include "cocos2d.h"
#include "ViewEventListener.h"
#include "ViewManagerEventListener.h"
#include "DrawableTitle.h"
#include "DrawableLabel.h"

USING_NS_CC;

class TitleViewManager : public ViewEventListener {
private:    
    std::vector<ViewManagerEventListener*> listeners;
    Scene* baseScene;
    void eventNotify(ViewManagerEventListener::ViewManagerEvent, void*);
    DrawableTitle* dTitle;
    DrawableLabel* dLabel;

public:
    void initialize(Scene* baseScene);
    void initializeTitle(int, int);
    void addViewManagerEventListener(ViewManagerEventListener*);
    void removeViewManagerEventListener(ViewManagerEventListener*);
    void onTouchBegan(Node*, Position, void*);
    void onTouchMoved(Node*, Position, void*);
    void onTouchEnded(Node*, void*);
};

#endif // __TITLEVIEWMANAGER_H__
