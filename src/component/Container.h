//
// Created by Dawid Drozd aka Gelldur on 6/17/16.
//

#pragma once

#include <map>

#include <component/Component.h>
#include <component/Nodect.h>

class Nodect;

/**
 * Implementation is environment specific
 */
class Container : public Component
{
	using inherited = Component;
public:
	using InitType = std::initializer_list<Nodect>;




	Container& add(Nodect&& nodect);

	virtual Nodect& get(const std::string& tag);

	virtual bool remove(const std::string& tag);

	size_t count() const
	{
		return _managed.size();
	}

	COMPONENT_TO_STRING(Container)

	static Container& getNullObject();

private:
	std::map<std::string, Nodect> _managed;
};

class NullContainer : public Container
{
public:
	virtual Nodect& get(const std::string& tag) override;
	virtual bool remove(const std::string& tag) override;
};
