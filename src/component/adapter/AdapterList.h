//
// Created by Dawid Drozd aka Gelldur on 8/12/16.
//

#pragma once

#include <component/Nodect.h>
#include "ListDataSource.h"

class AdapterList
{
public:
	virtual ~AdapterList() = default;

	virtual int getSize();

	virtual const std::string& getIdentifier(int index);

	virtual void setElement(int position, const Nodect& row);

	virtual std::unique_ptr<ListDataSource> getData();
};


