//
// Created by Dawid Drozd aka Gelldur on 6/30/16.
//
#import "AdapterListProtocol.h"

#include <component/adapter/ListDataSourceComponent.h>
#include <platform/Context.h>
#include <platform/ContextHelper.h>

void ListDataSourceComponent::setData(std::unique_ptr<ListDataSource>&& list) //
{
	auto context = getContext();
	id<AdapterListProtocol> adapter = ContextHelper::getNative(context);

	[adapter setData:std::move(list)];
}
