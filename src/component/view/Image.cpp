//
// Created by Dawid Drozd aka Gelldur on 6/22/16.
//

#include "Image.h"

#include <log.h>

#if !defined PLATFORM_IOS && !defined PLATFORM_ANDROID

void Image::loadImage(const std::string& url)
{
	WLOG("Function %s not implemented: %s:%d", __func__, __FILE__, __LINE__);
}

void Image::image(const std::string& name)
{
	WLOG("Function %s not implemented: %s:%d", __func__, __FILE__, __LINE__);
}

#endif

Image& Image::getNullObject()
{
	static NullImage nullObject;
	return nullObject;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// NullImage
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void NullImage::loadImage(const std::string& url)
{
	WLOG("NullObject ignoring call: %s in: %s:%d", __func__, __FILE__, __LINE__);
}

void NullImage::image(const std::string& name)
{
	WLOG("NullObject ignoring call: %s in: %s:%d", __func__, __FILE__, __LINE__);
}
