//
// Created by Dawid Drozd aka Gelldur on 7/26/16.
//

#pragma once

#include <functional>
#include <queue>

class Refresher
{
public:
	Refresher();
	~Refresher();

	struct Callback
	{
		using call_t = std::function<void()>;

		unsigned repeat;
		unsigned delay;

		long long time;
		call_t call;
	};

	void schedule(unsigned delay, const Callback::call_t& task, unsigned repeatCount = 1);
	void unscheduleAll();

	void onTick(const void* sender, int& dummy);

private:

	bool _isScheduled = false;

	struct compare
	{
		bool operator()(const Refresher::Callback& lhs, const Refresher::Callback& rhs) const
		{
			return lhs.time > rhs.time;
		}
	};

	std::priority_queue<Callback, std::vector<Callback>, compare> _callbacks;
};


