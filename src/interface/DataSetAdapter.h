//
// Created by Dawid Drozd aka Gelldur on 08.03.16.
//

#pragma once

template<class Type>
class DataSetAdapter
{
public:
	virtual ~DataSetAdapter() = default;

	virtual int getCount() const = 0;
	virtual Type getItem(const int position) = 0;
};


