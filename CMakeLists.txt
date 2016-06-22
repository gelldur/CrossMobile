CMAKE_MINIMUM_REQUIRED(VERSION 3.3)
PROJECT(DexodeEngine)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# Set core files
SET(SOURCE_FILES_CORE
		src/acme/ColorUtils.h
		src/api/adapter/Response.h
		src/api/exception/ApiException.cpp src/api/exception/ApiException.h
		src/api/exception/ApiException.cpp src/api/exception/ApiException.h
		src/api/exception/ValidateException.cpp src/api/exception/ValidateException.h
		src/api/exception/ValidateException.cpp src/api/exception/ValidateException.h
		src/api/method/CommonMethod.cpp src/api/method/CommonMethod.h
		src/api/Server.cpp src/api/Server.h
		src/api/UrlBuilder.cpp src/api/UrlBuilder.h
		src/Application.cpp src/Application.h
		src/bridge/NativeAdapter.h
		src/Component.cpp src/Component.h
		src/data/provider/DataProviderComponent.cpp src/data/provider/DataProviderComponent.h
		src/data/provider/Provider.cpp src/data/provider/Provider.h
		src/data/receiver/Receiver.cpp src/data/receiver/Receiver.h
		src/Director.cpp src/Director.h
		src/exception/ExcaptionHelper.h
		src/interface/DataSetAdapter.h
		src/Screen.cpp src/Screen.h
		src/UILoop.h
		src/acme/text/Utf8.cpp src/acme/text/Utf8.h
		src/acme/text/StringFastUtils.cpp src/acme/text/StringFastUtils.h
		src/acme/LambdaObserver.cpp src/acme/LambdaObserver.h
		src/api/Async.h
		src/acme/Assert.h
		src/api/ApiThreadPool.cpp src/api/ApiThreadPool.h
		src/acme/DebugUtils.cpp src/acme/DebugUtils.h
		src/screen/StateManager.cpp src/screen/StateManager.h
		src/acme/Macros.h
		src/component/view/TextProtocol.h
		src/bridge/NativeObject.cpp src/bridge/NativeObject.h
		src/bridge/NativeObjectBuilder.cpp src/bridge/NativeObjectBuilder.h
		src/component/Container.cpp src/component/Container.h
		src/component/view/Visibility.h
		src/utils/Utils.h
		src/component/view/NullTextProtocol.h
		src/component/view/NullVisibility.h
		src/component/NullContainer.h
		)

IF(LINUX)
	SET(SOURCE_FILES_PLATFORM
			proj/linux/LinuxAdapter.cpp proj/linux/LinuxAdapter.h
			proj/linux/log.h
			proj/linux/bridge/Context.cpp proj/linux/bridge/Context.h
			proj/linux/component/view/TextProtocol.cpp
			proj/linux/component/view/Visibility.cpp
			)

	SET(INCLUDE_DIRS_PLATFORM
			proj/linux
			)
ELSEIF(ANDROID)
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
ELSEIF(MAC_IOS)
	SET(SOURCE_FILES_PLATFORM
			"proj/ios/IosAdapter.cpp" "proj/ios/IosAdapter.h"
			proj/ios/ColorUtils.h
			proj/ios/Utils.h
			proj/ios/bridge/Context.mm proj/ios/bridge/Context.h
			proj/ios/component/view/TextProtocol.mm
			proj/ios/component/view/Visibility.mm
			)

	SET(INCLUDE_DIRS_PLATFORM
			"proj/ios/"
			)
ELSE()
	MESSAGE(FATAL_ERROR "Set build platform, CMake will exit.")
ENDIF(LINUX)

SET(INCLUDE_DIRS_CORE
		"src/"
		)

ADD_LIBRARY(DexodeEngine ${SOURCE_FILES_CORE} ${SOURCE_FILES_PLATFORM})

TARGET_INCLUDE_DIRECTORIES(DexodeEngine PUBLIC
		${INCLUDE_DIRS_CORE}
		${INCLUDE_DIRS_PLATFORM}
		)

SET(JSONCPP_WITH_TESTS OFF CACHE BOOL "" FORCE)
SET(JSONCPP_WITH_POST_BUILD_UNITTEST OFF CACHE BOOL "" FORCE)
SET(JSONCPP_WITH_PKGCONFIG_SUPPORT OFF CACHE BOOL "" FORCE)

ADD_SUBDIRECTORY("libs/jsoncpp/")
TARGET_LINK_LIBRARIES(DexodeEngine jsoncpp_lib_static)

SET(ENABLE_XML OFF CACHE BOOL "Enable the XML" FORCE)
SET(ENABLE_JSON OFF CACHE BOOL "Enable the JSON" FORCE)
SET(ENABLE_MONGODB OFF CACHE BOOL "Enable MongoDB" FORCE)
SET(ENABLE_NETSSL OFF CACHE BOOL "Enable NetSSL" FORCE)
SET(ENABLE_CRYPTO OFF CACHE BOOL "Enable Crypto" FORCE)
SET(ENABLE_DATA OFF CACHE BOOL "Enable Data" FORCE)
SET(ENABLE_DATA_SQLITE OFF CACHE BOOL "Enable Data SQlite" FORCE)
SET(ENABLE_DATA_MYSQL OFF CACHE BOOL "Enable Data MySQL" FORCE)
SET(ENABLE_DATA_ODBC OFF CACHE BOOL "Enable Data ODBC" FORCE)
SET(ENABLE_ZIP OFF CACHE BOOL "Enable Zip" FORCE)
SET(ENABLE_PAGECOMPILER OFF CACHE BOOL "Enable PageCompiler" FORCE)
SET(ENABLE_PAGECOMPILER_FILE2PAGE OFF CACHE BOOL "Enable File2Page" FORCE)


ADD_SUBDIRECTORY("libs/poco")
TARGET_LINK_LIBRARIES(DexodeEngine PocoNet PocoUtil)
