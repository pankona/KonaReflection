#ifndef __SPLASH_SCENE_H__
#define __SPLASH_SCENE_H__

#include "cocos2d.h"
#include "GameControl.h"

USING_NS_CC;

class Splash : public cocos2d::Scene {
private:
    GameControl gameControl;

public:
    virtual bool init();
    virtual void update(float delta);
    CREATE_FUNC(Splash);
};

#endif // __Splash_SCENE_H__
