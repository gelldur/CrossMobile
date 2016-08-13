//
// Created by Dawid Drozd aka Gelldur on 8/9/16.
//

#include "AndroidBridge.h"
#include <log.h>

namespace CrossMobile
{

namespace Platform
{

std::string AndroidBridge::getWritablePath() const
{
	WLOG("Function %s not implemented: %s:%d", __func__, __FILE__, __LINE__);
	return "";
}

}
}

