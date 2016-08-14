//
// Created by Dawid Drozd aka Gelldur on 07.03.16.
//

#pragma once

#include <string>
#include <cassert>
#include <typeinfo>

#define COMPONENT_TO_STRING(NAME) virtual const char* toString() const override{ return #NAME;}

class Nodect;

class Context;

class Component
{
public:
	friend class Nodect;

	Component() = default;
	virtual ~Component();

	Component(Component const&) = delete;
	Component& operator=(Component const&) = delete;

	virtual const char* toString() const = 0;

	bool isNullObject() const
	{
		return _owner == nullptr;
	}

protected:
	Nodect* getOwner() const
	{
		assert(_owner != nullptr);
		return _owner;
	}

	Context* getContext() const;

	/**
	 * Called when Component is added to Nodect
	 */
	virtual void onEnter()
	{
	}

	/**
	 * Called when Component is removed to Nodect
	 */
	virtual void onExit()
	{
	}

private:
	Nodect* _owner = nullptr;
};

template<class T>
inline size_t getIdForType()
{
	static size_t id = typeid(T).hash_code();
	return id;
}

