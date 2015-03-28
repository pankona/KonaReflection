#ifndef __VIEWMANAGER_H__
#define __VIEWMANAGER_H__

#include "cocos2d.h"
#include "Position.h"
#include "DrawableBall.h"
#include "DrawableField.h"
#include "DrawableBar.h"
#include "DrawableBlock.h"
#include "DrawableCongrat.h"
#include "SelfTimer.h"
#include "SelfTimerListener.h"
#include "ViewEventListener.h"
#include "ViewManagerEventListener.h"

USING_NS_CC;

class ViewManager : public ViewEventListener, public SelfTimerListener {
private:    
    std::vector<ViewManagerEventListener*> listeners;
    std::vector<SelfTimer*> timers;
    Scene* baseScene;
    DrawableBall* dBall;
    DrawableField* dField;
    DrawableBar* dBar;
    DrawableCongrat* dCongrat;
    std::vector<DrawableBlock*> dBlocks;
    void eventNotify(ViewManagerEventListener::ViewManagerEvent, void*);

public:
    void initialize(Scene* baseScene);
    void initializeBar(int, int, Position);
    void initializeField(int, int);
    void initializeBall(int, Position);
    void updateView();
    void setBallPosition(Position);
    void setBarPosition(Position);
    void removeBall();
    void setTimer(int, int);
    void onTimerExpired(int);

    void addViewManagerEventListener(ViewManagerEventListener*);
    void removeViewManagerEventListener(ViewManagerEventListener*);

    void onTouchBegan(Node*, Position);
    void onTouchMoved(Node*, Position);
    void onTouchEnded(Node*);

    void addBlock(int, int, Position);
    void setBlockColor(int, Color3B);
    void markBlockAsKilled(int);

    void showCongratulation(int, int);
};

#endif // __VIEWMANAGER_H__
