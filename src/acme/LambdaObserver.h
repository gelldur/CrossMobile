//
// Created by Dawid Drozd aka Gelldur on 5/17/16.
//

#pragma once

#include <memory>
#include <functional>
#include <Poco/NotificationCenter.h>
#include <Poco/NObserver.h>

template<class N>
struct LObserver
{
	typedef std::function<void(const Poco::AutoPtr<N>&)> Lambda;

	LObserver(const Lambda& callback)
			: _callback(callback)
	{
	}

	void handleNotification(const Poco::AutoPtr<N>& notification)
	{
		_callback(notification);
	}

	Lambda _callback;
};

template<class N>
class LambdaObserver : public Poco::NObserver<LObserver<N>, N>
{
public:
	typedef std::unique_ptr<LObserver<N>> Pointer;

	LambdaObserver(LObserver<N>* target)
			: Poco::NObserver<LObserver<N>, N>(*target, &LObserver<N>::handleNotification)
	{
	}

	static std::unique_ptr<LObserver<N>> addObserver(Poco::NotificationCenter& notificationCenter
													 , const typename LObserver<N>::Lambda& callback)
	{
		auto observer = std::unique_ptr<LObserver<N>>(new LObserver<N>(callback));
		notificationCenter.addObserver(LambdaObserver<N>(observer.get()));
		return observer;
	}

	static void removeObserver(Poco::NotificationCenter& notificationCenter, std::unique_ptr<LObserver<N>>& observer)
	{
		notificationCenter.removeObserver(LambdaObserver<N>(observer.get()));
	}
};
