//
// Created by Dawid Drozd aka Gelldur on 6/21/16.
//

#include "NodectBuilder.h"
#include <component/Container.h>

namespace NodectBuilder
{

create::create(const std::string& tag, std::shared_ptr<Context> context)
		: _node(tag, context)
{
}

Nodect create::build()
{
	if (_containerForObject != nullptr && _containerForObject->count() > 0)
	{
		_node.addComponent(std::move(_containerForObject));
	}
	return std::move(_node);
}

create& create::nestObject(Nodect&& nodect)
{
	if (_containerForObject == nullptr)
	{
		_containerForObject = std::make_unique<Container>();
	}
	_containerForObject->add(std::move(nodect));
	return *this;
}

}
