//
// Created by Dawid Drozd aka Gelldur on 6/17/16.
//

#include <component/view/Visibility.h>
#include <bridge/Nodect.h>
#include <bridge/Context.h>

#import <UIKit/UIKit.h>

void Visibility::setVisibility(Visibility::Visible visible)
{
	auto context = getContext();

	UIView* view = context->getNative();
	const bool hidden = (visible != Visible::VISIBLE);
	// @formatter:off
	[view setHidden:hidden];
	// @formatter:on
}
