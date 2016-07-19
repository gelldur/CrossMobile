//
// Created by Dawid Drozd aka Gelldur on 7/19/16.
//

#pragma once

#include <string>
#include <map>

class Preferences
{
public:
	void setValue(const std::string& key, const std::string& value);

	std::string getValue(const std::string& key, const std::string& defaultValue);

private:
	std::map<std::string, std::string> _cache;
};


