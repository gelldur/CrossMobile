//
// Created by Dawid Drozd aka Gelldur on 7/11/16.
//

#import "LoadingProtocol.h"

#include <platform/Context.h>
#include <component/view/Loading.h>

#import <UIKit/UIKit.h>

void Loading::loadingStart()
{
	auto context = getContext();

	id view = context->getNative();
	[view loadingStart];
}

void Loading::loadingStop()
{
	auto context = getContext();

	id view = context->getNative();
	[view loadingStop];
}
