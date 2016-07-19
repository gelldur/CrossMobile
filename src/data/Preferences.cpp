//
// Created by Dawid Drozd aka Gelldur on 7/19/16.
//

#include "Preferences.h"

void Preferences::setValue(const std::string& key, const std::string& value)
{
	_cache[key] = value;
}

std::string Preferences::getValue(const std::string& key, const std::string& defaultValue)
{
	auto found = _cache.find(key);
	if (found != _cache.end())
	{
		return found->second;
	}

	_cache[key] = defaultValue;
	//TODO use leveldb https://github.com/google/leveldb
	return defaultValue;
}
