//
// Created by Dawid Drozd aka Gelldur on 03.02.16.
//

#pragma once


#include "Provider.h"

class DataProviderComponent : public Receiver
{
public:
	DataProviderComponent(Provider* provider, Receiver* receiver);

	void onResume();
	void onPause();

	void onRequestData();

	virtual void onReceive(Provider* provider) override;
	virtual void onError(Provider* provider) override;

	void onStartLoading();
	void onStopLoading();

private:
	Provider* _provider = nullptr;
	Receiver* _receiver = nullptr;
};


