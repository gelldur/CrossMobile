//
// Created by Dawid Drozd aka Gelldur on 03.02.16.
//

#include "Provider.h"

#include <Poco/Delegate.h>
#include "Application.h"

void Provider::setReceiver(Receiver* receiver)
{
	_receiver = receiver;
}

void Provider::onCancel()
{
	//TODO implement
}

void Provider::onEvent(const void* sender, int& dummy)
{
	if (checkDone())
	{
		unregisterCheck();
	}
}

void Provider::registerCheck()
{
	Application::getInstance()->getUILoop().uiTick += Poco::delegate(this, &Provider::onEvent);
}

void Provider::unregisterCheck()
{
	Application::getInstance()->getUILoop().uiTick -= Poco::delegate(this, &Provider::onEvent);
}

