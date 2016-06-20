//
// Created by Dawid Drozd aka Gelldur on 6/20/16.
//

#pragma once

#include "Visibility.h"
#include <log.h>

class NullVisibility : public Visibility
{
public:
	virtual void setVisibility(Visible visible) override
	{
		WLOG("NullObject ignoring call: %s in: %s:%d", __func__, __FILE__, __LINE__);
	}
};

Visibility& Visibility::getNullObject()
{
	static NullVisibility nullObject;
	return nullObject;
}
