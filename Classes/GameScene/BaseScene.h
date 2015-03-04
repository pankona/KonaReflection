#ifndef __BASESCENE_H__
#define __BASESCENE_H__

#include "cocos2d.h"
#include "GameControl.h"

USING_NS_CC;

class BaseScene : public Scene {
private:
    GameControl gameControl;

public:
    virtual bool init();
    virtual void update(float delta);
    CREATE_FUNC(BaseScene);
};

#endif // __BASESCENE_H__
