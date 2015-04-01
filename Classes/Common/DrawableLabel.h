#ifndef __DRAWABLELABEL_H__
#define __DRAWABLELABEL_H__

#include "cocos2d.h"
#include "Drawable.h"
#include "ViewEventListener.h"
#include <string>

USING_NS_CC;

class DrawableLabel : public Drawable {

private:
    Label* label;
    void createLabel(Position, std::string);

public:
    DrawableLabel(Position, std::string);
    Node* getNode();
};

#endif // __DRAWABLELABEL_H__
