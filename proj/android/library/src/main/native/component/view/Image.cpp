//
// Created by Dawid Drozd aka Gelldur on 8/13/16.
//

#include <component/view/Image.h>

#include <log.h>
#include <platform/Context.h>
#include <JniObject.h>

void Image::loadImage(const std::string& url)
{
	WLOG("Function %s not implemented: %s:%d", __func__, __FILE__, __LINE__);
}

void Image::image(const std::string& name)
{
	JniObject imageWrapper("com.cross.mobile.component.view.Image");// helper class
	imageWrapper.staticCallVoid("setDrawableImage", getContext()->getNative(), name);
}
