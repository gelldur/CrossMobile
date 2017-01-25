//
// Created by Dawid Drozd aka Gelldur on 14.03.16.
//

#include "Server.h"

bool Server::defaultDebugable = false;
std::string Server::defaultHost;

Server::Server(bool isDebugable)
		: Server(defaultHost, isDebugable)
{
}

Server::Server(const std::string& host, bool isDebugable)
		: _session(new Poco::Net::HTTPClientSession(host))
		, _isDebugable(isDebugable)
{
	_session->setTimeout(Poco::Timespan(_timeoutConnect, 0));
}

void Server::setDefaultDebugable(bool isDebugableDefault)
{
	defaultDebugable = isDebugableDefault;
}

void Server::setDefaultHost(const std::string& host)
{
	defaultHost = host;
}

const std::string& Server::getHost() const
{
	return _session->getHost();
}

Poco::Net::HTTPClientSession* Server::getSession() const
{
	return _session.get();
}
