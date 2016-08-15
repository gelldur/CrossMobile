//
// Created by Dawid Drozd aka Gelldur on 7/11/16.
//

#import "LoadingProtocol.h"

#include <platform/Context.h>
#include <component/view/Loading.h>
#include <platform/ContextHelper.h>

#import <UIKit/UIKit.h>

void Loading::loadingStart()
{
	auto context = getContext();

	id view = ContextHelper::getNative(context);
	[view loadingStart];
}

void Loading::loadingStop()
{
	auto context = getContext();

	id view = ContextHelper::getNative(context);
	[view loadingStop];
}
