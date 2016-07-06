//
// Created by Dawid Drozd aka Gelldur on 6/15/16.
//

#include <component/view/List.h>

#include <platform/Context.h>
#include <log.h>

#import <UIKit/UIKit.h>

namespace Dexode
{
namespace Component
{

void List::reloadData()
{
	auto context = getContext();

	id list = context->getNative();

	// @formatter:off
	[list reloadData];
	// @formatter:on
}

}
}
