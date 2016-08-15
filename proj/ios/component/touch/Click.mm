//
// Created by Dawid Drozd aka Gelldur on 8/4/16.
//

#include <component/touch/Click.h>

#include <log.h>
#include <platform/Context.h>
#include <platform/ContextHelper.h>

#import <BlocksKit/BlocksKit.h>
#import <BlocksKit/BlocksKit+UIKit.h>

void Click::onEnter()
{
	auto context = getContext();
	UIButton* button = ContextHelper::getNative(context);

	[button bk_addEventHandler:^(id sender) {
		onClick();
	} forControlEvents:UIControlEventTouchUpInside];
}

void Click::onExit()
{
}
