//
// Created by Dawid Drozd aka Gelldur on 8/11/16.
//

#include "ComponentSerializer.h"

#include <component/view/Text.h>
#include <component/view/Image.h>

ComponentSerializer::map_type ComponentSerializer::_componentCreators;

void ComponentSerializer::registerComponent(const std::string& componentName, void (* creator)(NodectBuilder::create&))
{
	_componentCreators[componentName] = creator;
}

void ComponentSerializer::addComponentByName(NodectBuilder::create& builder, const std::string& componentName)
{
	auto found = _componentCreators.find(componentName);
	if (found == _componentCreators.end())
	{
		WLOG("Missing component creator: [%s]", componentName.c_str());
		return;
	}
	found->second(builder);
}

void ComponentSerializer::init()
{
	registerComponent(Text::myName(), &ComponentSerializerAddFromName<Text>);
	registerComponent(Image::myName(), &ComponentSerializerAddFromName<Image>);
}
