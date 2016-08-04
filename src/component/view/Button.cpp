//
// Created by Dawid Drozd aka Gelldur on 8/4/16.
//

#include "Button.h"

#include <log.h>
#include <component/Nodect.h>
#include <component/touch/Click.h>

#ifndef PLATFORM_IOS

void Button::image(const std::string& name)
{
	WLOG("Function %s not implemented: %s:%d", __func__, __FILE__, __LINE__);
}

#endif

void Button::setOnClick(const std::function<void(Nodect*)>& callback)
{
	getOwner()->getComponent<Click>().setCallback(callback);
}

Button& Button::getNullObject()
{
	static NullButton nullObject;
	return nullObject;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// NullButton
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void NullButton::image(const std::string& name)
{
	WLOG("NullObject ignoring call: %s in: %s:%d", __func__, __FILE__, __LINE__);
}

