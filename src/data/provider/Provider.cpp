//
// Created by Dawid Drozd aka Gelldur on 03.02.16.
//

#include "Provider.h"

#include <atomic>

#include <log.h>
#include <Poco/Delegate.h>
#include <Poco/Runnable.h>
#include "Application.h"

//TODO make thread safe
class BackroundHelper : public Poco::Runnable
{
public:
	BackroundHelper(Provider* provider)
			: isReady(false)
			, _provider(provider)
	{
	}

	virtual void run() override
	{
		if (_provider != nullptr)
		{
			_provider->onDoInBackground();
		}
		isReady = true;
		delete this;//self destruct!
	}

	std::atomic<bool> isReady;
	Provider* _provider;
};

Provider::~Provider()
{
	if (_runnable != nullptr)
	{
		auto request = dynamic_cast<BackroundHelper*>(_runnable);
		request->_provider = nullptr;
	}
}

void Provider::setReceiver(Receiver* receiver)
{
	_receiver = receiver;
}

void Provider::onRequestData()
{
	if (_runnable != nullptr)
	{
		ELOG("Already queued");
		return;
	}
	_runnable = new BackroundHelper(this);
	Application::getInstance()->getApiThreadPool().start(*_runnable);
	registerCheck();
}

void Provider::onCancel()
{
	//TODO implement
}

void Provider::onEvent(const void* sender, int& dummy)
{
	auto request = dynamic_cast<BackroundHelper*>(_runnable);
	if (request->isReady == false)
	{
		DLOG("WAITING!");
		return;
	}
	DLOG("Done request");

	onPostExecute();

	if (getReceiver() != nullptr)
	{
		getReceiver()->onReceive(this);
	}
	else
	{
		DLOG("%s:%s:%d", __FILE__, __func__, __LINE__);
		WLOG("No one to notify!");
	}

	delete _runnable;
	_runnable = nullptr;

	unregisterCheck();
}

void Provider::registerCheck()
{
	Application::getInstance()->getUILoop().uiTick += Poco::delegate(this, &Provider::onEvent);
}

void Provider::unregisterCheck()
{
	Application::getInstance()->getUILoop().uiTick -= Poco::delegate(this, &Provider::onEvent);
}