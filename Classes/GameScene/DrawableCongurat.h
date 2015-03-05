#ifndef __DRAWABLECONGURAT_H__
#define __DRAWABLECONGURAT_H__

#include "cocos2d.h"
#include "Position.h"
#include "DrawableLabel.h"
#include "ViewEventListener.h"

USING_NS_CC;

class DrawableCongurat /* listenable */ {

private:
    Layer* baseLayer;
    DrawableLabel* dCongLabel;
    std::vector<ViewEventListener*> listeners;
    void createBaseLayer(int, int);

public:
    DrawableCongurat(int, int);
    Layer* getLayer();
    void addViewEventListener(ViewEventListener*);
    void removeViewEventListener(ViewEventListener*);
};

#endif // __DRAWABLECONGURAT_H__
