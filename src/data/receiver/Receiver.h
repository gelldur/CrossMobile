//
// Created by Dawid Drozd aka Gelldur on 03.02.16.
//

#pragma once

class Provider;

class Receiver
{
public:
	virtual ~Receiver() = default;
	virtual void onReceive(Provider* provider) = 0;
	virtual void onError(Provider* provider) = 0;
};


