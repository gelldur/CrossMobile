# Set the Base SDK (only change the SDKVER value, if for instance, you are building for iOS 5.0):
IF(NOT SDKVER)
	MESSAGE(ERROR "Please define SDKVER variable for iOS")
ENDIF()

SET(DEVROOT "/Applications/Xcode.app/Contents/Developer/Platforms/iPhoneOS.platform/Developer")
SET(SDKROOT "${DEVROOT}/SDKs/iPhoneOS${SDKVER}.sdk")
IF(EXISTS ${SDKROOT})
	SET(CMAKE_OSX_SYSROOT "iphoneos${SDKVER}")
ELSE()
	MESSAGE("Warning, iOS Base SDK path not found: " ${SDKROOT})
ENDIF()

# Will resolve to "Standard (armv6 armv7)" on Xcode 4.0.2 and to "Standard (armv7)" on Xcode 4.2:
SET(CMAKE_OSX_ARCHITECTURES "$(ARCHS_STANDARD)")

# seamless toggle between device and simulator
SET(CMAKE_XCODE_EFFECTIVE_PLATFORMS "-iphoneos;-iphonesimulator")


MACRO(ADD_FRAMEWORK fwname appname)
	FIND_LIBRARY(FRAMEWORK_${fwname}
			NAMES ${fwname}
			PATHS ${CMAKE_OSX_SYSROOT}/System/Library
			PATH_SUFFIXES Frameworks
			NO_DEFAULT_PATH)
	IF(${FRAMEWORK_${fwname}} STREQUAL FRAMEWORK_${fwname}-NOTFOUND)
		MESSAGE(ERROR ": Framework ${fwname} not found")
	ELSE()
		TARGET_LINK_LIBRARIES(${appname} ${FRAMEWORK_${fwname}})
		MESSAGE(STATUS "Framework ${fwname} found at ${FRAMEWORK_${fwname}}")
	ENDIF()
ENDMACRO(ADD_FRAMEWORK)

# This little macro lets you set any XCode specific property.
MACRO(SET_XCODE_PROPERTY TARGET XCODE_PROPERTY XCODE_VALUE)
	SET_PROPERTY(TARGET ${TARGET} PROPERTY
			XCODE_ATTRIBUTE_${XCODE_PROPERTY} ${XCODE_VALUE})
ENDMACRO(SET_XCODE_PROPERTY)

MACRO(SET_XCODE_PROPERTY_VARIANT TARGET XCODE_PROPERTY XCODE_VARIANT XCODE_VALUE)
	SET_PROPERTY(TARGET ${TARGET} PROPERTY
			XCODE_ATTRIBUTE_${XCODE_PROPERTY}[variant=${XCODE_VARIANT}] ${XCODE_VALUE})
ENDMACRO(SET_XCODE_PROPERTY_VARIANT)
