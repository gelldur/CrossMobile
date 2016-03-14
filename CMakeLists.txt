CMAKE_MINIMUM_REQUIRED(VERSION 3.3)
PROJECT(DexodeEngine)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

OPTION(IS_LINUX "" ON)
OPTION(IS_ANDROID "" ON)
OPTION(IS_IOS "" OFF)

# Set core files
SET(SOURCE_FILES_CORE
		src/Application.cpp src/Application.h
		src/bridge/NativeAdapter.h
		src/bridge/NativeView.cpp src/bridge/NativeView.h
		src/Component.cpp src/Component.h
		src/data/provider/DataProviderComponent.cpp src/data/provider/DataProviderComponent.h
		src/data/provider/Provider.cpp src/data/provider/Provider.h
		src/data/receiver/Receiver.cpp src/data/receiver/Receiver.h
		src/Director.cpp src/Director.h
		src/interface/DataSetAdapter.h
		src/Screen.cpp src/Screen.h
		)

IF(IS_LINUX)
	SET(SOURCE_FILES_PLATFORM
			proj/linux/LinuxAdapter.cpp proj/linux/LinuxAdapter.h
			proj/linux/log.h
			)
	SET(INCLUDE_DIRS_PLATFORM
			"proj/linux/"
			)
ELSEIF(IS_ANDROID)
	SET(SOURCE_FILES_PLATFORM
			proj/android/jni/log.h
			proj/android/jni/Android.h
			proj/android/jni/AndroidAdapter.cpp proj/android/jni/AndroidAdapter.h
			proj/android/jni/AndroidView.cpp proj/android/jni/AndroidView.h
			proj/android/jni/Bridge.cpp
			proj/android/jni/JniObject.cpp proj/android/jni/JniObject.h
			)
	SET(INCLUDE_DIRS_PLATFORM
			"/home/dawid/Android/Sdk/ndk-bundle/platforms/android-21/arch-x86/usr/include/"
			"proj/android/jni"
			)
ELSEIF(IS_IOS)
ENDIF(IS_LINUX)

SET(INCLUDE_DIRS_CORE
		"libs/SQLiteCpp/include"
		"src/"
		)

#OPTION(DEXODE_BUILD_FOR_ANDROID "Building for android" ON)

#IF(DEXODE_BUILD_FOR_ANDROID)
#	SET(INCLUDE_DIRS
#			${INCLUDE_DIRS}
#			proj/android/jni/
#			/home/dawid/Android/Sdk/ndk-bundle/platforms/android-21/arch-x86/usr/include/
#			)
#ENDIF()

#INCLUDE_DIRECTORIES(${INCLUDE_DIRS})

ADD_LIBRARY(DexodeEngine ${SOURCE_FILES_CORE} ${SOURCE_FILES_PLATFORM})

TARGET_INCLUDE_DIRECTORIES(DexodeEngine PUBLIC
		${INCLUDE_DIRS_CORE}
		${INCLUDE_DIRS_PLATFORM}
		)