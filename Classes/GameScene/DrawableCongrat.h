#ifndef __DRAWABLECONGRAT_H__
#define __DRAWABLECONGRAT_H__

#include "cocos2d.h"
#include "Position.h"
#include "Drawable.h"
#include "DrawableLabel.h"
#include "ViewEventListener.h"

USING_NS_CC;

class DrawableCongrat : public Drawable, public ViewEventListener {

private:
    Layer* baseLayer;
    DrawableLabel* dCongLabel;
    DrawableLabel* dBackToTitleLabel;
    DrawableLabel* dNextStageLabel;
    void createBaseLayer(int, int);

public:
    DrawableCongrat(int, int);
    Node* getNode();

    void onTouchBegan(Node*, Position, void*);
    void onTouchMoved(Node*, Position, void*);
    void onTouchEnded(Node*, void*);
};

#endif // __DRAWABLECONGRAT_H__
