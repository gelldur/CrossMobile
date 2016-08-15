//
// Created by Dawid Drozd aka Gelldur on 7/28/16.
//

#pragma once

#include <platform/Bridge.h>

namespace CrossMobile
{

namespace Platform
{

class IosBridge : public Bridge
{
private:
	virtual std::string getWritablePathNative() const override;
};

}
}
