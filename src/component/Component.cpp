//
// Created by Dawid Drozd aka Gelldur on 07.03.16.
//

#include "Component.h"
#include <component/Nodect.h>

Component::~Component()
{
	_owner = nullptr;
}

Context* Component::getContext() const
{
	return getOwner()->getContext();
}
