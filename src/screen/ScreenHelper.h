//
// Created by Dawid Drozd aka Gelldur on 6/29/16.
//

#pragma once

#include <Director.h>

namespace ScreenHelper
{

template<class T>
T& getScreen(const char* screenName)
{
	return dynamic_cast<T&>(Director::getInstance().getScreen(screenName));
}

#ifdef PLATFORM_IOS

template<class T>
T& getScreen(id screenController)
{
	return getScreen<T>([screenController getName]);
}

#endif

}
