//
// Created by Dawid Drozd aka Gelldur on 6/30/16.
//
#import "AdapterListProtocol.h"

#include <component/adapter/ListDataSourceComponent.h>
#include <platform/Context.h>

void ListDataSourceComponent::setData(std::unique_ptr<ListDataSource>&& list) //
{
	auto context = getContext();
	id<AdapterListProtocol> adapter = context->getNative();

	[adapter setData:std::move(list)];
}
