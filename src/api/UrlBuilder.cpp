//
// Created by Dawid Drozd aka Gelldur on 14.03.16.
//

#include "UrlBuilder.h"

UrlBuilder::UrlBuilder()
{
}

UrlBuilder::UrlBuilder(const std::string& url)
{
	appendUrl(url);
}

UrlBuilder& UrlBuilder::appendUrl(const std::string& string)
{
	_builder.setPath(_builder.getPath() + string);
	return *this;
}

UrlBuilder& UrlBuilder::appendUrl(const long long value)
{
	_builder.setPath(_builder.getPath() + std::to_string(value));
	return *this;
}

std::string UrlBuilder::build()
{
	return _builder.toString();
}

