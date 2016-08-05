//
// Created by Dawid Drozd aka Gelldur on 6/30/16.
//

#include "ListDataSourceComponent.h"

#include <model/match/Match.h>
#include <log.h>

#ifndef PLATFORM_IOS

void ListDataSourceComponent::setData(std::unique_ptr<ListDataSource>&& list)
{
	WLOG("Function %s not implemented: %s:%d", __func__, __FILE__, __LINE__);
}

#endif

ListDataSourceComponent& ListDataSourceComponent::getNullObject()
{
	static NullListDataSourceComponent nullObject;
	return nullObject;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// NullListDataSourceComponent
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void NullListDataSourceComponent::setData(std::unique_ptr<ListDataSource>&& list)
{
	WLOG("NullObject ignoring call: %s in: %s:%d", __func__, __FILE__, __LINE__);
}
