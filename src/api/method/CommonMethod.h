//
// Created by Dawid Drozd aka Gelldur on 14.03.16.
//

#pragma once

#include <memory>
#include <sstream>

#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>

#include <json/json.h>

#include <api/Server.h>

class CommonMethod
{
public:
	CommonMethod(const std::shared_ptr<Server>& server);

	class Connection
	{
	public:
		Poco::Net::HTTPRequest request;
		Poco::Net::HTTPResponse response;

		Connection(const std::shared_ptr<Server>& server);

		std::ostream& send();
		std::istream& receive();

	private:
		const std::shared_ptr<Server> _server;
		std::istream* _responseBody = nullptr;
	};

	std::unique_ptr<Connection> requestGet(const std::string& pathAndQuery);
	std::unique_ptr<Connection> requestPostForm(const std::string& pathAndQuery
			, const std::map<std::string, std::string>& params);
	std::unique_ptr<Connection> requestPostJson(const std::string& pathAndQuery, const std::string& json);

	void toJson(std::istream& stream, Json::Value& rootOut);
	void toJson(const std::string& document, Json::Value& rootOut);

private:
	const std::shared_ptr<Server> _server;
};

