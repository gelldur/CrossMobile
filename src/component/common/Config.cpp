//
// Created by Dawid Drozd aka Gelldur on 7/11/16.
//

#include "Config.h"

#include <log.h>

namespace CrossMobile
{
namespace Component
{

long long Config::getValue(const std::string& name, const long long defaultValue)
{
	auto found = _numbers.find(name);
	return found != _numbers.end() ? found->second : defaultValue;
}

std::string Config::getValue(const std::string& name, const std::string& defaultValue)
{
	auto found = _strings.find(name);
	return found != _strings.end() ? found->second : defaultValue;
}

void Config::setValue(const std::string& name, const long long value)
{
	_numbers[name] = value;
}

void Config::setValue(const std::string& name, const std::string& value)
{
	_strings[name] = value;
}

Config& Config::getNullObject()
{
	static NullConfig nullObject;
	return nullObject;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// NullConfig
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

long long NullConfig::getValue(const std::string& name, const long long defaultValue)
{
	WLOG("NullObject ignoring call: %s in: %s:%d", __func__, __FILE__, __LINE__);
	return defaultValue;
}

std::string NullConfig::getValue(const std::string& name, const std::string& defaultValue)
{
	WLOG("NullObject ignoring call: %s in: %s:%d", __func__, __FILE__, __LINE__);
	return defaultValue;
}

void NullConfig::setValue(const std::string& name, const long long value)
{
	WLOG("NullObject ignoring call: %s in: %s:%d", __func__, __FILE__, __LINE__);
}

void NullConfig::setValue(const std::string& name, const std::string& value)
{
	WLOG("NullObject ignoring call: %s in: %s:%d", __func__, __FILE__, __LINE__);
}

}
}
