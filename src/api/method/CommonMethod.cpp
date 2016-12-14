//
// Created by Dawid Drozd aka Gelldur on 14.03.16.
//

#include "CommonMethod.h"

#include <sstream>
#include <cassert>

#include <Poco/Net/HTTPResponse.h>
#include <Poco/Net/MediaType.h>

#include <log.h>
#include <api/exception/ValidateException.h>
#include <exception/Fail.h>

std::unique_ptr<CommonMethod::HTTPMethod>
CommonMethod::requestGet(const Server& server, const std::string& pathAndQuery)
{
	using Poco::Net::HTTPRequest;
	using Poco::Net::HTTPResponse;
	using Poco::Net::HTTPMessage;

	auto data = std::unique_ptr<HTTPMethod>(new HTTPMethod(server.getSession()));
	data->request.setMethod(HTTPRequest::HTTP_GET);
	data->request.setURI(pathAndQuery);
	data->request.setVersion(HTTPMessage::HTTP_1_1);
	if (server.isDebugable())
	{
		DLOG("Request[GET]: %s%s", server.getHost().c_str(), data->request.getURI().c_str());
	}

	data->send();
	return data;
}

std::unique_ptr<CommonMethod::HTTPMethod>
CommonMethod::requestPostForm(const Server& server, const std::string& pathAndQuery
		, const std::map<std::string, std::string>& params)
{
	using Poco::Net::HTTPRequest;
	using Poco::Net::HTTPResponse;
	using Poco::Net::HTTPMessage;

	auto data = std::unique_ptr<HTTPMethod>(new HTTPMethod(server.getSession()));
	data->request.setMethod(HTTPRequest::HTTP_POST);
	data->request.setURI(pathAndQuery);
	data->request.setVersion(HTTPMessage::HTTP_1_1);
	data->request.setContentType("application/x-www-form-urlencoded");

	if (server.isDebugable())
	{
		DLOG("Request[POST]: %s%s", server.getHost().c_str(), data->request.getURI().c_str());
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
	data->request.setContentLength(urlForm.length());

	data->send() << urlForm;
	return data;
}

std::unique_ptr<CommonMethod::HTTPMethod>
CommonMethod::requestPostJson(const Server& server, const std::string& pathAndQuery
		, const std::string& json)
{
	using Poco::Net::HTTPRequest;
	using Poco::Net::HTTPResponse;
	using Poco::Net::HTTPMessage;

	auto data = std::unique_ptr<HTTPMethod>(new HTTPMethod(server.getSession()));
	data->request.setMethod(HTTPRequest::HTTP_POST);
	data->request.setURI(pathAndQuery);
	data->request.setVersion(HTTPMessage::HTTP_1_1);
	data->request.setContentType("application/json");
	data->request.setContentLength(json.length());

	if (server.isDebugable())
	{
		DLOG("Request[POST]: %s%s", server.getHost().c_str(), data->request.getURI().c_str());
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

CommonMethod::HTTPMethod::HTTPMethod(Poco::Net::HTTPClientSession* session)
		: _session(session)
{
}

std::ostream& CommonMethod::HTTPMethod::send()
{
	return _session->sendRequest(request);
}

std::istream& CommonMethod::HTTPMethod::receive()
{
	_responseBody = &_session->receiveResponse(response);
	return *_responseBody;//can't be null
}
