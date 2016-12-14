//
// Created by Dawid Drozd aka Gelldur on 14.03.16.
//

#pragma once

#include <memory>
#include <sstream>

#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>

#include <api/Server.h>
#include <Poco/Any.h>

#include <json/json.h>

class CommonMethod
{
public:
	class HTTPMethod
	{
	public:
		Poco::Net::HTTPRequest request;
		Poco::Net::HTTPResponse response;

		HTTPMethod(Poco::Net::HTTPClientSession* session);

		std::ostream& send();
		std::istream& receive();

	private:
		Poco::Net::HTTPClientSession* _session = nullptr;
		std::istream* _responseBody = nullptr;
	};

	std::unique_ptr<HTTPMethod> requestGet(const Server& server, const std::string& pathAndQuery);
	std::unique_ptr<HTTPMethod> requestPostForm(const Server& server, const std::string& pathAndQuery
			, const std::map<std::string, std::string>& params);
	std::unique_ptr<HTTPMethod>
	requestPostJson(const Server& server, const std::string& pathAndQuery, const std::string& json);

	void toJson(std::istream& stream, Json::Value& rootOut);
	void toJson(const std::string& document, Json::Value& rootOut);
};

