//
// Created by Dawid Drozd aka Gelldur on 6/17/16.
//

#include "NativeObject.h"
#include <Component.h>

#include <component/view/NullTextProtocol.h>
#include <component/view/NullVisibility.h>
#include <component/NullContainer.h>

NativeObject* NativeObject::nullObject = new NativeObject("nullObject", nullptr);

NativeObject::NativeObject(const std::string& tag, std::shared_ptr<Context> context)
		: _context(context)
		, _tag(tag)
{
	DLOG("Normal ctor %s", tag.c_str());
}

NativeObject::NativeObject(NativeObject&& other)
		: _context(std::move(other._context))
		, _tag(std::move(other._tag))
		, _components(std::move(other._components))
{
	DLOG("Move ctor %s", _tag.c_str());
	for (auto& component : _components)
	{
		component.second->_owner = this;//Changing of owner!
	}
}

NativeObject::~NativeObject()
{
	DLOG("# Dtor %s - clean:%s", _tag.c_str(), (_context == nullptr ? "yes" : "no"));
}

void NativeObject::addComponentWithId(int id, std::unique_ptr<Component>&& component)
{
	if (_context == nullptr)
	{
		WLOG("NullObject ignoring call: %s in: %s:%d", __func__, __FILE__, __LINE__);
		return;
	}
	if (_components.find(id) != _components.end())
	{
		throw std::runtime_error(std::string("Component already added ") + component->toString());
	}

	assert(component->_owner == nullptr);
	component->_owner = this;
	_components[id] = std::move(component);
}
