//
// Created by Dawid Drozd aka Gelldur on 02/01/17.
//
#include "Handler.h"
//////////////////////////////////

#include <Poco/Delegate.h>

#include <Director.h>
#include <Application.h>

Handler::Handler()
{
}

Handler::~Handler()
{
	unscheduleAll();
}

void Handler::schedule(const std::function<void()>& task)
{
	schedule(std::chrono::milliseconds{0}, task);
}

void Handler::schedule(std::chrono::milliseconds delay, const std::function<void()>& task)
{
	using namespace std::chrono;
	auto now = system_clock::now();

	milliseconds delayDuration(delay);
	delayDuration += duration_cast<milliseconds>(now.time_since_epoch());

	Callback callback;
	callback.time = delayDuration;
	callback.call = task;

	std::lock_guard<std::mutex> lock(_mutex);

	_callbacks.push(std::move(callback));

	if (_isScheduled == false)
	{
		Director::getInstance().getApp()->getUILoop().uiTick += Poco::delegate(this, &Handler::onTick);
		_isScheduled = true;
	}
}

void Handler::unscheduleAll()
{
	std::lock_guard<std::mutex> lock(_mutex);

	_callbacks = decltype(_callbacks){};
	if (_isScheduled)
	{
		Director::getInstance().getApp()->getUILoop().uiTick -= Poco::delegate(this, &Handler::onTick);
	}
	_isScheduled = false;
}

void Handler::onTick(const void* sender, int& dummy)
{
	auto now = std::chrono::system_clock::now();
	auto nowInMls = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch());

	while (isReadyToCall(nowInMls))
	{
		Callback top;
		{
			std::lock_guard<std::mutex> lock(_mutex);
			top = _callbacks.top();
			_callbacks.pop();
		}
		top.call();
	}
	if (isEmpty())
	{
		unscheduleAll();//no more left
	}
}
