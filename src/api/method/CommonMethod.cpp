//
// Created by Dawid Drozd aka Gelldur on 14.03.16.
//

#include "CommonMethod.h"

#include <Poco/Net/HTTPResponse.h>

#include <log.h>

std::istream& CommonMethod::requestGet(const Server& server, const std::string& pathAndQuery)
{
	using Poco::Net::HTTPRequest;
	using Poco::Net::HTTPResponse;
	using Poco::Net::HTTPMessage;

	HTTPRequest request(HTTPRequest::HTTP_GET, pathAndQuery, HTTPMessage::HTTP_1_1);
	HTTPResponse response;

	if (server.isDebugable())
	{
		DLOG("Request: %s%s", server.getHost().c_str(), request.getURI().c_str());
	}

	server.getSession()->sendRequest(request);
	return server.getSession()->receiveResponse(response);
}

void CommonMethod::process(std::unique_ptr<Response>& response)
{
	const auto code = response->getCode();
	if (response->isSuccessful() == false)
	{
		return;
	}
}

void CommonMethod::throwIfNeedStatusException(std::unique_ptr<Response>& response)
{
	if (response->getCode() >= 200 && response->getCode() < 300)
	{
	}
}

void CommonMethod::toJson(std::istream& stream, Json::Value& rootOut)
{
	Json::Reader reader;
	if (reader.parse(stream, rootOut, false) == false)
	{
		ELOG("Error parsing json: %s", reader.getFormattedErrorMessages().c_str());
		throw std::exception();
	}
}


