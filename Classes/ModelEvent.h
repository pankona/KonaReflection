#ifndef __MODELEVENT_H__
#define __MODELEVENT_H__

#include "ModelEventObserver.h"
#include <vector>

class ModelEvent {
private:
    std::vector<ModelEventObserver*> observers;

public:
    void addObserver(ModelEventObserver*);
    void notify();
};

#endif /* __MODELEVENT_H__ */

