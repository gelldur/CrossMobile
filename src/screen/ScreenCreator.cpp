//
// Created by Dawid Drozd aka Gelldur on 8/10/16.
//

#include "ScreenCreator.h"

#include <exception/Fail.h>

Screen* ScreenCreator::create(const std::string& name)
{
	return create(name, Nodect("nullObject-screen:" + name, nullptr));
}

Screen* ScreenCreator::create(const std::string& name, Nodect&& nodeScreen)
{
	Fail(__FILE__, __func__, __LINE__).add("No such screen:").add(name).report();
	return nullptr;
}
