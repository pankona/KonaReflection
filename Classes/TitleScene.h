#ifndef __TITLESCENE_H__
#define __TITLESCENE_H__

#include "cocos2d.h"
#include "TitleControl.h"

USING_NS_CC;

class TitleScene : public Scene {
private:
    TitleControl titleControl;

public:
    virtual bool init();
    CREATE_FUNC(TitleScene);
};

#endif // __TITLESCENE_H__
