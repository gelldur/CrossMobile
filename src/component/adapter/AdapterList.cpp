//
// Created by Dawid Drozd aka Gelldur on 8/12/16.
//

#include "AdapterList.h"

int AdapterList::getSize()
{
	return 0;
}

const std::string& AdapterList::getIdentifier(int index)
{
	static std::string overrideME;
	return overrideME;
}

void AdapterList::setElement(int position, const Nodect& row)
{
}

std::unique_ptr<ListDataSource> AdapterList::getData()
{
	return std::unique_ptr<ListDataSource>(new ListDataSource());
}
