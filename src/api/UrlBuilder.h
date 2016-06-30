//
// Created by Dawid Drozd aka Gelldur on 14.03.16.
//

#pragma once

#include <vector>
#include <string>
#include <sstream>

#include <Poco/URI.h>

class UrlBuilder
{
public:
	UrlBuilder();
	UrlBuilder(const std::string& url);

	UrlBuilder& appendUrl(const std::string& string);

	UrlBuilder& appendUrl(const long long value);

	template<class Type>
	UrlBuilder& appendQuery(const std::string& key, const Type& value)
	{
		_builder.addQueryParameter(key, std::to_string(value));
		return *this;
	}

	UrlBuilder& appendQuery(const std::string& key, const char* const value)
	{
		_builder.addQueryParameter(key, value);
		return *this;
	}


	template<class Type>
	UrlBuilder& appendQuery(const std::string& key, const std::vector<Type>& values)
	{
		if (values.size() < 1)
		{
			_builder.addQueryParameter(key, "[]");
			return *this;
		}
		std::stringstream stream;
		stream << '[' << values[0];
		for (unsigned i = 1; i < values.size(); ++i)
		{
			stream << ',' << values[i];
		}
		stream << ']';
		_builder.addQueryParameter(key, stream.str());
		return *this;
	}

	std::string build();

private:
	Poco::URI _builder;
};

template<>
inline UrlBuilder& UrlBuilder::appendQuery<std::string>(const std::string& key, const std::string& value)
{
	_builder.addQueryParameter(key, value);
	return *this;
}
