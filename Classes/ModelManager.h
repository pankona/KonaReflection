#ifndef __MODELMANAGER_H__
#define __MODELMANAGER_H__

#include "Field.h"
#include "Bar.h"
#include "Ball.h"
#include "Block.h"
#include "ModelManagerEventListener.h"
#include <vector>

class ModelManager {
private:
    Field* field;
    Bar* bar;
    Ball* ball;
    std::vector<Block*> blocks;
    Position lastTouchedPosition;
    std::vector<ModelManagerEventListener*> listeners;

    bool isTouchOnRightSideOfBar(int);
    void moveBall(float);
    void moveBar(float);
    void eventNotify(ModelManagerEventListener::ModelManagerEvent, void*);

public:
    ModelManager();
    void initialize();
    void progress(float delta);
    void onTouchBegan(int, int);
    void onTouchMoved(int, int);
    void onTouchEnded();
    void onCollisionBallAndBar();
    void onCollisionBallAndBlock(int, bool);

    void initializeBar();
    Position getBarPosition();
    int getBarWidth();
    int getBarHeight();

    void initializeBall();
    Position getBallPosition();
    int getBallRadius();

    void setFieldSize(int, int);

    void initializeBlocks();
    int getBlockNum();
    int getBlockWidth(int);
    int getBlockHeight(int);
    Position getBlockPosition(int);
    void killBlock(int);

    void addModelManagerEventListener(ModelManagerEventListener*);
};

#endif // __MODELMANAGER_H__
