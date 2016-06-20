//
// Created by Dawid Drozd aka Gelldur on on 25.04.16.
//

#pragma once

#include <bridge/NativeAdapter.h>

class IosAdapter : public NativeAdapter
{
public:
	virtual void onStartScreen(Screen* screen) override;
};


