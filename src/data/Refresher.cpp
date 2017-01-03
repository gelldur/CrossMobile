//
// Created by Dawid Drozd aka Gelldur on 7/26/16.
//

#include "Refresher.h"

#include <Poco/Delegate.h>

#include <Director.h>
#include <Application.h>

Refresher::Refresher()
{
}

Refresher::~Refresher()
{
	unscheduleAll();
}

void Refresher::schedule(std::chrono::milliseconds delay, const std::function<void()>& task, unsigned repeatCount)
{
	using namespace std::chrono;
	if (repeatCount < 1)
	{
		return;
	}
	auto now = system_clock::now();

	milliseconds delayDuration(delay);
	delayDuration += duration_cast<milliseconds>(now.time_since_epoch());

	Callback callback;
	callback.time = delayDuration;
	callback.call = task;
	callback.delay = delay;
	callback.repeat = repeatCount;

	std::lock_guard<std::mutex> lock(_mutex);

	_callbacks.push(std::move(callback));

	if (_isScheduled == false)
	{
		Director::getInstance().getApp()->getUILoop().uiTick += Poco::delegate(this, &Refresher::onTick);
		_isScheduled = true;
	}
}

void Refresher::unscheduleAll()
{
	std::lock_guard<std::mutex> lock(_mutex);

	_callbacks = decltype(_callbacks){};
	if (_isScheduled)
	{
		Director::getInstance().getApp()->getUILoop().uiTick -= Poco::delegate(this, &Refresher::onTick);
	}
	_isScheduled = false;
}

void Refresher::onTick(const void* sender, int& dummy)
{
	auto now = std::chrono::system_clock::now();
	auto nowInMls = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch());

	std::vector<Callback> repeatCallbacks;
	while (isReadyToCall(nowInMls))
	{
		Callback top;
		{
			std::lock_guard<std::mutex> lock(_mutex);
			top = _callbacks.top();
			_callbacks.pop();
		}
		top.call();
		if (top.repeat > 1)
		{
			--top.repeat;
			top.time = nowInMls + top.delay;
			repeatCallbacks.push_back(top);
		}
	}
	if (repeatCallbacks.empty() == false)
	{
		std::lock_guard<std::mutex> lock(_mutex);
		for (auto& element : repeatCallbacks)
		{
			_callbacks.push(element);
		}
	}
	if (isEmpty())
	{
		unscheduleAll();//no more left
	}
}
