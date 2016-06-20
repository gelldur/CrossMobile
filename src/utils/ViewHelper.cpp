//
// Created by Dawid Drozd aka Gelldur on 6/15/16.
//
#include "ViewHelper.h"

#include <component/view/TextProtocol.h>
#include <log.h>

namespace ViewHelper
{

void loadImage(NativeObject& view, const std::string& url)
{
	WLOG("Function %s not implemented: %s:%d", __func__, __FILE__, __LINE__);
}

void setText(NativeObject& view, const std::string& text)
{
	auto& textView = view.getComponent<TextProtocol>();
	textView.setText(text);
}

}
