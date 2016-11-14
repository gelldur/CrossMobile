//
// Created by Dawid Drozd aka Gelldur on 03.02.16.
//

#include "Provider.h"

#include <log.h>
#include <Poco/Delegate.h>
#include <Poco/Runnable.h>
#include <Director.h>
#include <exception/Fail.h>
#include <acme/guard/ChangeOnEnd.h>
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
		assert(_provider);
		_provider->setState(Provider::State::BEFORE_RUN);
	}

	virtual void run() override
	{
		ChangeOnEnd<std::atomic<bool>, bool> guard(isReady, true);
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

Provider::Provider()
		: _state(State::IDLE)
{
}

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
	_receiver->onStartLoading();
	Director::getInstance().getApp()->getApiThreadPool().start(*_runnable);
	registerCheck();
}

void Provider::cancel()
{
	if (isReady())
	{
		//Skip if doing nothing
		return;
	}
	if (_state != State::CANCELED)
	{
		setState(State::CANCELED);
		onCancel();
	}
}

void Provider::onCancel()
{
	//TODO implement
	DLOG("OnCancel");
	if (_receiver != nullptr)
	{
		_receiver->onStopLoading();
	}
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

	if (_receiver != nullptr)
	{
		if (_state == State::ERROR)
		{
			_receiver->onStopLoading();
			//TODO add catches?
			getReceiver()->onError(this);
		}
		else if (_state == State::DONE)
		{
			_receiver->onStopLoading();
			getReceiver()->onReceive(this);
		}
		else if (_state == State::CANCELED)
		{
			DLOG("Task canceled");
		}
		else
		{
			Fail(__FILE__, __func__, __LINE__).add("Wrong state:").add(static_cast<int>(_state.load())).report();
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
	if (_state == State::CANCELED && state != State::IDLE)
	{
		return;
	}
	_state = state;
}

bool Provider::isCanceled()
{
	return _state == State::CANCELED;
}

bool Provider::isReady()
{
	return _state == State::IDLE;
}
