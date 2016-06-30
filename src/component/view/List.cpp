//
// Created by Dawid Drozd aka Gelldur on 6/30/16.
//

#include "List.h"

#include <log.h>

namespace Dexode
{
namespace Component
{

#ifndef PLATFORM_IOS

void List::reloadData()
{
	WLOG("Function %s not implemented: %s:%d", __func__, __FILE__, __LINE__);
}

#endif

List& List::getNullObject()
{
	static NullList nullObject;
	return nullObject;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// NullImage
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void NullList::reloadData()
{
	WLOG("NullObject ignoring call: %s in: %s:%d", __func__, __FILE__, __LINE__);
}

}
}
