//
// Created by Dawid Drozd aka Gelldur on 03.02.16.
//

#include "DataProviderComponent.h"

#include <cassert>
#include <log.h>

DataProviderComponent::DataProviderComponent(std::shared_ptr<Provider> provider, Receiver* receiver)
		: _provider(provider)
		, _receiver(receiver)
{
	assert(provider);
}

DataProviderComponent::~DataProviderComponent()
{
	_provider->cancel();
	_receiver = nullptr;
}

void DataProviderComponent::onResume()
{
	_provider->setReceiver(this);
}

void DataProviderComponent::onPause()
{
	_provider->setReceiver(nullptr);
	_provider->cancel();
}

void DataProviderComponent::onRequestData()
{
	if (_provider->isReady())
	{
		_provider->onRequestData(_provider);
	}
	else
	{
		WLOG("Provider is busy");
	}
}

void DataProviderComponent::onStartLoading()
{
	if (_receiver != nullptr && _isLoading == false)
	{
		_receiver->onStartLoading();
		_isLoading = true;
	}
}

void DataProviderComponent::onStopLoading()
{
	if (_receiver != nullptr && _isLoading == true)
	{
		_receiver->onStopLoading();
		_isLoading = false;
	}
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

