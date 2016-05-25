//
// Created by Dawid Drozd aka Gelldur on 14.03.16.
//

#include "Server.h"

bool Server::defaultDebugable = false;
std::string Server::defaultHost;

Server::Server()
		: Server(defaultDebugable)
{
}

Server::Server(bool isDebugable)
		: _isDebugable(isDebugable)
		, _session(new Poco::Net::HTTPClientSession(_host))
{
}

void Server::setDefaultDebugable(bool isDebugableDefault)
{
	defaultDebugable = isDebugableDefault;
}

void Server::setDefaultHost(const std::string& host)
{
	defaultHost = host;
}
