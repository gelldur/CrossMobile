//
// Created by Dawid Drozd aka Gelldur on 6/30/16.
//

#pragma once

#include <sstream>

class Fail
{
public:
	Fail(const std::string& fileName, const std::string& functionName, int lineNumber);

	static std::string where(const std::string& fileName, const std::string& functionName, int lineNumber);

	template<class T>
	Fail& add(const T& message)
	{
		_stream << message;
		return *this;
	}

	Fail& br()
	{
		_stream << '\n';
		return *this;
	}

	void report();

private:
	int _lineNumber;
	std::string _fileName;
	std::string _functionName;
	std::stringstream _stream;
};


