//
// Created by Dawid Drozd aka Gelldur on 14.03.16.
//

#pragma once

#include <memory>
#include <string>

#include <Poco/Net/HTTPClientSession.h>

class Server
{
public:
	Server(bool isDebugable);
	Server(const std::string& host = Server::defaultHost, bool isDebugable = Server::defaultDebugable);

	static void setDefaultDebugable(bool isDebugableDefault);
	static void setDefaultHost(const std::string& host);

	const std::string& getHost() const;

	Poco::Net::HTTPClientSession* getSession() const;

	const bool isDebugable() const
	{
		return _isDebugable;
	}

private:
	static bool defaultDebugable;
	static std::string defaultHost;

	std::unique_ptr<Poco::Net::HTTPClientSession> _session;

	const bool _isDebugable;
	const int _timeoutConnect = 12;
};


