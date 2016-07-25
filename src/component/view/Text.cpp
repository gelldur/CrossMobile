//
// Created by Dawid Drozd aka Gelldur on 6/22/16.
//


#include "Text.h"

#include <log.h>

#ifndef PLATFORM_IOS

void Text::setText(const char* text)
{
	WLOG("Function %s not implemented: %s:%d", __func__, __FILE__, __LINE__);
}

void Text::setText(const std::string& text)
{
	WLOG("Function %s not implemented: %s:%d", __func__, __FILE__, __LINE__);
}

void Text::setTextColor(int color)
{
	WLOG("Function %s not implemented: %s:%d", __func__, __FILE__, __LINE__);
}

void Text::setTextAttributed(const AttributedText& attributedText)
{
	WLOG("Function %s not implemented: %s:%d", __func__, __FILE__, __LINE__);
}

#endif

Text& Text::getNullObject()
{
	static NullText nullObject;
	return nullObject;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// NullText
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void NullText::setText(const char* text)
{
	WLOG("NullObject ignoring call: %s in: %s:%d", __func__, __FILE__, __LINE__);
}

void NullText::setText(const std::string& text)
{
	WLOG("NullObject ignoring call: %s in: %s:%d", __func__, __FILE__, __LINE__);
}

void NullText::setTextColor(int color)
{
	WLOG("NullObject ignoring call: %s in: %s:%d", __func__, __FILE__, __LINE__);
}

void NullText::setTextAttributed(const AttributedText& attributedText)
{
	WLOG("NullObject ignoring call: %s in: %s:%d", __func__, __FILE__, __LINE__);
}
