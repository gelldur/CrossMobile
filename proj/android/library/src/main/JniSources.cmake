SET(PLATFORM_ANDROID_JNI ${PROJECT_SOURCE_DIR}/native/libraries/CrossMobile/proj/android/library/src/main/native-jni)

SET(SOURCE_FILES_PLATFORM_JNI
		${PLATFORM_ANDROID_JNI}/ActivityComponent.cpp
		${PLATFORM_ANDROID_JNI}/List.cpp
		${PLATFORM_ANDROID_JNI}/NodectBridge-jni.cpp
		${PLATFORM_ANDROID_JNI}/Extractor.cpp
		${PLATFORM_ANDROID_JNI}/main.cpp
		)
