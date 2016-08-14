//
// Created by Dawid Drozd aka Gelldur on 6/17/16.
//

#include "Context.h"

#include <exception/Fail.h>

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
