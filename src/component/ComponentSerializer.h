//
// Created by Dawid Drozd aka Gelldur on 8/11/16.
//

#pragma once

#include <map>
#include "NodectBuilder.h"

template<typename T>
void ComponentSerializerAddFromName(NodectBuilder::create& creator)
{
	creator.addComponent<T>();
}

class ComponentSerializer
{
public:
	using map_type = std::map<std::string, void (*)(NodectBuilder::create&)>;

	static void init();

	static void addComponentByName(NodectBuilder::create& builder, const std::string& componentName);
	static void registerComponent(const std::string& componentName, void(* creator)(NodectBuilder::create&));

private:
	static map_type _componentCreators;
};


