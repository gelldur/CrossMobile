//
// Created by Dawid Drozd aka Gelldur on 8/15/16.
//

#include "Context.h"

#include <exception/Fail.h>

#ifdef PLATFORM_IOS
#import <UIKit/UIKit.h>

id Context::getNative()
{
	if(_nativeObject == nil)
	{
		Fail(__FILE__,__func__,__LINE__).report();
	}
	return _nativeObject;
}
#elif PLATFORM_ANDROID

JniObject& Context::getNative()
{
	if (!_nativeObject)
	{
		Fail(__FILE__, __func__, __LINE__).report();
	}
	return _nativeObject;
}

void Context::setApplicationContext(jobject appContext)
{
	auto& _appContext = getApplicationContext();
	_appContext.clear();
	_appContext.init(appContext);
}

JniObject& Context::getApplicationContext()
{
	static JniObject _appContext;
	return _appContext;
}

#endif
