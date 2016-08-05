//
// Created by Dawid Drozd aka Gelldur on 6/30/16.
//

#pragma once

#include <string>
#include <vector>
#include <memory>

#include <component/Component.h>
#include <component/adapter/ListDataSource.h>

class Match;

class ListDataSourceComponent : public Component
{
	using inherited = Component;
public:
	virtual void setData(std::unique_ptr<ListDataSource>&& list);

	COMPONENT_TO_STRING(MatchesAdapterWrapper);

	static ListDataSourceComponent& getNullObject();
};

class NullListDataSourceComponent : public ListDataSourceComponent
{
public:
	virtual void setData(std::unique_ptr<ListDataSource>&& list) override;
};
