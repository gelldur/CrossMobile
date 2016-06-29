//
// Created by Dawid Drozd aka Gelldur on 6/17/16.
//

#include "Nodect.h"
#include <component/Component.h>

Nodect* Nodect::nullObject = new Nodect("nullObject", nullptr);

Nodect::Nodect(const std::string& tag, std::shared_ptr<Context> context)
		: _context(context)
		, _tag(tag)
{
	//DLOG("Normal ctor %s", tag.c_str());
}

Nodect::Nodect(Nodect&& other)
		: _context(std::move(other._context))
		, _tag(std::move(other._tag))
		, _components(std::move(other._components))
{
	//DLOG("Move ctor %s", _tag.c_str());
	for (auto& component : _components)
	{
		component.second->_owner = this;//Changing of owner!
	}
}

//Nodect::Nodect(const Nodect& other)
//		: _context(other._context)
//		, _tag(other._tag + "_cpy")
//		, _components(other._components)
//{
//	DLOG("Copy ctor %s", _tag.c_str());
//}
//
//Nodect& Nodect::operator=(const Nodect& other)
//{
//	DLOG("Asign operator %s -> %s", _tag.c_str(),other._tag.c_str());
//	_context = other._context;
//	_tag = other._tag;
//	_components = other._components;
//}

Nodect::~Nodect()
{
	//DLOG("# Dtor %s - clean:%s", _tag.c_str(), (_context == nullptr ? "yes" : "no"));
}

void Nodect::addComponentWithId(int id, std::unique_ptr<Component>&& component)
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
