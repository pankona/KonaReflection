LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/Common/DrawableLabel.cpp \
                   ../../Classes/Common/SelfTimer.cpp \
                   ../../Classes/SceneManager/SceneManager.cpp \
                   ../../Classes/TitleScene/DrawableTitle.cpp \
                   ../../Classes/TitleScene/TitleControl.cpp \
                   ../../Classes/TitleScene/TitleScene.cpp \
                   ../../Classes/TitleScene/TitleViewManager.cpp \
                   ../../Classes/GameScene/Ball.cpp \
                   ../../Classes/GameScene/Bar.cpp \
                   ../../Classes/GameScene/BaseScene.cpp \
                   ../../Classes/GameScene/Block.cpp \
                   ../../Classes/GameScene/DrawableBall.cpp \
                   ../../Classes/GameScene/DrawableBar.cpp \
                   ../../Classes/GameScene/DrawableBlock.cpp \
                   ../../Classes/GameScene/DrawableCongurat.cpp \
                   ../../Classes/GameScene/DrawableField.cpp \
                   ../../Classes/GameScene/Field.cpp \
                   ../../Classes/GameScene/GameControl.cpp \
                   ../../Classes/GameScene/ModelManager.cpp \
                   ../../Classes/GameScene/ViewManager.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes \
                    $(LOCAL_PATH)/../../Classes/Common \
                    $(LOCAL_PATH)/../../Classes/SceneManager \
                    $(LOCAL_PATH)/../../Classes/TitleScene \
                    $(LOCAL_PATH)/../../Classes/GameScene

LOCAL_STATIC_LIBRARIES := cocos2dx_static

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)
