//
// Created by Dawid Drozd aka Gelldur on 5/17/16.
//

#pragma once

#include <string>
#include <vector>

#include <Poco/Any.h>

class ListDataSource
{
public:
	ListDataSource(size_t capacity = 128)
	{
		_identifiers.reserve(capacity);
		_data.reserve(capacity);
	}

	size_t size()
	{
		return _identifiers.size();
	}

	const std::string& getIdentifier(size_t index)
	{
		return _identifiers[index];
	}

	template<class T>
	const T getData(size_t index) const
	{
		return Poco::AnyCast<T>(_data[index]);
	}

	const Poco::Any& getDataRaw(size_t index) const
	{
		return _data[index];
	}

	void add(const std::string&& identifier, const Poco::Any&& data = {})
	{
		_identifiers.push_back(std::move(identifier));
		_data.push_back(std::move(data));
	}

	const std::vector<std::string>& getIdentifiers() const
	{
		return _identifiers;
	}

private:
	std::vector<std::string> _identifiers;
	std::vector<Poco::Any> _data;
};
