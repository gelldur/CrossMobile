CMAKE_MINIMUM_REQUIRED(VERSION 3.3)
PROJECT(CrossMobile)

# Set core files
SET(SOURCE_FILES_CORE
		src/acme/ColorUtils.h
		src/acme/DebugUtils.cpp src/acme/DebugUtils.h
		src/acme/guard/ChangeOnEnd.h
		src/acme/LambdaObserver.cpp src/acme/LambdaObserver.h
		src/acme/Macros.h
		src/acme/MakeUnique.h
		src/acme/text/AttributedText.cpp src/acme/text/AttributedText.h
		src/acme/text/StringFastUtils.cpp src/acme/text/StringFastUtils.h
		src/acme/text/StringUtils.cpp src/acme/text/StringUtils.h
		src/acme/text/Utf8.cpp src/acme/text/Utf8.h
		src/api/ApiThreadPool.cpp src/api/ApiThreadPool.h
		src/api/Async.h
		src/api/exception/ApiException.cpp src/api/exception/ApiException.h
		src/api/exception/ApiException.cpp src/api/exception/ApiException.h
		src/api/exception/ValidateException.cpp src/api/exception/ValidateException.h
		src/api/exception/ValidateException.cpp src/api/exception/ValidateException.h
		src/api/method/CommonMethod.cpp src/api/method/CommonMethod.h
		src/api/Server.cpp src/api/Server.h
		src/api/UrlBuilder.cpp src/api/UrlBuilder.h
		src/Application.cpp src/Application.h
		src/component/adapter/AdapterList.cpp src/component/adapter/AdapterList.h
		src/component/adapter/ListDataSourceComponent.cpp src/component/adapter/ListDataSourceComponent.h
		src/component/common/Config.cpp src/component/common/Config.h
		src/component/common/Container.cpp src/component/common/Container.h
		src/component/common/Pool.cpp src/component/common/Pool.h
		src/component/Component.cpp src/component/Component.h
		src/component/ComponentSerializer.cpp src/component/ComponentSerializer.h
		src/component/Nodect.cpp src/component/Nodect.h
		src/component/NodectBuilder.cpp src/component/NodectBuilder.h
		src/component/NodectHelper.cpp src/component/NodectHelper.h
		src/component/touch/Click.cpp src/component/touch/Click.h
		src/component/view/Button.cpp src/component/view/Button.h
		src/component/view/Image.cpp src/component/view/Image.h
		src/component/view/Layout.cpp src/component/view/Layout.h
		src/component/view/List.cpp src/component/view/List.h
		src/component/view/Loading.cpp src/component/view/Loading.h
		src/component/view/Text.cpp src/component/view/Text.h
		src/component/view/Visibility.cpp src/component/view/Visibility.h
		src/data/Preferences.cpp src/data/Preferences.h
		src/data/provider/DataProviderComponent.cpp src/data/provider/DataProviderComponent.h
		src/data/provider/Provider.cpp src/data/provider/Provider.h
		src/data/receiver/Receiver.cpp src/data/receiver/Receiver.h
		src/data/Refresher.cpp src/data/Refresher.h
		src/Director.cpp src/Director.h
		src/exception/Fail.cpp src/exception/Fail.h
		src/platform/Bridge.cpp src/platform/Bridge.h
		src/platform/Context.cpp src/platform/Context.h
		src/screen/Screen.cpp src/screen/Screen.h
		src/screen/ScreenCreator.cpp src/screen/ScreenCreator.h
		src/screen/ScreenHelper.h
		src/screen/StateManager.cpp src/screen/StateManager.h
		src/UILoop.h
		)

IF(LINUX)
	SET(SOURCE_FILES_PLATFORM
			proj/linux/log.h
			)

	SET(INCLUDE_DIRS_PLATFORM
			proj/linux
			)
