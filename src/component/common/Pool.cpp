//
// Created by Dawid Drozd aka Gelldur on 8/11/16.
//

#include "Pool.h"

#include <log.h>

Pool& Pool::getNullObject()
{
	static NullPool nullObject;
	return nullObject;
}

Poco::Any* Pool::getObject(const std::string& identifier)
{
	auto found = _objects.find(identifier);
	if (found == _objects.end())
	{
		WLOG("Pool not found: %s", identifier.c_str());
		static Poco::Any empty;
		return &empty;
	}
	return found->second.get();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// NullPool
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Poco::Any* NullPool::getObject(const std::string& identifier)
{
	WLOG("Function %s not implemented: %s:%d", __func__, __FILE__, __LINE__);
	static Poco::Any empty;
	return &empty;
}

void NullPool::add(const std::string& identifier, Poco::Any&& data)
{
	WLOG("Function %s not implemented: %s:%d", __func__, __FILE__, __LINE__);
}
