LOCAL_PATH := $(call my-dir)

#$(warning $(LOCAL_PATH))

ROOT := $(LOCAL_PATH)/../../../src

DEXODE_ENGINE_SRC := \
	$(ROOT)/Application.cpp\
	$(ROOT)/bridge/android/AndroidAdapter.cpp\
	$(ROOT)/bridge/android/AndroidView.cpp\
	$(ROOT)/bridge/android/Bridge.cpp\
	$(ROOT)/bridge/android/JniObject.cpp\
	$(ROOT)/bridge/NativeView.cpp\
	$(ROOT)/Component.cpp\
	$(ROOT)/data/provider/DataProviderComponent.cpp\
	$(ROOT)/data/provider/Provider.cpp\
	$(ROOT)/data/receiver/Receiver.cpp\
	$(ROOT)/Director.cpp\
	$(ROOT)/Screen.cpp

DEXODE_ENGINE_INCLUDE := $(ROOT)
