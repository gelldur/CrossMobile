CMAKE_MINIMUM_REQUIRED(VERSION 3.3)

SET(PLATFORM_ANDROID_SRC proj/android/library/src/main/native)
SET(PLATFORM_ANDROID_SRC_OBJECTJNI proj/android/library/src/main/libs-native/jniobject/src/)
SET(PLATFORM_ANDROID_JNI proj/android/library/src/main/native-jni)

SET(SOURCE_FILES_PLATFORM
		${PLATFORM_ANDROID_JNI}/ActivityComponent.cpp
		${PLATFORM_ANDROID_JNI}/Extractor.cpp
		${PLATFORM_ANDROID_JNI}/List.cpp
		${PLATFORM_ANDROID_JNI}/main.cpp
		${PLATFORM_ANDROID_JNI}/NodectBridge-jni.cpp
		${PLATFORM_ANDROID_SRC_OBJECTJNI}/JniObject.cpp ${PLATFORM_ANDROID_SRC_OBJECTJNI}/JniObject.h
		${PLATFORM_ANDROID_SRC}/Android.h
		${PLATFORM_ANDROID_SRC}/component/NodectBridge.cpp ${PLATFORM_ANDROID_SRC}/component/NodectBridge.h
		${PLATFORM_ANDROID_SRC}/component/view/Image.cpp
		${PLATFORM_ANDROID_SRC}/component/view/Text.cpp
		${PLATFORM_ANDROID_SRC}/FixAny.h
		${PLATFORM_ANDROID_SRC}/log.h
		${PLATFORM_ANDROID_SRC}/platform/AndroidBridge.cpp ${PLATFORM_ANDROID_SRC}/platform/AndroidBridge.h
		)

SET(INCLUDE_DIRS_PLATFORM
		${PLATFORM_ANDROID_SRC}
		proj/android/library/src/main/libs-native/jniobject/src/
		)

IF(DEVELOPER_ANDROID)
	TARGET_INCLUDE_DIRECTORIES(CrossMobile PUBLIC
			$ENV{NDK_ROOT}/platforms/android-9/arch-arm/usr/include/
			)
ENDIF()


IF(CMAKE_CXX_COMPILER_ID MATCHES "Clang")# using Clang
ELSEIF(CMAKE_CXX_COMPILER_ID MATCHES "GNU")# using GCC
ELSEIF(CMAKE_CXX_COMPILER_ID MATCHES "Intel")# using Intel C++
ELSEIF(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")# using Visual Studio C++
ENDIF()
