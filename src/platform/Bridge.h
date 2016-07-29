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

	virtual std::string getWritablePath() const = 0;
};

class DummyBridge : public Bridge
{
public:
	virtual std::string getWritablePath() const override;
};

}
}
