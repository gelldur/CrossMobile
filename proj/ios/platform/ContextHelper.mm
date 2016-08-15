//
// Created by Dawid Drozd aka Gelldur on 8/15/16.
//

#include "ContextHelper.h"

namespace ContextHelper
{

id getNative(Context* context)
{
	return (__bridge id)context->getNative();
}

void* wrap(id nativeObject)
{
	return (__bridge void*)nativeObject;
}

}
