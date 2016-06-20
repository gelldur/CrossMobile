//
// Created by Dawid Drozd aka Gelldur on 6/15/16.
//

#pragma once

#include <Component.h>

/**
 * Implementation is environment specific
 */
class TextProtocol : public Component
{
	using inherited = Component;
public:
	TextProtocol()
			: inherited()
	{
	}

	virtual void setText(const char* text);
	virtual void setText(const std::string& text);

	virtual void setTextColor(int color);

	COMPONENT_TO_STRING(TextProtocol)

	static TextProtocol& getNullObject();
};


