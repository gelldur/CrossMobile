//
// Created by Dawid Drozd aka Gelldur on 8/15/16.
//

#pragma once

#include <memory>

#include <platform/Context.h>
#include <component/NodectBuilder.h>

namespace ContextHelper
{
id getNative(Context* context);

void* wrap(id nativeObject);

}

namespace NodectBuilder
{

class createIos : public create
{
public:
	createIos(const std::string& tag, id nativePointer)
			: create(std::make_shared<Context>(ContextHelper::wrap(nativePointer)), tag)
	{
	}
};

}
