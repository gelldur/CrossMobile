//
// Created by Dawid Drozd aka Gelldur on 7/11/16.
//

#include "Loading.h"

#include <log.h>

#ifndef PLATFORM_IOS

void Loading::loadingStart()
{
	WLOG("Function %s not implemented: %s:%d", __func__, __FILE__, __LINE__);
}

void Loading::loadingStop()
{
	WLOG("Function %s not implemented: %s:%d", __func__, __FILE__, __LINE__);
}

#endif

Loading& Loading::getNullObject()
{
	static NullLoading nullObject;
	return nullObject;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// NullLoading
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void NullLoading::loadingStart()
{
	WLOG("NullObject ignoring call: %s in: %s:%d", __func__, __FILE__, __LINE__);
}

void NullLoading::loadingStop()
{
	WLOG("NullObject ignoring call: %s in: %s:%d", __func__, __FILE__, __LINE__);
}
