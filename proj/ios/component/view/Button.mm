//
// Created by Dawid Drozd aka Gelldur on 8/4/16.
//

#include <component/view/Button.h>

#include <platform/Context.h>
#include <log.h>
#include <platform/ContextHelper.h>

#import <UIKit/UIKit.h>

void Button::image(const std::string& name)
{
	auto context = getContext();

	UIButton* button = ContextHelper::getNative(context);

	// @formatter:off
	[button setImage:[UIImage imageNamed:[NSString stringWithUTF8String:name.c_str()]] forState:UIControlStateNormal];
	// @formatter:on
}
