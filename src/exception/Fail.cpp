//
// Created by Dawid Drozd aka Gelldur on 6/30/16.
//

#include "Fail.h"

#include <exception>

#include <log.h>

Fail::Fail(const char* fileName, const char* functionName, int lineNumber)
		: _lineNumber(lineNumber)
		, _fileName(fileName)
		, _functionName(functionName)
{
	auto srcPosition = _fileName.rfind("/src/");
	if (srcPosition != std::string::npos)
	{
		_fileName.erase(0, srcPosition);
	}
	_stream << _fileName << " " << _fileName << ":" << _lineNumber;
}

Fail& Fail::add(const std::string& message)
{
	_stream << message;
	return *this;
}

void Fail::report()
{
	throw std::runtime_error(_stream.str());
}
