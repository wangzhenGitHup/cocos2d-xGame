LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/HelloWorldScene.cpp \
                   ../../Classes/WelcomeLayer.cpp \
                   ../../Classes/GameLayer.cpp \
                   ../../Classes/PlaneLayer.cpp \
                   ../../Classes/BulletLayer.cpp \
                   ../../Classes/MultiBulletLayer.cpp \
                   ../../Classes/Enemy.cpp \
                   ../../Classes/EnemyLayer.cpp \
                   ../../Classes/BulletBase.cpp \
                   ../../Classes/UFO.cpp \
                   ../../Classes/GameOverLayer.cpp \
                   ../../Classes/ControlLayer.cpp \
                   ../../Classes/NoTouchLayer.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

LOCAL_WHOLE_STATIC_LIBRARIES += cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static
LOCAL_WHOLE_STATIC_LIBRARIES += box2d_static
LOCAL_WHOLE_STATIC_LIBRARIES += chipmunk_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_extension_static

include $(BUILD_SHARED_LIBRARY)

$(call import-module,cocos2dx)
$(call import-module,cocos2dx/platform/third_party/android/prebuilt/libcurl)
$(call import-module,CocosDenshion/android)
$(call import-module,extensions)
$(call import-module,external/Box2D)
$(call import-module,external/chipmunk)
