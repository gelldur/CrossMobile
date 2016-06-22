//
// Created by Dawid Drozd aka Gelldur on 6/22/16.
//

#include "Visibility.h"

#include <log.h>

#ifndef PLATFORM_IOS

void Visibility::setVisibility(Visible visible)
{
	WLOG("Function %s not implemented: %s:%d", __func__, __FILE__, __LINE__);
}

#endif

Visibility& Visibility::getNullObject()
{
	static NullVisibility nullObject;
	return nullObject;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// NullVisibility
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void NullVisibility::setVisibility(Visibility::Visible visible)
{
	WLOG("NullObject ignoring call: %s in: %s:%d", __func__, __FILE__, __LINE__);
}

