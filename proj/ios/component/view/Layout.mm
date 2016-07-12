//
// Created by Dawid Drozd aka Gelldur on 7/11/16.
//

#include <platform/Context.h>
#include <component/view/Layout.h>

#import <UIKit/UIKit.h>

void Layout::layout()
{
	auto context = getContext();

	UIView* view = context->getNative();
	[view setNeedsLayout];
	[view layoutIfNeeded];
}
