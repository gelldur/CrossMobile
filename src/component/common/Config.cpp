//
// Created by Dawid Drozd aka Gelldur on 7/11/16.
//

#include "Config.h"

#include <log.h>

namespace CrossMobile
{
namespace Component
{

int Config::getValue(const std::string& name, const int defaultValue)
{
	auto found = _numbers.find(name);
	return found != _numbers.end() ? found->second : defaultValue;
}

void Config::setValue(const std::string& name, const int value)
{
	_numbers[name] = value;
}

Config& Config::getNullObject()
{
	static NullConfig nullObject;
	return nullObject;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// NullImage
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int CrossMobile::Component::NullConfig::getValue(const std::string& name, const int defaultValue)
{
	WLOG("NullObject ignoring call: %s in: %s:%d", __func__, __FILE__, __LINE__);
	return defaultValue;
}

void CrossMobile::Component::NullConfig::setValue(const std::string& name, const int value)
{
	WLOG("NullObject ignoring call: %s in: %s:%d", __func__, __FILE__, __LINE__);
}

}
}
