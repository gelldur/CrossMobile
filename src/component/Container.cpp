//
// Created by Dawid Drozd aka Gelldur on 6/17/16.
//

#include "Container.h"
#include <bridge/NativeObject.h>

Container& Container::getNullObject()
{
	static NullContainer nullObject;
	return nullObject;
}

NativeObject& Container::get(const std::string& tag)
{
	auto found = _managed.find(tag);
	if (found == _managed.end())
	{
		WLOG("Tag not found: %s", tag.c_str());
		return *NativeObject::nullObject;
	}

	return found->second;
}

Container& Container::add(NativeObject&& nativeObject)
{
	if (_managed.find(nativeObject.getTag()) != _managed.end())
	{
		throw std::runtime_error(std::string("Already added this tag") + nativeObject.getTag());
	}
	const std::string key = nativeObject.getTag();//because of move semantics
	_managed.emplace(key, std::move(nativeObject));

	return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// NullContainer
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

NativeObject& NullContainer::get(const std::string& tag)
{
	WLOG("NullObject ignoring call: %s in: %s:%d", __func__, __FILE__, __LINE__);
	return *NativeObject::nullObject;
}

