//
// Created by Dawid Drozd aka Gelldur on 03.02.16.
//

#include "DataProviderComponent.h"

DataProviderComponent::DataProviderComponent(Provider* provider, Receiver* receiver)
		: _provider(provider)
		, _receiver(receiver)
{
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
	_provider->onRequestData();
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
}

void DataProviderComponent::onError(Provider* provider)
{
	if (_receiver != nullptr)
	{
		_receiver->onError(provider);
	}
}
