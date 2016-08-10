//
// Created by Dawid Drozd aka Gelldur on 8/10/16.
//

#pragma once

#include <string>
#include <memory>
#include <component/Nodect.h>

class Screen;

class ScreenCreator
{
public:
	virtual ~ScreenCreator() = default;

	virtual Screen* create(const std::string& name);
	virtual Screen* create(const std::string& name, Nodect&& nodeScreen);

};
