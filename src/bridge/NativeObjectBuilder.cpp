//
// Created by Dawid Drozd aka Gelldur on 6/21/16.
//

#include "NativeObjectBuilder.h"
#include <component/Container.h>

namespace NativeObjectBuilder
{

create::create(const std::string& tag, std::shared_ptr<Context> context)
		: _nativeObject(tag, context)
{
}

NativeObject create::build()
{
	if (_containerForObject != nullptr && _containerForObject->count() > 0)
	{
		_nativeObject.addComponent(std::move(_containerForObject));
	}
	return std::move(_nativeObject);
}

create& create::nestObject(NativeObject&& nativeObject)
{
	if (_containerForObject == nullptr)
	{
		_containerForObject = std::make_unique<Container>();
	}
	_containerForObject->add(std::move(nativeObject));
	return *this;
}

}

