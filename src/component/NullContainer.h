//
// Created by Dawid Drozd aka Gelldur on 6/20/16.
//

#pragma once

#include "Container.h"
#include <log.h>

class NullContainer : public Container
{
public:
	virtual NativeObject& get(const std::string& tag) override
	{
		WLOG("NullObject ignoring call: %s in: %s:%d", __func__, __FILE__, __LINE__);
		return *NativeObject::nullObject;
	}
};

Container& Container::getNullObject()
{
	static NullContainer nullObject;
	return nullObject;
}
