//
// Created by Dawid Drozd aka Gelldur on 07.03.16.
//

#pragma once

#include <string>
#include <cassert>

#define COMPONENT_TO_STRING(NAME) virtual const char* toString() const override{ return #NAME;}

class NativeObject;

class Component
{
public:
	friend class NativeObject;

	Component() = default;
	virtual ~Component() = default;

	Component(Component const&) = delete;
	Component& operator=(Component const&) = delete;

	virtual const char* toString() const = 0;

protected:
	bool isNullObject() const
	{
		return _owner == nullptr;
	}

	NativeObject* getOwner() const
	{
		return _owner;
	}

private:
	NativeObject* _owner = nullptr;
};

//TODO check getIdForType and move to other dir
static int counter = 0;

template<class T>
inline int getIdForType()
{
	static int id = ++counter;
	return id;
}

