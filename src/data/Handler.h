//
// Created by Dawid Drozd aka Gelldur on 02/01/17.
//
#pragma once

#include <functional>
#include <queue>
#include <chrono>
#include <mutex>

//TODO a lot of copy in Refresher.cpp
class Handler
{
public:
	Handler();
	~Handler();

	struct Callback
	{
		std::chrono::milliseconds time;
		std::function<void()> call;
	};

	void schedule(const std::function<void()>& task);
	void schedule(std::chrono::milliseconds delay, const std::function<void()>& task);
	void unscheduleAll();

private:
	std::mutex _mutex;
	bool _isScheduled = false;

	struct compare
	{
		bool operator()(const Handler::Callback& lhs, const Handler::Callback& rhs) const
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


