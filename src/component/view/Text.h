//
// Created by Dawid Drozd aka Gelldur on 6/15/16.
//

#pragma once

#include <Component.h>

/**
 * Implementation is environment specific
 */
class Text : public Component
{
	using inherited = Component;
public:

	virtual void setText(const char* text);
	virtual void setText(const std::string& text);

	virtual void setTextColor(int color);

	COMPONENT_TO_STRING(Text)

	static Text& getNullObject();
};

class NullText : public Text
{
public:
	virtual void setText(const char* text) override;

	virtual void setText(const std::string& text) override;

	virtual void setTextColor(int color) override;
};
