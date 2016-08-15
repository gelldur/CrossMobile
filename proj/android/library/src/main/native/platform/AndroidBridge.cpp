//
// Created by Dawid Drozd aka Gelldur on 8/9/16.
//

#include "AndroidBridge.h"

#include <log.h>
#include <JniObject.h>
#include <platform/Context.h>

namespace CrossMobile
{

namespace Platform
{

std::string AndroidBridge::getWritablePathNative() const
{
	auto& appContext = Context::getApplicationContext();

	JniObject file = appContext.call("getFilesDir", JniObject("java.io.File"));
	std::string path = file.call("getPath", std::string(""));
	return path;
}

}
}

