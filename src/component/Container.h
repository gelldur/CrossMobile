//
// Created by Dawid Drozd aka Gelldur on 6/17/16.
//

#pragma once

#include <map>

#include <Component.h>
#include <bridge/NativeObject.h>

class NativeObject;

/**
 * Implementation is environment specific
 */
class Container : public Component
{
	using inherited = Component;
public:
	using InitType = std::initializer_list<NativeObject>;

	Container()
			: inherited()
	{
	}


	Container& add(NativeObject&& nativeObject);

	virtual NativeObject& get(const std::string& tag);

	size_t count() const
	{
		return _managed.size();
	}

	COMPONENT_TO_STRING(Container)

	static Container& getNullObject();

private:
	std::map<std::string, NativeObject> _managed;
};
