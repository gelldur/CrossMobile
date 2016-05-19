//
// Created by Dawid Drozd aka Gelldur on 03.02.16.
//

#pragma once

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

	virtual ~Provider();
	virtual void onRequestData();

	virtual void onCancel();

	void setReceiver(Receiver* receiver);

	void onEvent(const void* sender, int& dummy);

protected:
	Receiver* getReceiver()
	{
		return _receiver;
	}

private:
	Receiver* _receiver = nullptr;
	Poco::Runnable* _runnable = nullptr;

	void registerCheck();
	void unregisterCheck();
};
