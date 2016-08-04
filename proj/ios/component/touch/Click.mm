//
// Created by Dawid Drozd aka Gelldur on 8/4/16.
//

#include <component/touch/Click.h>

#include <log.h>
#include <platform/Context.h>

#import <BlocksKit/BlocksKit.h>
#import <BlocksKit/BlocksKit+UIKit.h>

void Click::onEnter()
{
	auto context = getContext();
	UIButton* button = context->getNative();

	[button bk_addEventHandler:^(id sender) {
		onClick();
	} forControlEvents:UIControlEventTouchUpInside];
}

void Click::onExit()
{
}
