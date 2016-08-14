//
// Created by Dawid Drozd aka Gelldur on 8/11/16.
//

#pragma once

#include <map>
#include <memory>

#include <component/Component.h>
#include <Poco/Any.h>

//DeadPool :)
class Pool : public Component
{
	using inherited = Component;
public:
	virtual Poco::Any* getObject(const std::string& identifier);

	virtual void add(const std::string& identifier, Poco::Any&& data)
	{
		_objects[identifier] = std::unique_ptr<Poco::Any>(new Poco::Any(std::move(data)));
	}

	COMPONENT_TO_STRING(Pool)

	static Pool& getNullObject();

private:
	std::map<std::string, std::unique_ptr<Poco::Any>> _objects;
};

class NullPool : public Pool
{
public:
	virtual Poco::Any* getObject(const std::string& identifier) override;

	virtual void add(const std::string& identifier, Poco::Any&& data) override;
};
