//
// Created by Dawid Drozd aka Gelldur on 6/30/16.
//

#include "NodectHelper.h"
#include "component/common/Container.h"

namespace NodectHelper
{

Nodect& find(const Nodect& nodect, const std::string& tag)
{
	return nodect.getComponent<Container>().get(tag);
}

void nest(Nodect& owner, Nodect&& nodect)
{
	owner.getComponent<Container>().add(std::move(nodect));
}

Nodect& remove(Nodect& owner, const std::string& nodectName)
{
	owner.getComponent<Container>().remove(nodectName);
	return owner;
}

void clear(Nodect& owner)
{
	owner.getComponent<Container>().removeAll();
}

}
