#ifndef __DRAWABLEGAMEOVER_H__
#define __DRAWABLEGAMEOVER_H__

#include "cocos2d.h"
#include "Position.h"
#include "Drawable.h"
#include "DrawableLabel.h"
#include "ViewEventListener.h"

USING_NS_CC;

class DrawableGameOver : public Drawable, public ViewEventListener {

private:
    Layer* baseLayer;
    DrawableLabel* dGameOverLabel;
    DrawableLabel* dBackToTitleLabel;
    DrawableLabel* dRetryLabel;
    void createBaseLayer(int, int);

public:
    // FIXME: This enum should define common event header.
    enum GameOverEvent {
        BACK_TO_TITLE,
        RETRY
    };
    DrawableGameOver(int, int);
    Node* getNode();

    void onTouchBegan(Node*, Position, void*);
    void onTouchMoved(Node*, Position, void*);
    void onTouchEnded(Node*, void*);
};

#endif // __DRAWABLEGAMEOVER_H__
