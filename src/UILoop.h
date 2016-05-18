//
// Created by Dawid Drozd aka Gelldur on 5/16/16.
//

#pragma once

#include <Poco/BasicEvent.h>

class UILoop
{
public:
	/**
	 * Sample how to register for event:
	 * uiTick += Poco::delegate(this, &Provider::onEvent);
	 *
	 * Sample how to unregister for event:
	 * uiTick -= Poco::delegate(this, &Provider::onEvent);
	 */
	Poco::BasicEvent<int> uiTick;

	/**
	 * Method called from UI thread
	 */
	void onTick()
	{
		if (uiTick.empty() == false)
		{
			int a = 0;//Dummy integer for now
			uiTick.notify(this, a);
		}
	}
};


