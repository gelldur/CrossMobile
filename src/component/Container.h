//
// Created by Dawid Drozd aka Gelldur on 6/17/16.
//

#pragma once

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
	Container()
			: inherited()
	{
	}

	/**
	 * @return nullptr if element not found
	 */
	virtual NativeObject& get(const std::string& tag);

	COMPONENT_TO_STRING(Container)

	static Container& getNullObject();
};


