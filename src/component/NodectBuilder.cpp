//
// Created by Dawid Drozd aka Gelldur on 6/21/16.
//

#include "NodectBuilder.h"
#include "ComponentSerializer.h"

namespace NodectBuilder
{

create::create(const std::shared_ptr<Context>& context, const std::string& tag)
		: _node(tag, context)
{
}

Nodect create::build()
{
	if (_containerForObject != nullptr)
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

create& create::addComponentByName(const std::string& componentName)
{
	ComponentSerializer::addComponentByName(*this, componentName);
	return *this;
}

}
