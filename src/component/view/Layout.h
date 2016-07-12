//
// Created by Dawid Drozd aka Gelldur on 7/11/16.
//

#pragma once

#include <component/Component.h>

/**
 * Implementation is environment specific
 */
class Layout : public Component
{
	using inherited = Component;
public:

	virtual void layout();

	COMPONENT_TO_STRING(Layout)

	static Layout& getNullObject();
};

class NullLayout : public Layout
{
public:
	virtual void layout() override;
};

