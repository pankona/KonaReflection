#ifndef __VIEWMANAGER_H__
#define __VIEWMANAGER_H__

#include "cocos2d.h"
#include "Position.h"
#include "DrawableBall.h"
#include "DrawableField.h"
#include "DrawableBar.h"
#include "DrawableBlock.h"
#include "ViewEventListener.h"
#include "ViewManagerEventListener.h"

USING_NS_CC;

class ViewManager : public ViewEventListener {
private:    
    std::vector<ViewManagerEventListener*> listeners;
    Scene* baseScene;
    DrawableBall* dBall;
    DrawableField* dField;
    DrawableBar* dBar;
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

    void addViewManagerEventListener(ViewManagerEventListener*);
    void removeViewManagerEventListener(ViewManagerEventListener*);

    void onTouchBegan(Position);
    void onTouchMoved(Position);
    void onTouchEnded();

    void addBlock(int, int, Position);
    void setBlockColor(int, Color3B);
    void markBlockAsKilled(int);
};

#endif // __VIEWMANAGER_H__
