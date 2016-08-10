//
// Created by Dawid Drozd aka Gelldur on 8/10/16.
//

#include "ScreenCreator.h"

Screen* ScreenCreator::create(const std::string& name)
{
	return create(name, Nodect("nullObject-screen:" + name, nullptr));
}

Screen* ScreenCreator::create(const std::string& name, Nodect&& nodeScreen)
{
	DLOG("%s:%s:%d", __FILE__, __func__, __LINE__);
	ELOG("No such screen: %s", name.c_str());
	throw std::runtime_error(std::string("No such screen: ") + name);
}
