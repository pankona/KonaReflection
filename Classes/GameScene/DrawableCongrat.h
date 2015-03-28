#ifndef __DRAWABLECONGRAT_H__
#define __DRAWABLECONGRAT_H__

#include "cocos2d.h"
#include "Position.h"
#include "DrawableLabel.h"
#include "ViewEventListener.h"

USING_NS_CC;

class DrawableCongrat : public ViewEventListener /* listenable */ {

private:
    Layer* baseLayer;
    DrawableLabel* dCongLabel;
    DrawableLabel* dBackToTitleLabel;
    DrawableLabel* dNextStageLabel;
    std::vector<ViewEventListener*> listeners;
    void createBaseLayer(int, int);

public:
    DrawableCongrat(int, int);
    Layer* getLayer();
    void addViewEventListener(ViewEventListener*);
    void removeViewEventListener(ViewEventListener*);

    void onTouchBegan(Node*, Position);
    void onTouchMoved(Node*, Position);
    void onTouchEnded(Node*);
};

#endif // __DRAWABLECONGRAT_H__
