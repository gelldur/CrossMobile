//
// Created by Dawid Drozd aka Gelldur on 14.03.16.
//

#pragma once

class Response
{
public:

	static Response createGet();

	~Response() = default;

	int getCode() const
	{
		return 0;
	}

	/**
	 * Returns true if the code is in [200..300), which means the request was successfully received,
	 * understood, and accepted.
	 */
	bool isSuccessful() const
	{
		return getCode() >= 200 && getCode() < 300;
	}

private:
	Response() = default;

};


