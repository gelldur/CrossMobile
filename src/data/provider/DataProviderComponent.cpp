//
// Created by Dawid Drozd aka Gelldur on 03.02.16.
//

#include "DataProviderComponent.h"

#include <log.h>

DataProviderComponent::DataProviderComponent(std::shared_ptr<Provider> provider, Receiver* receiver)
		: _provider(provider)
		, _receiver(receiver)
{
}

DataProviderComponent::~DataProviderComponent()
{
	_receiver = nullptr;
}

void DataProviderComponent::onResume()
{
	_provider->setReceiver(this);
}

void DataProviderComponent::onPause()
{
	_provider->setReceiver(nullptr);
}

void DataProviderComponent::onRequestData()
{
	_provider->onRequestData(_provider);
}

void DataProviderComponent::onStartLoading()
{
}

void DataProviderComponent::onStopLoading()
{
}

void DataProviderComponent::onReceive(Provider* provider)
{
	if (_receiver != nullptr)
	{
		_receiver->onReceive(provider);
	}
	else
	{
		WLOG("[DataProviderComponent] No receiver setted!");
	}
}

void DataProviderComponent::onError(Provider* provider)
{
	if (_receiver != nullptr)
	{
		_receiver->onError(provider);
	}
	else
	{
		WLOG("[DataProviderComponent] No receiver setted!");
	}
}

