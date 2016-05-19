//
// Created by Dawid Drozd aka Gelldur on 5/19/16.
//

#pragma once

namespace Api
{

class Async
{
public:
	virtual ~Async() = default;

	/**
	 * Called in background thread
	 */
	virtual void onDoInBackground()
	{
	}

	/**
	 * Called on UI thread
	 */
	virtual void onPostExecute()
	{
	}
};

}
