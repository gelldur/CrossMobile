//
// Created by Dawid Drozd aka Gelldur on 03.02.16.
//

#pragma once

#include <atomic>
#include <memory>

#include <data/receiver/Receiver.h>
#include "api/Async.h"

namespace Poco
{
class Runnable;
}

class Provider : public Api::Async
{
public:
	friend class BackroundHelper;

	Provider();
	virtual ~Provider();
	/**
	 * Pass here provider shared_ptr that owns this provider
	 */
	virtual void onRequestData(std::shared_ptr<Provider>& thisProvider);

	void cancel();

	enum class State
	{
		IDLE, BEFORE_RUN, RUNNING, CANCELED, ERROR, DONE
	};

	bool isCanceled();

	void setReceiver(Receiver* receiver);

	void onEvent(const void* sender, int& dummy);

	bool isReady();

protected:
	Receiver* getReceiver()
	{
		return _receiver;
	}

	virtual void onCancel();

private:
	std::atomic<State> _state;
	Receiver* _receiver = nullptr;
	Poco::Runnable* _runnable = nullptr;

	void registerCheck();
	void unregisterCheck();

	void setState(State state);
};
