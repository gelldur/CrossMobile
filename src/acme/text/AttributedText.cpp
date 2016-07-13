//
// Created by Dawid Drozd aka Gelldur on 7/11/16.
//

#include "AttributedText.h"

AttributedText& AttributedText::append(const char* text)
{
	_text.emplace_back(ElementType::TEXT, text);
	return *this;
}

AttributedText& AttributedText::append(const std::string& text)
{
	_text.emplace_back(ElementType::TEXT, text);
	return *this;
}

AttributedText& AttributedText::appendImage(const std::string& name)
{
	_text.emplace_back(ElementType::IMAGE_LOCAL, name);
	return *this;
}

AttributedText& AttributedText::space(const int count)
{
	_text.emplace_back(ElementType::TEXT, std::string(count, ' '));
	return *this;
}
