//
// Created by Dawid Drozd aka Gelldur on 7/11/16.
//

#include "Layout.h"

#include <log.h>

#ifndef PLATFORM_IOS

void Layout::layout()
{
	WLOG("Function %s not implemented: %s:%d", __func__, __FILE__, __LINE__);
}

#endif

Layout& Layout::getNullObject()
{
	static NullLayout nullObject;
	return nullObject;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// NullLayout
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void NullLayout::layout()
{
	WLOG("NullObject ignoring call: %s in: %s:%d", __func__, __FILE__, __LINE__);
}


