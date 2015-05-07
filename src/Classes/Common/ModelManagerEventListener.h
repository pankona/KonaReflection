#ifndef __MODELMANAGEREVENTLISTERN_H__
#define __MODELMANAGEREVENTLISTERN_H__

class ModelManagerEventListener {
public:
    enum ModelManagerEvent {
        BLOCK_DIED,
        ALL_BLOCK_DESTROYED,
        BALL_FALL,
        PLAYER_DEAD,
        BAR_SWING_START,
        BAR_SWINGING,
        BAR_SWING_AT_HIT,
        BAR_SWING_END,
    };

   virtual void onModelManagerEvent(ModelManagerEvent, void*) = 0;
};

#endif /* __MODELMANAGEREVENTLISTERN_H__ */
