#ifndef __DRAWABLE_H__
#define __DRAWABLE_H__

#include "ViewEventListener.h"
#include <vector>

class Drawable {

private:
    std::vector<ViewEventListener*> listeners;

public:
    virtual Node* getNode() = 0;
    void addViewEventListener(ViewEventListener*);
    void removeViewEventListener(ViewEventListener*);
};

#endif /* __DRAWABLE_H__ */
