LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_LDLIBS += -llog
LOCAL_MODULE    := umc_jni
LOCAL_SRC_FILES := encryptor.c aes/aes.c des/des.c

APP_OPTIM := release
OPT_CFLAGS := -O2 -fno-exceptions -fno-rtti
   
OPT_CPPFLAGS := $(OPT_CLFAGS)
  
APP_CFLAGS := $(APP_CFLAGS) $(OPT_CFLAGS)
#APP_CPPFLAGS := $(APP_CPPFLAGS) $(OPT_CPPFLAGS

include $(BUILD_SHARED_LIBRARY)