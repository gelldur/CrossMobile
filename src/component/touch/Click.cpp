//
// Created by Dawid Drozd aka Gelldur on 8/4/16.
//

#include "Click.h"

#include <log.h>

#ifndef PLATFORM_IOS

void Click::onEnter()
{
	WLOG("Function %s not implemented: %s:%d", __func__, __FILE__, __LINE__);
}

void Click::onExit()
{
	WLOG("Function %s not implemented: %s:%d", __func__, __FILE__, __LINE__);
}

#endif

void Click::onClick()
{
	if (_callback)
	{
		_callback(getOwner());
	}
	else
	{
		WLOG("Click callback not set!");
	}
}

void Click::setCallback(const std::function<void(Nodect*)>& callback)
{
	_callback = callback;
}

Click& Click::getNullObject()
{
	static NullClick nullObject;
	return nullObject;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// NullClick
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void NullClick::onClick()
{
	WLOG("NullObject ignoring call: %s in: %s:%d", __func__, __FILE__, __LINE__);
}

