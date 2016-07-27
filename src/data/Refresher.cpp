//
// Created by Dawid Drozd aka Gelldur on 7/26/16.
//

#include "Refresher.h"

#include <chrono>

#include <Poco/Delegate.h>
#include <Poco/Runnable.h>

#include <Director.h>
#include <Application.h>

Refresher::Refresher()
{
}

Refresher::~Refresher()
{
	unscheduleAll();
}

void Refresher::schedule(unsigned delay, const Refresher::Callback::call_t& task, unsigned repeatCount)
{
	if (repeatCount < 1)
	{
		return;
	}
	auto now = std::chrono::system_clock::now();

	std::chrono::seconds delayDuration(delay);
	delayDuration += std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch());

	Callback callback;
	callback.time = (long long) delayDuration.count();
	callback.call = task;
	callback.delay = delay;
	callback.repeat = repeatCount;
	_callbacks.push(std::move(callback));

	if (_isScheduled == false)
	{
		Director::getInstance().getApp()->getUILoop().uiTick += Poco::delegate(this, &Refresher::onTick);
		_isScheduled = true;
	}
}

void Refresher::unscheduleAll()
{
	if (_isScheduled == false)
	{
		return;
	}

	_callbacks = decltype(_callbacks)();
	Director::getInstance().getApp()->getUILoop().uiTick -= Poco::delegate(this, &Refresher::onTick);
	_isScheduled = false;
}

void Refresher::onTick(const void* sender, int& dummy)
{
	//TODO do it better ;)
	auto now = std::chrono::system_clock::now();

	long long nowInSecs = std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch()).count();

	std::vector<Callback> repeatCallbacks;
	while (_callbacks.empty() == false)
	{
		auto& top = _callbacks.top();
		if (top.time <= nowInSecs)
		{
			top.call();
			if (top.repeat > 1)
			{
				repeatCallbacks.push_back(top);
				repeatCallbacks.back().time = nowInSecs += repeatCallbacks.back().delay;
				--repeatCallbacks.back().repeat;
			}
			_callbacks.pop();
		}
		else
		{
			break;
		}
	}
	if (repeatCallbacks.empty() == false)
	{
		for (auto& element : repeatCallbacks)
		{
			_callbacks.push(element);
		}
	}
	if (_callbacks.empty())
	{
		unscheduleAll();
	}
}
