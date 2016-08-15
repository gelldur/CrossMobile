//
// Created by Dawid Drozd aka Gelldur on 6/17/16.
//

#include <platform/Context.h>
#include <component/view/Visibility.h>
#include <platform/ContextHelper.h>

#import <UIKit/UIKit.h>

void Visibility::setVisibility(Visibility::Visible visible)
{
	auto context = getContext();

	UIView* view = ContextHelper::getNative(context);
	const bool hidden = (visible != Visible::VISIBLE);
	// @formatter:off
	[view setHidden:hidden];
	// @formatter:on
}
