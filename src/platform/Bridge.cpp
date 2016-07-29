//
// Created by Dawid Drozd aka Gelldur on 7/28/16.
//

#include "Bridge.h"

#include <log.h>

std::string CrossMobile::Platform::DummyBridge::getWritablePath() const
{
	WLOG("Function %s not implemented: %s:%d", __func__, __FILE__, __LINE__);
	return "";
}
