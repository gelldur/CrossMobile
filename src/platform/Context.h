//
// Created by Dawid Drozd aka Gelldur on 8/15/16.
//

#pragma once

#if PLATFORM_ANDROID
#include <JniObject.h>
#endif

class Context
{
public:
#if PLATFORM_ANDROID

	Context(JniObject nativeObject)
			: _nativeObject(nativeObject)
	{
	}

	//For tests
	Context(void* testCtor)
	{
	}

	JniObject& getNative();

	static void setApplicationContext(jobject appContext);
	static JniObject& getApplicationContext();

#else

	Context(void* pointer)
			: _nativePointer(pointer)
	{
	}

	void* getNative();

#endif

private:
#if PLATFORM_ANDROID
	JniObject _nativeObject;
#else
	void* _nativePointer = nullptr;
#endif

};
