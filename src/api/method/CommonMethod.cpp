//
// Created by Dawid Drozd aka Gelldur on 14.03.16.
//

#include "CommonMethod.h"

#include <sstream>
#include <cassert>

#include <log.h>
#include <api/exception/ValidateException.h>
#include <exception/Fail.h>

CommonMethod::CommonMethod(const std::shared_ptr<Server>& server)
		: _server(server)
{
	assert(_server != nullptr);
}

std::unique_ptr<CommonMethod::Connection> CommonMethod::buildRequestGet(const std::string& pathAndQuery)
{
	using Poco::Net::HTTPRequest;
	using Poco::Net::HTTPResponse;
	using Poco::Net::HTTPMessage;

	auto data = std::unique_ptr<Connection>(new Connection(_server));
	data->request.setMethod(HTTPRequest::HTTP_GET);
	data->request.setURI(pathAndQuery);
	data->request.setVersion(HTTPMessage::HTTP_1_1);
	if (_server->isDebugable())
	{
		DLOG("Request[GET]: %s%s", _server->getHost().c_str(), data->request.getURI().c_str());
	}

	return data;
}

std::unique_ptr<CommonMethod::Connection> CommonMethod::requestGet(const std::string& pathAndQuery)
{
	auto data = buildRequestGet(pathAndQuery);

	data->send();
	return data;
}

std::unique_ptr<CommonMethod::Connection> CommonMethod::requestPostForm(
		const std::string& pathAndQuery
		, const std::map<std::string, std::string>& params)
{
	using Poco::Net::HTTPRequest;
	using Poco::Net::HTTPResponse;
	using Poco::Net::HTTPMessage;

	auto data = std::unique_ptr<Connection>(new Connection(_server));
	data->request.setMethod(HTTPRequest::HTTP_POST);
	data->request.setURI(pathAndQuery);
	data->request.setVersion(HTTPMessage::HTTP_1_1);
	data->request.setContentType("application/x-www-form-urlencoded");

	if (_server->isDebugable())
	{
		DLOG("Request[POST]: %s%s", _server->getHost().c_str(), data->request.getURI().c_str());
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
	if (_server->isDebugable())
	{
		DLOG("\tBody: %s", urlForm.c_str());
	}
	data->request.setContentLength(urlForm.length());

	data->send() << urlForm;
	return data;
}

std::unique_ptr<CommonMethod::Connection> CommonMethod::requestPostJson(
		const std::string& pathAndQuery
		, const std::string& json)
{
	using Poco::Net::HTTPRequest;
	using Poco::Net::HTTPResponse;
	using Poco::Net::HTTPMessage;

	auto data = std::unique_ptr<Connection>(new Connection(_server));
	data->request.setMethod(HTTPRequest::HTTP_POST);
	data->request.setURI(pathAndQuery);
	data->request.setVersion(HTTPMessage::HTTP_1_1);
	data->request.setContentType("application/json");
	data->request.setContentLength(json.length());

	if (_server->isDebugable())
	{
		DLOG("Request[POST]: %s%s", _server->getHost().c_str(), data->request.getURI().c_str());
		DLOG("\tBody: %s", json.c_str());
	}

	data->send() << json;
	return data;
}

void CommonMethod::toJson(std::istream& stream, Json::Value& rootOut)
{
	Json::Reader reader;

	std::string content;
	std::getline(stream, content, (char) EOF);

	if (reader.parse(content.data(), content.data() + content.size(), rootOut, false) == false)
	{
		throw ValidateException(__LINE__, __func__, __FILE__, reader.getFormattedErrorMessages(), content);
	}
}

void CommonMethod::toJson(const std::string& document, Json::Value& rootOut)
{
	//Method used only for debug. You should use toJson(std::istream&,...)
	std::stringstream tmpStream(document);
	toJson(tmpStream, rootOut);
}

CommonMethod::Connection::Connection(const std::shared_ptr<Server>& server)
		: _server(server)
{
}

std::ostream& CommonMethod::Connection::send()
{
	return _server->getSession()->sendRequest(request);
}

std::istream& CommonMethod::Connection::receive()
{
	_responseBody = &_server->getSession()->receiveResponse(response);
	return *_responseBody;//can't be null
}
