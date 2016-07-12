//
// Created by Dawid Drozd aka Gelldur on 6/15/16.
//

#pragma once

#include <component/Component.h>

class AttributedText;

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

	virtual void setTextAttributed(const AttributedText& attributedText);

	COMPONENT_TO_STRING(Text)

	static Text& getNullObject();
};

class NullText : public Text
{
public:
	virtual void setText(const char* text) override;

	virtual void setText(const std::string& text) override;

	virtual void setTextColor(int color) override;

	virtual void setTextAttributed(const AttributedText& attributedText) override;
};
