//
// Created by Dawid Drozd aka Gelldur on 8/9/16.
//

#pragma once

#include <platform/Bridge.h>

namespace CrossMobile
{

namespace Platform
{

class AndroidBridge : public Bridge
{
private:
	virtual std::string getWritablePathNative() const override;
};

}
}
