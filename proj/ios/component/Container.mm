//
// Created by Dawid Drozd aka Gelldur on 6/17/16.
//

#include <component/Container.h>

NativeObject& Container::get(const std::string& tag)
{
	WLOG("Function %s not implemented: %s:%d", __func__, __FILE__, __LINE__);
	return *NativeObject::nullObject;
}

