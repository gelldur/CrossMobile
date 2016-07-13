//
// Created by Dawid Drozd aka Gelldur on 6/21/16.
//

#pragma once

#include <string>

#include "Nodect.h"
#include "Container.h"

namespace NodectBuilder
{

class create
{
public:
	create(const std::string& tag, std::shared_ptr<Context> context);

	template<class... Args>
	create(const std::string& tag, Args&& ... args)
			: _node(tag, std::make_shared<Context>(std::forward<Args>(args)...))
	{
	}

	create(create&&) = delete;
	create(const create&) = delete;
	create& operator=(const create&) = delete;

	template<class T, class... Args>
	create& addComponent(Args&& ... args)
	{
		static_assert(std::is_base_of<Component, T>(), "T must be child of Component");
		_node.addComponent<T>(std::forward<Args>(args)...);
		return *this;
	}

	create& nestObject(Nodect&& nodect);

	create& nest(Nodect&& nodect)
	{
		return nestObject(std::move(nodect));
	}

	Nodect build();

private:
	Nodect _node;
	std::unique_ptr<Container> _containerForObject;
};

template<>
inline create& create::addComponent<Container>()
{
	if (_containerForObject == nullptr)
	{
		_containerForObject = std::make_unique<Container>();
	}
	return *this;
}

}
