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

	template<class... Args>
	create(const std::string& tag, Args&& ... args)
			: _nativeObject(tag, std::make_shared<Context>(std::forward<Args>(args)...))
	{
	}

	create(create&&) = delete;
	create(const create&) = delete;
	create& operator=(const create&) = delete;

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
