//
// Created by Dawid Drozd aka Gelldur on 6/30/16.
//

#pragma once

#include <sstream>

class Fail
{
public:
	Fail(const char* fileName, const char* functionName, int lineNumber);

	template<class T>
	Fail& add(const T& message)
	{
		_stream << message;
		return *this;
	}

	void report();

private:
	int _lineNumber;
	std::string _fileName;
	std::string _functionName;
	std::stringstream _stream;
};


