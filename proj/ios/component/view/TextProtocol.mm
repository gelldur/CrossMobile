//
// Created by Dawid Drozd aka Gelldur on 6/15/16.
//

#include <component/view/TextProtocol.h>

#include <bridge/NativeObject.h>
#include <bridge/Context.h>
#include <log.h>
#include <ColorUtils.h>

#import <UIKit/UIKit.h>

void TextProtocol::setText(const char* text)
{
	auto context = getContext();

	UILabel* label = context->getNative();
	label.text = [NSString stringWithUTF8String:text];
}

void TextProtocol::setText(const std::string& text)
{
	setText(text.c_str());
}

void TextProtocol::setTextColor(int color)
{
	auto context = getContext();

	UILabel* label = context->getNative();
	label.textColor = UIColorFromRGB(color);
}


