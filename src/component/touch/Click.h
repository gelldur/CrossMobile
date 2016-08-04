//
// Created by Dawid Drozd aka Gelldur on 8/4/16.
//

#pragma once

#include <component/Component.h>
#include <functional>

/**
 * Implementation is environment specific
 */
class Click : public Component
{
	using inherited = Component;
public:
	virtual void onClick();

	void setCallback(const std::function<void(Nodect*)>& callback);

	static Click& getNullObject();

	COMPONENT_TO_STRING(Click)

protected:
	virtual void onEnter() override;
	virtual void onExit() override;

private:
	std::function<void(Nodect*)> _callback;
};

class NullClick : public Click
{
public:
	virtual void onClick() override;
};
