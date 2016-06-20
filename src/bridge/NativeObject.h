//
// Created by Dawid Drozd aka Gelldur on 6/17/16.
//

#pragma once

#include <map>
#include <string>
#include <memory>

#include <log.h>
#include <Component.h>
#include <utils/Utils.h>

class Context;

class NativeObject
{
public:
	NativeObject(const std::string& tag, Context* context)
			: _context(context)
	{
	}

	NativeObject(NativeObject const&) = delete;
	NativeObject& operator=(NativeObject const&) = delete;

	void addComponent(int id, std::unique_ptr<Component> component);

	template<class T, class... Args>
	void addComponent(Args&& ... args)
	{
		if (_context == nullptr)
		{
			WLOG("NullObject(%s) ignoring call: %s in: %s:%d", getTag(), __func__, __FILE__, __LINE__);
			return;
		}

		auto component = std::make_unique<T>(std::forward<Args>(args)...);
		addComponent(getIdForType<T>(), component);
	}

	template<class T>
	T& getComponent()
	{
		const int id = getIdForType<T>();
		auto found = _components.find(id);
		if (found == _components.end())
		{
			auto& nullObject = T::getNullObject();
			WLOG("Missing component: %s", nullObject.toString());

			return nullObject;
		}

		T* casted = dynamic_cast<T*>(found->second.get());
		if (casted == nullptr)
		{
			throw std::bad_cast();
		}
		return *casted;
	}

	const std::string& getTag() const
	{
		return _tag;
	}

	Context* getContext() const
	{
		assert(_context != nullptr);
		return _context;
	}

	static NativeObject* nullObject;

private:
	Context* _context;
	std::string _tag;
	std::map<int, std::unique_ptr<Component>> _components;
};
