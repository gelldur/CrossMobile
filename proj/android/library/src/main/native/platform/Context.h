//
// Created by Dawid Drozd aka Gelldur on 6/17/16.
//

#pragma once

#include <Android.h>

class Context
{
public:
	Context(jobject nativeObject)
			: _nativeObject(nativeObject)
	{
	}

	jobject getNative();

private:
	jobject _nativeObject;
};


