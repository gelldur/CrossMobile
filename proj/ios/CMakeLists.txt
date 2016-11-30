CMAKE_MINIMUM_REQUIRED(VERSION 3.3)

#SET(CMAKE_OSX_DEPLOYMENT_TARGET "10.1")
#SET(CMAKE_OSX_SYSROOT "iphoneos")
#
#IF(NOT XCODE_VERSION)
#	MESSAGE(FATAL_ERROR "Xcode only")
#ENDIF()
#
#SET(SDKVER ${CMAKE_OSX_DEPLOYMENT_TARGET})
#
#INCLUDE(../../cmake/iOSBuildHelpers.cmake)

SET(SOURCE_FILES_PLATFORM_IOS
		ColorUtils.h
		component/adapter/AdapterListProtocol.h
		component/adapter/ListDataSourceComponent.mm
		component/list/List.mm
		component/list/ListProtocol.h
		component/touch/Click.mm
		component/view/Button.mm
		component/view/Image.mm
		component/view/Layout.mm
		component/view/Loading.mm
		component/view/LoadingProtocol.h
		component/view/Text.mm
		component/view/Visibility.mm
		DebugUtils.mm DebugUtils.h
		log.h
		platform/ContextHelper.mm platform/ContextHelper.h
		platform/IosBridge.mm platform/IosBridge.h
		screen/BaseScreenController.mm screen/BaseScreenController.h
		Utils.mm Utils.h
		view/adapter/BaseAdapter.mm view/adapter/BaseAdapter.h
		view/adapter/UserInteraction.h
		)

ADD_LIBRARY(CrossMobile-Platform STATIC ${SOURCE_FILES_PLATFORM_IOS})

SET(CMAKE_EXE_LINKER_FLAGS "-framework UIKit")
#FIND_LIBRARY(UIKIT UIKit)
#TARGET_LINK_LIBRARIES(CrossMobile-Platform ${UIKIT})

#ADD_FRAMEWORK(UIKit CrossMobile-Platform)
TARGET_LINK_LIBRARIES(CrossMobile-Platform CrossMobile)

TARGET_INCLUDE_DIRECTORIES(CrossMobile-Platform PUBLIC
		./
		)

#SET_XCODE_PROPERTY(CrossMobile-Platform IPHONEOS_DEPLOYMENT_TARGET ${CMAKE_OSX_DEPLOYMENT_TARGET})
#SET_XCODE_PROPERTY_VARIANT(CrossMobile-Platform ONLY_ACTIVE_ARCH Debug "YES")
#
#SET_TARGET_PROPERTIES(
#		CrossMobile-Platform
#		PROPERTIES
#		MACOSX_BUNDLE YES
#		XCODE_ATTRIBUTE_CODE_SIGN_IDENTITY "iPhone Developer"
#		XCODE_ATTRIBUTE_TARGETED_DEVICE_FAMILY "1,2"
#		XCODE_ATTRIBUTE_CLANG_ENABLE_OBJC_ARC YES
#		XCODE_ATTRIBUTE_COMBINE_HIDPI_IMAGES "NO"
#		XCODE_ATTRIBUTE_PRODUCT_NAME "CrossMobile-Platform"
#		XCODE_ATTRIBUTE_PRODUCT_NAME[variant=Debug] "CrossMobile-Platform_d"
#)
