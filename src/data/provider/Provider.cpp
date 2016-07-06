//
// Created by Dawid Drozd aka Gelldur on 03.02.16.
//

#include "Provider.h"

#include <atomic>

#include <log.h>
#include <Poco/Delegate.h>
#include <Poco/Runnable.h>
#include <Director.h>
#include <exception/Fail.h>
#include "Application.h"

//TODO make thread safe
class BackroundHelper : public Poco::Runnable
{
public:
	std::atomic<bool> isReady;

	BackroundHelper(std::shared_ptr<Provider>& provider)
			: isReady(false)
			, _provider(provider)
	{
		_provider->setState(Provider::State::BEFORE_RUN);
	}

	virtual void run() override
	{
		try
		{
			runTask();
		}
		catch (std::exception& exception)
		{
			DLOG("Exception in background task!\n%s", exception.what());
			throw;
		}
		catch (...)
		{
			DLOG("Exception in background task!");
			throw;
		}
		isReady = true;
	}

	void runTask()
	{
		if (_provider->isCanceled())
		{
			return;
		}
		_provider->setState(Provider::State::RUNNING);
		try
		{
			_provider->onDoInBackground();
			_provider->setState(Provider::State::DONE);
		}
		catch (...)
		{
			_provider->setState(Provider::State::ERROR);
			throw;
		}
	}

private:
	std::shared_ptr<Provider> _provider;
};

Provider::~Provider()
{
	if (_runnable != nullptr)
	{
		Fail(__FILE__, __func__, __LINE__).add("Provider is running and you try to release it durring this operation")
				.report();
	}
}

void Provider::setReceiver(Receiver* receiver)
{
	_receiver = receiver;
}

void Provider::onRequestData(std::shared_ptr<Provider>& thisProvider)
{
	if (_runnable != nullptr)
	{
		ELOG("Already queued");
		return;
	}

	assert(thisProvider.get() == this);

	_runnable = new BackroundHelper(thisProvider);
	Director::getInstance().getApp()->getApiThreadPool().start(*_runnable);
	registerCheck();
}

void Provider::cancel()
{
	if (_state != State::CANCELED)
	{
		setState(State::CANCELED);
		onCancel();
	}
}

void Provider::onCancel()
{
	//TODO implement
}

void Provider::onEvent(const void* sender, int& dummy)
{
	if (_runnable == nullptr)
	{
		Fail(__FILE__, __func__, __LINE__).report();
	}
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
		if (_state == State::ERROR)
		{
			//TODO add catches?
			getReceiver()->onError(this);
		}
		else if (_state == State::DONE)
		{
			getReceiver()->onReceive(this);
		}
		else
		{
			Fail(__FILE__, __func__, __LINE__).add("Wrong state:").add(static_cast<int>(_state)).report();
		}
	}
	else
	{
		DLOG("%s:%s:%d", __FILE__, __func__, __LINE__);
		WLOG("No one to notify!");
	}

	unregisterCheck();
	setState(State::IDLE);

	auto runnable = _runnable;
	_runnable = nullptr;
	delete runnable;
}

void Provider::registerCheck()
{
	Director::getInstance().getApp()->getUILoop().uiTick += Poco::delegate(this, &Provider::onEvent);
}

void Provider::unregisterCheck()
{
	Director::getInstance().getApp()->getUILoop().uiTick -= Poco::delegate(this, &Provider::onEvent);
}

void Provider::setState(State state)
{
	std::lock_guard<std::mutex> lock(_mutex);
	if (_state == State::CANCELED && state != State::IDLE)
	{
		return;
	}
	_state = state;
}

bool Provider::isCanceled()
{
	std::lock_guard<std::mutex> lock(_mutex);
	return _state == State::CANCELED;
}


