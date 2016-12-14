//
// Created by Dawid Drozd aka Gelldur on 16.03.16.
//

#include "ValidateException.h"

#include <json/json.h>

#include <exception/Fail.h>

namespace
{
std::string prepareMessage(int line, const char* functionName, const char* fileName
		, const std::string& message, const std::string& dump)
{
	Json::Value value(Json::ValueType::objectValue);
	value["where_throw"] = Fail::where(fileName, functionName, line);
	value["message"] = message;
	value["dump"] = dump;
	return value.toStyledString();
}

}

ValidateException::ValidateException(int line, const char* functionName, const char* fileName
		, const std::string& message, const std::string& dump)
		: inherited(prepareMessage(line, functionName, fileName, message, dump))
{
}

