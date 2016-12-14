//
// Created by Dawid Drozd aka Gelldur on 6/30/16.
//

#include "Fail.h"

#include <stdexcept>

#include <log.h>

Fail::Fail(const std::string& fileName, const std::string& functionName, int lineNumber)
		: _lineNumber(lineNumber)
		, _fileName(fileName)
		, _functionName(functionName)
		, _stream(where(fileName, functionName, lineNumber))
{
}

void Fail::report()
{
	auto message = _stream.str();
	ILOG("Fail: %s", message.c_str());
	throw std::runtime_error(message);
}

std::string Fail::where(const std::string& fileName, const std::string& functionName, int lineNumber)
{
	std::stringstream stream;
	auto shortFileName = fileName;
	auto srcPosition = shortFileName.rfind("/src/");
	if (srcPosition != std::string::npos)
	{
		shortFileName.erase(0, srcPosition);
	}
	stream << shortFileName << " " << functionName << ":" << lineNumber << " ";
	return stream.str();
}
