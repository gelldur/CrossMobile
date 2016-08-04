//
// Created by Dawid Drozd aka Gelldur on 7/11/16.
//

#pragma once

#include <component/Component.h>

#include <map>
#include <string>

namespace CrossMobile
{
namespace Component
{

class Config : public ::Component
{
	using inherited = Component;
public:

	virtual long long getValue(const std::string& name, const long long defaultValue);
	virtual std::string getValue(const std::string& name, const std::string& defaultValue);

	virtual void setValue(const std::string& name, const long long value);
	virtual void setValue(const std::string& name, const std::string& value);

	COMPONENT_TO_STRING(Config)

	static Config& getNullObject();

private:
	std::map<std::string, long long> _numbers;
	std::map<std::string, std::string> _strings;
};

class NullConfig : public Config
{
	virtual long long getValue(const std::string& name, const long long defaultValue) override;
	virtual std::string getValue(const std::string& name, const std::string& defaultValue) override;
	virtual void setValue(const std::string& name, const long long value) override;
	virtual void setValue(const std::string& name, const std::string& value) override;
};

}
}
