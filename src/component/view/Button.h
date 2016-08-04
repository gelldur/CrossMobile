//
// Created by Dawid Drozd aka Gelldur on 8/4/16.
//

#pragma once

#include <functional>

#include <component/Component.h>

/**
 * Implementation is environment specific
 */
class Button : public Component
{
	using inherited = Component;
public:
	virtual void image(const std::string& name);
	void setOnClick(const std::function<void(Nodect*)>& callback);

	COMPONENT_TO_STRING(Button)

	static Button& getNullObject();
};

class NullButton : public Button
{
public:
	virtual void image(const std::string& name) override;
};


