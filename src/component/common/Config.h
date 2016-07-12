//
// Created by Dawid Drozd aka Gelldur on 7/11/16.
//

#pragma once

#include <component/Component.h>

#include <map>
#include <string>

namespace Dexode
{
namespace Component
{

class Config : public ::Component
{
	using inherited = Component;
public:

	virtual int getValue(const std::string& name, const int defaultValue);
	virtual void setValue(const std::string& name, const int value);

	COMPONENT_TO_STRING(Config)

	static Config& getNullObject();

private:
	std::map<std::string, int> _numbers;
};

class NullConfig : public Config
{
	virtual int getValue(const std::string& name, const int defaultValue) override;
	virtual void setValue(const std::string& name, const int value) override;
};

}
}
