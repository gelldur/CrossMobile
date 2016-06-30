//
// Created by Dawid Drozd aka Gelldur on 6/17/16.
//

#include "Context.h"

#import <UIKit/UIKit.h>

#include <exception/Fail.h>

id Context::getNative()
{
	if(_nativeObject == nil)
	{
		Fail(__FILE__,__func__,__LINE__).report();
	}
	return _nativeObject;
}
