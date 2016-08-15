//
// Created by Dawid Drozd aka Gelldur on 7/28/16.
//

#pragma once

#include <string>

namespace CrossMobile
{

namespace Platform
{

class Bridge
{
public:
	virtual ~Bridge()
	{
	}

	static Bridge* create();

	std::string getWritablePath();
private:
	virtual std::string getWritablePathNative() const = 0;
};

class DummyBridge : public Bridge
{
public:
	virtual std::string getWritablePathNative() const override;
};

}
}
