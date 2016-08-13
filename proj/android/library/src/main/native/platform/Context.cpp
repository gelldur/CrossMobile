//
// Created by Dawid Drozd aka Gelldur on 6/17/16.
//

#include "Context.h"

#include <exception/Fail.h>

JniObject& Context::getNative()
{
	if (_nativeObject == false)
	{
		Fail(__FILE__, __func__, __LINE__).report();
	}
	return _nativeObject;
}
