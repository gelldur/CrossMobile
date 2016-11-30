CMAKE_MINIMUM_REQUIRED(VERSION 3.4.1)

SET(TEST_SOURCE_FILES_CrossMobile
		gtest/ComponentTest.cpp
		gtest/PreferencesTest.cpp
		gtest/ProviderTest.cpp
		gtest/ScreenStateTest.cpp
		gtest/TestExtractingTags.cpp
		)

ADD_LIBRARY(CrossMobile-gTests STATIC ${TEST_SOURCE_FILES_CrossMobile})

TARGET_LINK_LIBRARIES(CrossMobile-gTests gtest)
TARGET_LINK_LIBRARIES(CrossMobile-gTests CrossMobile)

TARGET_INCLUDE_DIRECTORIES(CrossMobile-gTests
		PRIVATE ../libs/googletest/include
		PUBLIC gtest/
		)

IF(LINUX)
	TARGET_COMPILE_OPTIONS(CrossMobile-gTests PRIVATE -Werror)
ENDIF()

TARGET_COMPILE_OPTIONS(CrossMobile-gTests PRIVATE
		-Wall -pedantic
		-Wno-unused-private-field -Wnon-virtual-dtor)
