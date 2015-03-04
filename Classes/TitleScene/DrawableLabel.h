#ifndef __DRAWABLELABEL_H__
#define __DRAWABLELABEL_H__

#include "cocos2d.h"
#include "ViewEventListener.h"
#include <string>

USING_NS_CC;

class DrawableLabel /* listenable */ {

private:
    Label* label;
    std::vector<ViewEventListener*> listeners;
    void createLabel(Position, std::string);

public:
    DrawableLabel(Position, std::string);
    Label* getLabel();
    void addViewEventListener(ViewEventListener*);
    void removeViewEventListener(ViewEventListener*);
};

#endif // __DRAWABLELABEL_H__
