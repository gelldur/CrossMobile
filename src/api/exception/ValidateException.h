//
// Created by Dawid Drozd aka Gelldur on 16.03.16.
//

#pragma once

#include "ApiException.h"

class ValidateException : public ApiException
{
public:
	ValidateException(int line, const char* functionName, const char* fileName, const std::string& message
					  , const std::string& dump);
};


