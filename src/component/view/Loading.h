//
// Created by Dawid Drozd aka Gelldur on 7/11/16.
//

#pragma once

#include <component/Component.h>

/**
 * Implementation is environment specific
 */
class Loading : public Component
{
	using inherited = Component;
public:

	virtual void loadingStart();
	virtual void loadingStop();

	COMPONENT_TO_STRING(Loading)

	static Loading& getNullObject();
};

class NullLoading : public Loading
{
public:
	virtual void loadingStart() override;
	virtual void loadingStop() override;
};

