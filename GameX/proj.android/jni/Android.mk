LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := gamex_shared

LOCAL_MODULE_FILENAME := libgamex

CPP_FILE_LIST := $(wildcard $(LOCAL_PATH)../../Classes/*.cpp)

#LOCAL_SRC_FILES := gamex/main.cpp \
#                   $(CPP_FILE_LIST:$(LOCAL_PATH)/%=%)
                   
LOCAL_SRC_FILES := gamex/main.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes                   

LOCAL_WHOLE_STATIC_LIBRARIES := cocos_gamex_common
LOCAL_WHOLE_STATIC_LIBRARIES += cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_extension_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos2dxandroid_static
LOCAL_WHOLE_STATIC_LIBRARIES += pomelo_static

include $(BUILD_SHARED_LIBRARY)

$(call import-module,../GameX)
$(call import-module,cocos2dx)
$(call import-module,cocos2dx/platform/third_party/android/prebuilt/libcurl)
$(call import-module,CocosDenshion/android)
$(call import-module,extensions)
#$(call import-module,external/Box2D)
$(call import-module,cocos2dx/platform/android)
#$(call import-module,external/chipmunk)
$(call import-module,../libpomelo)
