//
// Created by Dawid Drozd aka Gelldur on 6/15/16.
//

#include <component/view/Text.h>

#include <platform/Context.h>
#include <log.h>
#include <ColorUtils.h>

#import <UIKit/UIKit.h>

void Text::setText(const char* text)
{
	auto context = getContext();

	// @formatter:off
	UILabel* label = context->getNative();
	label.text = [NSString stringWithUTF8String:text];
	// @formatter:on
}

void Text::setText(const std::string& text)
{
	setText(text.c_str());
}

void Text::setTextColor(int color)
{
	auto context = getContext();

	UILabel* label = context->getNative();
	label.textColor = UIColorFromRGB(color);
}


