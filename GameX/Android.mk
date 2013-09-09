LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := cocos_gamex_common

LOCAL_MODULE_FILENAME := libgamexcommon

CPP_FILE_LIST := $(wildcard $(LOCAL_PATH)/Classes/*.cpp)

LOCAL_SRC_FILES := \
										$(CPP_FILE_LIST:$(LOCAL_PATH)/%=%)										

LOCAL_CFLAGS := -I/$(LOCAL_PATH)/proj.android/jni/gamex/Classes
LOCAL_CFLAGS += -DUSE_FILE32API -DNDEBUG
LOCAL_EXPORT_CFLAGS := -DUSE_FILE32API -DNDEBUG

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_extension_static

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)
            
include $(BUILD_STATIC_LIBRARY)

$(call import-module,CocosDenshion/android)
$(call import-module,cocos2dx)
$(call import-module,extensions)
