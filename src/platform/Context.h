//
// Created by Dawid Drozd aka Gelldur on 8/15/16.
//

#pragma once

#ifdef PLATFORM_IOS

#elif PLATFORM_ANDROID
#include <JniObject.h>
#endif

class Context
{
public:
#ifdef PLATFORM_IOS

	Context(id nativeObject)
			: _nativeObject(nativeObject)
	{
	}

	id getNative();

#elif PLATFORM_ANDROID

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

#elif PLATFORM_LINUX

	Context(void* pointer)
	{
	}

#endif

private:
#ifdef PLATFORM_IOS
	__weak id _nativeObject;
#elif PLATFORM_ANDROID
	JniObject _nativeObject;
#endif

};


