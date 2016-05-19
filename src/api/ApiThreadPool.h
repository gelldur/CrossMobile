//
// Created by Dawid Drozd aka Gelldur on 5/16/16.
//

#pragma once

#include <Poco/ThreadPool.h>

class ApiThreadPool : public Poco::ThreadPool
{
public:
	ApiThreadPool()
			: ThreadPool("api")
	{
	}
};


