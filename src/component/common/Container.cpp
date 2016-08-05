//
// Created by Dawid Drozd aka Gelldur on 6/17/16.
//

#include "Container.h"
#include <component/Nodect.h>

Container& Container::getNullObject()
{
	static NullContainer nullObject;
	return nullObject;
}

Nodect& Container::get(const std::string& tag)
{
	auto found = _managed.find(tag);
	if (found == _managed.end())
	{
		WLOG("Tag not found: %s", tag.c_str());
		return *Nodect::nullObject;
	}

	return found->second;
}

Container& Container::add(Nodect&& nodect)
{
	if (_managed.find(nodect.getTag()) != _managed.end())
	{
		throw std::runtime_error(std::string("Already added this tag: ") + nodect.getTag());
	}
	const std::string key = nodect.getTag();//because of move semantics
	_managed.emplace(key, std::move(nodect));

	return *this;
}

bool Container::remove(const std::string& tag)
{
	auto found = _managed.find(tag);
	if (found == _managed.end())
	{
		WLOG("Not removed, not found: %s", tag.c_str());
		return false;
	}

	_managed.erase(found);
	return true;
}

void Container::removeAll()
{
	_managed.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// NullContainer
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Nodect& NullContainer::get(const std::string& tag)
{
	WLOG("NullObject ignoring call: %s(%s) in: %s:%d", __func__, tag.c_str(), __FILE__, __LINE__);
	return *Nodect::nullObject;
}

bool NullContainer::remove(const std::string& tag)
{
	WLOG("NullObject ignoring call: %s(%s) in: %s:%d", __func__, tag.c_str(), __FILE__, __LINE__);
	return false;
}

void NullContainer::removeAll()
{
	WLOG("NullObject ignoring call: %s in: %s:%d", __func__, __FILE__, __LINE__);
}
