//
// Created by Dawid Drozd aka Gelldur on 14.03.16.
//

#pragma once

#include <string>
#include <Poco/Net/HTTPClientSession.h>

class Server
{
public:
	Server();

	static void setDefaultDebugable(bool isDebugableDefault);
	static void setDefaultHost(const std::string& host);

	const std::string& getHost() const
	{
		return _host;
	}

	Poco::Net::HTTPClientSession* getSession() const
	{
		return _session;
	}


	bool isDebugable() const
	{
		return _isDebugable;
	}

private:
	static bool defaultDebugable;
	static std::string defaultHost;

	bool _isDebugable = defaultDebugable;

	int _timeoutRead = 15;
	int _timeoutConnect = 15;

	std::string _host = defaultHost;
	Poco::Net::HTTPClientSession* _session;
};


