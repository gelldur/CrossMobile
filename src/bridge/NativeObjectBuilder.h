//
// Created by Dawid Drozd aka Gelldur on 6/21/16.
//

#pragma once

#include <string>

#include "NativeObject.h"

class Container;

namespace NativeObjectBuilder
{

class create
{
public:
	create(const std::string& tag, std::shared_ptr<Context> context);

	template<class T, class... Args>
	create& addComponent(Args&& ... args)
	{
		static_assert(std::is_base_of<Component, T>(), "T must be child of Component");
		_nativeObject.addComponent<T>(std::forward<Args>(args)...);
		return *this;
	}

	create& nestObject(NativeObject&& nativeObject);

	NativeObject build();

private:
	NativeObject _nativeObject;
	std::unique_ptr<Container> _containerForObject;
};

}
