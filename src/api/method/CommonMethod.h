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
	std::istream& requestGet(const Server& server, const std::string& pathAndQuery);
	std::istream& requestPostForm(const Server& server, const std::string& pathAndQuery
			, const std::map<std::string, std::string>& params);
	std::istream& requestPostJson(const Server& server, const std::string& pathAndQuery, const std::string& json);

	void toJson(std::istream& stream, Json::Value& rootOut);
	void toJson(const std::string& document, Json::Value& rootOut);

	static void addMockedResponse(const std::string& response);

private:
	//TODO do it better way
	static std::deque<std::string> _mockedResponses;
	std::stringstream _mockedResponse;
};

