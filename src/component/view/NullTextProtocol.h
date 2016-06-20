//
// Created by Dawid Drozd aka Gelldur on 6/20/16.
//

#pragma once

#include <log.h>
#include "TextProtocol.h"

class NullTextProtocol : public TextProtocol
{
public:
	virtual void setText(const char* text) override
	{
		WLOG("NullObject ignoring call: %s in: %s:%d", __func__, __FILE__, __LINE__);
	}

	virtual void setText(const std::string& text) override
	{
		WLOG("NullObject ignoring call: %s in: %s:%d", __func__, __FILE__, __LINE__);
	}

	virtual void setTextColor(int color) override
	{
		WLOG("NullObject ignoring call: %s in: %s:%d", __func__, __FILE__, __LINE__);
	}
};

TextProtocol& TextProtocol::getNullObject()
{
	static NullTextProtocol nullObject;
	return nullObject;
}
