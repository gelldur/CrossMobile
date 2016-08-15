//
// Created by Dawid Drozd aka Gelldur on 6/15/16.
//

#include <component/view/List.h>

#include <platform/Context.h>
#import <component/list/ListProtocol.h>
#include <platform/ContextHelper.h>

namespace CrossMobile
{
namespace Component
{

void List::reloadData()
{
	auto context = getContext();

	id<ListProtocol> list = ContextHelper::getNative(context);

	// @formatter:off
	[list reloadData];
	// @formatter:on
}

}
}
