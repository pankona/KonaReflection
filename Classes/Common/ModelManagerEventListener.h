#ifndef __MODELMANAGEREVENTLISTERN_H__
#define __MODELMANAGEREVENTLISTERN_H__

class ModelManagerEventListener {
public:
    enum ModelManagerEvent {
        BLOCK_DIED,
        ALL_BLOCK_DESTROYED
    };

   virtual void onModelManagerEvent(ModelManagerEvent, void*) = 0;
};

#endif /* __MODELMANAGEREVENTLISTERN_H__ */
