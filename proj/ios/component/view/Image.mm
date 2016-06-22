//
// Created by Dawid Drozd aka Gelldur on 6/15/16.
//

#include <component/view/Image.h>

#include <bridge/NativeObject.h>
#include <bridge/Context.h>
#include <log.h>

#import <UIKit/UIKit.h>

void Image::loadImage(const std::string& url)
{
	auto context = getContext();

	UIImageView* image = context->getNative();

	// @formatter:off
	[image sd_setImageWithURL:[NSURL URLWithString:[NSString stringWithUTF8String:url.c_str()]]];
	// @formatter:on
}
