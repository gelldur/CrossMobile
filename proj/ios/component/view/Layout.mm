//
// Created by Dawid Drozd aka Gelldur on 7/11/16.
//

#include <platform/Context.h>
#include <component/view/Layout.h>
#include <platform/ContextHelper.h>

#import <UIKit/UIKit.h>

void Layout::layout()
{
	auto context = getContext();

	UIView* view = ContextHelper::getNative(context);
	[view setNeedsLayout];
	[view layoutIfNeeded];
}
