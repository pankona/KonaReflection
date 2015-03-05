#ifndef __GAMECONTROL_H__
#define __GAMECONTROL_H__

#include "cocos2d.h"
#include "ViewManager.h"
#include "ModelManager.h"
#include "ViewManagerEventListener.h"

USING_NS_CC;

class GameControl : public ViewManagerEventListener, public ModelManagerEventListener {
private:
    enum GameState {
        READY,
        STARTED
    };
    GameState gameState;
    ModelManager mm;
    ViewManager  vm;
    int collidedBlockNum;
    void dispatchTimerEvent(int*);

public:
    void initialize(Scene*);
    void update(float);
    void onViewManagerEvent(ViewManagerEventListener::ViewManagerEvent, void*);
    void onModelManagerEvent(ModelManagerEventListener::ModelManagerEvent, void*);
};

#endif // __FIELD_H__
