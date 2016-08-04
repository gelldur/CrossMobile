//
// Created by Dawid Drozd aka Gelldur on 14.03.16.
//

#include "CommonMethod.h"

#include <sstream>

#include <Poco/Net/HTTPResponse.h>
#include <Poco/Net/MediaType.h>

#include <log.h>

std::deque<std::string> CommonMethod::_mockedResponses;

std::istream& CommonMethod::requestGet(const Server& server, const std::string& pathAndQuery)
{
	using Poco::Net::HTTPRequest;
	using Poco::Net::HTTPResponse;
	using Poco::Net::HTTPMessage;

	HTTPRequest request(HTTPRequest::HTTP_GET, pathAndQuery, HTTPMessage::HTTP_1_1);
	if (server.isDebugable())
	{
		DLOG("Request[GET]: %s%s", server.getHost().c_str(), request.getURI().c_str());
	}

	if (_mockedResponses.empty() == false)
	{
		_mockedResponse.str(_mockedResponses.front());
		_mockedResponse.clear();
		_mockedResponses.pop_front();
		return _mockedResponse;
	}

	server.getSession()->sendRequest(request);
	HTTPResponse response;
	return server.getSession()->receiveResponse(response);
}

std::istream& CommonMethod::requestPostForm(const Server& server, const std::string& pathAndQuery
		, const std::map<std::string, std::string>& params)
{
	using Poco::Net::HTTPRequest;
	using Poco::Net::HTTPResponse;
	using Poco::Net::HTTPMessage;

	HTTPRequest request(HTTPRequest::HTTP_POST, pathAndQuery, HTTPMessage::HTTP_1_1);
	request.setContentType("application/x-www-form-urlencoded");

	if (server.isDebugable())
	{
		DLOG("Request[POST]: %s%s", server.getHost().c_str(), request.getURI().c_str());
	}
	if (_mockedResponses.empty() == false)
	{
		_mockedResponse.str(_mockedResponses.front());
		_mockedResponse.clear();
		_mockedResponses.pop_front();
		return _mockedResponse;
	}

	std::string urlForm;
	if (params.empty() == false)
	{
		for (auto& element : params)
		{
			urlForm += (element.first + '=' + element.second + '&');
		}
		urlForm.pop_back();
	}
	if (server.isDebugable())
	{
		DLOG("\tBody: %s", urlForm.c_str());
	}
	request.setContentLength(urlForm.length());

	auto& bodyData = server.getSession()->sendRequest(request);
	bodyData << urlForm;
	HTTPResponse response;
	return server.getSession()->receiveResponse(response);
}

std::istream& CommonMethod::requestPostJson(const Server& server, const std::string& pathAndQuery
		, const std::string& json)
{
	using Poco::Net::HTTPRequest;
	using Poco::Net::HTTPResponse;
	using Poco::Net::HTTPMessage;

	HTTPRequest request(HTTPRequest::HTTP_POST, pathAndQuery, HTTPMessage::HTTP_1_1);
	request.setContentType("application/json");

	if (server.isDebugable())
	{
		DLOG("Request[POST]: %s%s", server.getHost().c_str(), request.getURI().c_str());
		DLOG("\tBody: %s", json.c_str());
	}
	if (_mockedResponses.empty() == false)
	{
		_mockedResponse.str(_mockedResponses.front());
		_mockedResponse.clear();
		_mockedResponses.pop_front();
		return _mockedResponse;
	}

	request.setContentLength(json.length());

	auto& bodyData = server.getSession()->sendRequest(request);
	bodyData << json;
	HTTPResponse response;
	return server.getSession()->receiveResponse(response);
}

void CommonMethod::process(std::unique_ptr<Response>& response)
{
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

	std::string content;
	std::getline(stream, content, (char) EOF);

	if (reader.parse(content.data(), content.data() + content.size(), rootOut, false) == false)
	{
		ELOG("JSON:\n%s", content.c_str());

		ELOG("Error parsing json: %s", reader.getFormattedErrorMessages().c_str());
		throw std::runtime_error(reader.getFormattedErrorMessages().c_str());
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
