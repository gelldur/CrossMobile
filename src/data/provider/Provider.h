//
// Created by Dawid Drozd aka Gelldur on 03.02.16.
//

#pragma once

#include <data/receiver/Receiver.h>

class Provider
{
public:
	virtual ~Provider() = default;
	virtual void onRequestData() = 0;

	virtual void onCancel();

	void setReceiver(Receiver* receiver);

protected:
	Receiver* getReceiver()
	{
		return _receiver;
	}

private:
	Receiver* _receiver = nullptr;
};


