LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := ee_x_cocos_static
LOCAL_CPP_FEATURES := exceptions
LOCAL_CPPFLAGS := -std=c++17
LOCAL_SRC_FILES := ${shell find $(LOCAL_PATH) -name "*.cpp" -print}

ifeq ($(filter $(modules-get-list), cc_static),)
	# cocos-creator
	LOCAL_STATIC_LIBRARIES := cocos2dx_static
else
	# cocos2d-x
	LOCAL_STATIC_LIBRARIES := cc_static
endif

LOCAL_STATIC_LIBRARIES += ee_x_core_static

include $(BUILD_STATIC_LIBRARY)