ELSEIF(ANDROID)
	SET(PLATFORM_ANDROID_SRC proj/android/library/src/main/native)
	SET(PLATFORM_ANDROID_SRC_OBJECTJNI proj/android/library/src/main/libs-native/jniobject/src/)

	SET(SOURCE_FILES_PLATFORM
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
ELSEIF(MAC_IOS)
	SET(SOURCE_FILES_PLATFORM
			proj/ios/ColorUtils.h
			proj/ios/DebugUtils.h
			proj/ios/DebugUtils.mm
			proj/ios/log.h
			proj/ios/Utils.h
			proj/ios/Utils.mm
			proj/ios/component/adapter/AdapterListProtocol.h
			proj/ios/component/adapter/ListDataSourceComponent.mm
			proj/ios/component/list/List.mm
			proj/ios/component/list/ListProtocol.h
			proj/ios/component/touch/Click.mm
			proj/ios/component/view/Button.mm
			proj/ios/component/view/Image.mm
			proj/ios/component/view/Layout.mm
			proj/ios/component/view/Loading.mm
			proj/ios/component/view/LoadingProtocol.h
			proj/ios/component/view/Text.mm
			proj/ios/component/view/Visibility.mm
			proj/ios/platform/IosBridge.h
			proj/ios/platform/IosBridge.mm
			proj/ios/platform/ContextHelper.mm proj/ios/platform/ContextHelper.h
			proj/ios/screen/BaseScreenController.h
			proj/ios/screen/BaseScreenController.mm
			proj/ios/view/adapter/BaseAdapter.h
			proj/ios/view/adapter/BaseAdapter.mm
			proj/ios/view/adapter/UserInteraction.h
			)

	SET(INCLUDE_DIRS_PLATFORM
			proj/ios/
			)
ELSE()
	MESSAGE(FATAL_ERROR "Set build platform, CMake will exit.")
ENDIF(LINUX)

SET(INCLUDE_DIRS_CORE
		src/
		)

ADD_LIBRARY(CrossMobile STATIC ${SOURCE_FILES_CORE} ${SOURCE_FILES_PLATFORM})

TARGET_INCLUDE_DIRECTORIES(CrossMobile PUBLIC
		${INCLUDE_DIRS_CORE}
		${INCLUDE_DIRS_PLATFORM}
		)

IF(DEVELOPER_ANDROID)
	TARGET_INCLUDE_DIRECTORIES(CrossMobile PUBLIC
			$ENV{NDK_ROOT}/platforms/android-9/arch-arm/usr/include/
			)
ENDIF()

SET(JSONCPP_WITH_TESTS OFF CACHE BOOL "" FORCE)
SET(JSONCPP_WITH_POST_BUILD_UNITTEST OFF CACHE BOOL "" FORCE)
SET(JSONCPP_WITH_PKGCONFIG_SUPPORT OFF CACHE BOOL "" FORCE)

ADD_SUBDIRECTORY("libs/jsoncpp/")
TARGET_LINK_LIBRARIES(CrossMobile jsoncpp_lib_static)


SET(ENABLE_XML OFF CACHE BOOL "Enable the XML")
SET(ENABLE_JSON OFF CACHE BOOL "Enable the JSON")
SET(ENABLE_MONGODB OFF CACHE BOOL "Enable MongoDB")
SET(ENABLE_PDF OFF CACHE BOOL "Enable PDF")
SET(ENABLE_NETSSL OFF CACHE BOOL "Enable NetSSL")
SET(ENABLE_CRYPTO OFF CACHE BOOL "Enable Crypto")
SET(ENABLE_DATA_MYSQL OFF CACHE BOOL "Enable Data MySQL")
SET(ENABLE_DATA_ODBC OFF CACHE BOOL "Enable Data ODBC")
SET(ENABLE_ZIP OFF CACHE BOOL "Enable Zip")
SET(ENABLE_PAGECOMPILER OFF CACHE BOOL "Enable PageCompiler")
SET(ENABLE_PAGECOMPILER_FILE2PAGE OFF CACHE BOOL "Enable File2Page")

SET(POCO_STATIC ON CACHE BOOL "" FORCE)

ADD_SUBDIRECTORY("libs/poco")
TARGET_LINK_LIBRARIES(CrossMobile PocoNet PocoUtil PocoData PocoDataSQLite)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic")#Add -Werror
#SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-long-long -Wno-unused-private-field -Wnon-virtual-dtor")


MESSAGE(STATUS "CMake ${CMAKE_VERSION} successfully configured ${PROJECT_NAME} using ${CMAKE_GENERATOR} generator")
MESSAGE(STATUS "Installation target path: ${CMAKE_INSTALL_PREFIX}")

MESSAGE(STATUS "C_FLAGS:  =${CMAKE_C_FLAGS}")
MESSAGE(STATUS "CMAKE_C_FLAGS_DEBUG:=${CMAKE_C_FLAGS_DEBUG}")
MESSAGE(STATUS "CMAKE_C_FLAGS_RELEASE:=${CMAKE_C_FLAGS_RELEASE}")
MESSAGE(STATUS "CMAKE_C_FLAGS_MINSIZEREL:=${CMAKE_C_FLAGS_MINSIZEREL}")
MESSAGE(STATUS "CMAKE_C_FLAGS_RELWITHDEBINFO:=${CMAKE_C_FLAGS_RELWITHDEBINFO}")
MESSAGE(STATUS "")
MESSAGE(STATUS "")
MESSAGE(STATUS "CXX_FLAGS:=${CMAKE_CXX_FLAGS}")
MESSAGE(STATUS "CMAKE_CXX_FLAGS_DEBUG:=${CMAKE_CXX_FLAGS_DEBUG}")
MESSAGE(STATUS "CMAKE_CXX_FLAGS_RELEASE:=${CMAKE_CXX_FLAGS_RELEASE}")
MESSAGE(STATUS "CMAKE_CXX_FLAGS_MINSIZEREL:=${CMAKE_CXX_FLAGS_MINSIZEREL}")
MESSAGE(STATUS "CMAKE_CXX_FLAGS_RELWITHDEBINFO:=${CMAKE_CXX_FLAGS_RELWITHDEBINFO}")
