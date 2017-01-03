//
// Created by Dawid Drozd aka Gelldur on 7/26/16.
//

#pragma once

#include <functional>
#include <queue>
#include <chrono>
#include <mutex>

class Refresher
{
public:
	Refresher();
	~Refresher();

	struct Callback
	{
		unsigned repeat;

		std::chrono::milliseconds delay;
		std::chrono::milliseconds time;
		std::function<void()> call;
	};

	void schedule(std::chrono::milliseconds delay, const std::function<void()>& task, unsigned repeatCount = 1);
	void unscheduleAll();

private:
	std::mutex _mutex;
	bool _isScheduled = false;

	struct compare
	{
		bool operator()(const Refresher::Callback& lhs, const Refresher::Callback& rhs) const
		{
			return lhs.time > rhs.time;
		}
	};

	std::priority_queue<Callback, std::vector<Callback>, compare> _callbacks;

	void onTick(const void* sender, int& dummy);

	bool isEmpty()
	{
		std::lock_guard<std::mutex> lock(_mutex);
		return _callbacks.empty();
	}

	bool isReadyToCall(const std::chrono::milliseconds& now)
	{
		std::lock_guard<std::mutex> lock(_mutex);
		return _callbacks.empty() == false && _callbacks.top().time <= now;
	}
};


