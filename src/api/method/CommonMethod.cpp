//
// Created by Dawid Drozd aka Gelldur on 14.03.16.
//

#include "CommonMethod.h"

#include <sstream>

#include <Poco/Net/HTTPResponse.h>

#include <log.h>

std::deque<std::string> CommonMethod::_mockedResponses;

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

	if (_mockedResponses.empty() == false)
	{
		_mockedResponse.str(_mockedResponses.front());
		_mockedResponse.clear();
		_mockedResponses.pop_front();
		return _mockedResponse;
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

void CommonMethod::toJson(const std::string& document, Json::Value& rootOut)
{
	//Method used only for debug. You should use toJson(std::istream&,...)
	std::stringstream tmpStream(document);
	toJson(tmpStream, rootOut);
}

void CommonMethod::addMockedResponse(const std::string& response)
{
	_mockedResponses.emplace_back(response);
}
