//
// Created by Dawid Drozd aka Gelldur on 16.03.16.
//

#pragma once

#include <string>
#include <stdexcept>

class ApiException : public std::runtime_error
{
	using inherited = std::runtime_error;
public:
	ApiException(const std::string& message);
};


