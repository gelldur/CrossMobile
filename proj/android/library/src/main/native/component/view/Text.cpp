//
// Created by Dawid Drozd aka Gelldur on 8/12/16.
//

#include <component/view/Text.h>

#include <log.h>
#include <platform/Context.h>
#include <JniObject.h>

void Text::setText(const char* text)
{
	setText(std::string(text));
}

void Text::setText(const std::string& text)
{
	JniObject charSequence("java.lang.CharSequence");
	getContext()->getNative().callSignedVoid("setText", JniObject::createVoidSignature(charSequence), text);
}

void Text::setTextColor(int color)
{
	getContext()->getNative().callVoid("setTextColor", color);
}

void Text::setTextAttributed(const AttributedText& attributedText)
{
	WLOG("Function %s not implemented: %s:%d", __func__, __FILE__, __LINE__);
}
