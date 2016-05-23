//
// Created by Dawid Drozd aka Gelldur on 14.03.16.
//

#pragma once

#include <memory>

#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>

#include <api/Server.h>
#include <api/adapter/Response.h>
#include <Poco/Any.h>

#include <json/json.h>

class CommonMethod
{
public:
	std::istream& requestGet(const Server& server, const std::string& pathAndQuery);

	void toJson(std::istream& stream, Json::Value& rootOut);
	void toJson(const std::string& document, Json::Value& rootOut);

	void process(std::unique_ptr<Response>& response);

	void throwIfNeedStatusException(std::unique_ptr<Response>& response);

private:

};

