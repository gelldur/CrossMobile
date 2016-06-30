//
// Created by Dawid Drozd aka Gelldur on 6/30/16.
//

#pragma once

#include <component/Component.h>

namespace Dexode
{
namespace Component
{

/**
 * Implementation is environment specific
 */
class List : public ::Component
{
	using inherited = Component;
public:
	virtual void reloadData();

	COMPONENT_TO_STRING(List)

	static List& getNullObject();
};

class NullList : public List
{
public:
	virtual void reloadData() override;
};

}
}
