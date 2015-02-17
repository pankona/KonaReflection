#ifndef __MODELMANAGER_H__
#define __MODELMANAGER_H__

#include "Field.h"

class ModelManager {
private:    
    Field* field;

public:
    ModelManager();
    void initialize();
    void progress(float delta);

    Field* getField();
};

#endif // __MODELMANAGER_H__
