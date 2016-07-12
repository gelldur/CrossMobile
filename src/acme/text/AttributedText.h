//
// Created by Dawid Drozd aka Gelldur on 7/11/16.
//

#pragma once

#include <vector>
#include <string>

class AttributedText
{
public:
	AttributedText& append(const char* text);
	AttributedText& append(const std::string& text);
	AttributedText& appendImage(const std::string& name);

	enum class ElementType
	{
		TEXT, IMAGE_LOCAL
	};

	struct Element
	{
		Element(const ElementType& type, const std::string& value)
				: type(type)
				, value(value)
		{
		}

		ElementType type;
		std::string value;
	};

	const std::vector<Element>& getElements() const
	{
		return _text;
	}

private:
	std::vector<Element> _text;
};


