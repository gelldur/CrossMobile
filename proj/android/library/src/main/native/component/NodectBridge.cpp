//
// Created by Dawid Drozd aka Gelldur on 8/11/16.
//

#include "NodectBridge.h"

#include <Android.h>
#include <platform/Context.h>

#include <component/NodectHelper.h>

void deserializeComponents(NodectBuilder::create& builder, JniObject& nodectHelper)
{
	int componentCount = nodectHelper.call("getComponentCount", 0);
	for (int i = 0; i < componentCount; ++i)
	{
		std::string componentName = nodectHelper.call("getComponent", std::string(), i);
		builder.addComponentByName(componentName);
	}
}

Nodect deserializeNodect(JniObject& nodectHelper)
{
	std::string tag = nodectHelper.call("getTag", std::string());

	JniObject context = nodectHelper.call("getContext", JniObject("java.lang.Object"));
	if (!context)
	{
		ELOG("Missing context in %s", tag.c_str());
		return Nodect("missing-context", nullptr);
	}

	NodectBuilder::create builder(std::make_shared<Context>(context), tag);
	deserializeComponents(builder, nodectHelper);

	int nodesCount = nodectHelper.call("getNestedCount", 0);
	for (int i = 0; i < nodesCount; ++i)
	{
		JniObject nestedNodectHelperRaw = nodectHelper.call("getNested"
															, JniObject("com.cross.mobile.component.NodectBuilder"), i);
		if (nestedNodectHelperRaw)
		{
			builder.nest(deserializeNodect(nestedNodectHelperRaw));
		}
		else
		{
			ELOG("Errors during getNested: %s-%d", tag.c_str(), i);
		}
	}
	return builder.build();
}
