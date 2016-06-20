//
// Created by Dawid Drozd aka Gelldur on 6/17/16.
//

#include <component/view/Visibility.h>
#include <bridge/NativeObject.h>
#include <bridge/Context.h>

#import <UIKit/UIKit.h>

void Visibility::setVisibility(Visibility::Visible visible)
{
	auto context = getOwner()->getContext();

	UIView* view = context->getNative();

	if (visible == Visible::INVISIBLE)
	{
		[view setHidden:true];
	}
	else if (visible == Visible::VISIBLE)
	{
		[view setHidden:false];
	}
}
