//
// Created by Dawid Drozd aka Gelldur on 25.04.16.
//

#include <log.h>
#include "IosAdapter.h"

IosAdapter::IosAdapter()
{
}

void IosAdapter::onStartScreen(Screen* screen)
{
	//id object = [[NSClassFromString(@"NameofClass") alloc] init];
}

NativeView* IosAdapter::findViewByTag(const std::string& tag)
{
	return nullptr;
}
