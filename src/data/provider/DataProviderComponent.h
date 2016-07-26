//
// Created by Dawid Drozd aka Gelldur on 03.02.16.
//

#pragma once

#include <memory>
#include "Provider.h"

class DataProviderComponent : public Receiver
{
public:
	DataProviderComponent(std::shared_ptr<Provider> provider, Receiver* receiver = nullptr);
	~DataProviderComponent();

	void onResume();
	void onPause();

	void onRequestData();

	virtual void onReceive(Provider* provider) override;
	virtual void onError(Provider* provider) override;

	virtual void onStartLoading() override;
	virtual void onStopLoading() override;

private:
	bool _isLoading = false;
	std::shared_ptr<Provider> _provider;
	Receiver* _receiver = nullptr;
};


