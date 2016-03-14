LOCAL_PATH := $(call my-dir)

#$(warning $(LOCAL_PATH))

ROOT := $(LOCAL_PATH)/../../../src
PROJ := $(LOCAL_PATH)/../../../proj/android/jni
LIB_JNI_OBJECT := $(LOCAL_PATH)/../../../libs/jniobject/src

DEXODE_ENGINE_SRC := \
	$(ROOT)/Application.cpp\
	$(PROJ)/AndroidAdapter.cpp\
	$(PROJ)/AndroidView.cpp\
	$(PROJ)/Bridge.cpp\
	$(LIB_JNI_OBJECT)/JniObject.cpp\
	$(ROOT)/bridge/NativeView.cpp\
	$(ROOT)/Component.cpp\
	$(ROOT)/data/provider/DataProviderComponent.cpp\
	$(ROOT)/data/provider/Provider.cpp\
	$(ROOT)/data/receiver/Receiver.cpp\
	$(ROOT)/Director.cpp\
	$(ROOT)/Screen.cpp

DEXODE_ENGINE_INCLUDE :=\
	$(ROOT)\
	$(PROJ)\
	$(LIB_JNI_OBJECT)
