#ifndef __VIEWMANAGER_H__
#define __VIEWMANAGER_H__

#include "cocos2d.h"
#include "Position.h"
#include "DrawableBall.h"
#include "DrawableField.h"
#include "DrawableBar.h"
#include "DrawableBlock.h"
#include "DrawableCongrat.h"
#include "DrawableGameOver.h"
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
    DrawableGameOver* dGameOver;
    std::vector<DrawableBlock*> dBlocks;
    bool isBarSwinging;
    void eventNotify(ViewManagerEventListener::ViewManagerEvent, void*);
    bool hasCollisionWhileBarSwinging(DrawableBar*, DrawableBall*);

public:
    void initialize(Scene* baseScene);
    void initializeBar(int, int, Position);
    void initializeField(int, int);
    void initializeBall(int, Position);
    void setBallPosition(Position);
    void setBarPosition(Position);
    void removeBall();
    void setTimer(int, int);
    void onTimerExpired(int);

    void addViewManagerEventListener(ViewManagerEventListener*);
    void removeViewManagerEventListener(ViewManagerEventListener*);

    void onTouchBegan(Node*, Position, void*);
    void onTouchMoved(Node*, Position, void*);
    void onTouchEnded(Node*, void*);

    void addBlock(int, int, Position);
    void setBlockColor(int, Color3B);
    void markBlockAsKilled(int);

    void showCongratulation(int, int);
    void showGameOver(int, int);

    void setVerticalDrawDelta(int);

    void setIsBarSwinging(bool);
};

#endif // __VIEWMANAGER_H__
