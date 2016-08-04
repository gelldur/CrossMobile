/*
 * Utf8.cpp
 *
 *  Created on: Jul 16, 2013
 *      Author: Dawid Drozd
 */

#include "Utf8.h"
#include <cassert>
#include <algorithm>

using namespace std;

namespace Utf8
{

std::map<std::string, std::string> m_capitalSmallLetters;
std::map<std::string, std::string> m_smallCapitalLetters;
std::map<std::string, std::string> m_nationalLettersToASCII;

size_t length(const string& text)
{
	size_t size = text.size();
	const char* pChar = text.c_str();
	const char* pLastChar = pChar + size;
	assert(*pLastChar == '\0');

	size = 0; //counter

	while (pChar < pLastChar)
	{
		unsigned short bytes = getLetterByteSize((const unsigned char*) pChar);

		if (bytes <= 0)
		{
			break;
		}

		pChar += bytes;
		++size;
	}

	return size;
}

bool pop(string& text)
{
	if (text.empty())
	{
		return false;
	}

	//we have at least 1 sign
	size_t position = getPositionBeforeLastLetter(text);

	text.erase(text.begin() + position, text.end());

	return true;
}

string getLastLetter(const string& text)
{
	if (text.empty())
	{
		return "";
	}

	//we have at least 1 sign
	size_t position = getPositionBeforeLastLetter(text);

	return string(text.begin() + position, text.end());
}

string getFirstLetter(const string& text)
{
	if (text.empty())
	{
		return "";
	}

	unsigned size = getLetterByteSize((const unsigned char*) text.c_str());

	return string(text.begin(), text.begin() + size);
}

unsigned short getLetterByteSize(const unsigned char* const pPosition)
{
	//Look here https://en.wikipedia.org/wiki/UTF-8
	if ((*pPosition) >= 252)
	{
		//we need read 6 byte
		return 6;
	}
	else if ((*pPosition) >= 248)
	{
		//we need read 5 byte
		return 5;
	}
	else if ((*pPosition) >= 240)
	{
		//we need read 4 byte
		return 4;
	}
	else if ((*pPosition) >= 224)
	{
		//we need read 3 byte
		return 3;
	}
	else if ((*pPosition) >= 192)
	{
		//we need read 2 byte
		return 2;
	}
	else if ((*pPosition) <= 127)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

size_t getPositionBeforeLastLetter(const string& text)
{
	if (text.empty())
	{
		return 0;
	}

	size_t position = text.size() - 1;

	while (position > 0
		   && getLetterByteSize((const unsigned char*) text.c_str() + position) == 0)
	{
		assert(position >= 1);
		--position;
	}

	return position;
}

string toLower(const string& letter)
{
	map<string, string>::iterator result = m_capitalSmallLetters.find(letter);

	if (result != m_capitalSmallLetters.end())
	{
		return result->second;
	}

	return letter;
}

string toUpper(const string& letter)
{
	map<string, string>::iterator result = m_smallCapitalLetters.find(letter);

	if (result != m_smallCapitalLetters.end())
	{
		return result->second;
	}

	return letter;
}

string toLowerCase(const string& letters)
{
	string result;
	result.reserve(letters.size() + 1);
	unsigned position = 0;

	while (position < letters.size())
	{
		unsigned short size = getLetterByteSize(
				(const unsigned char*) letters.c_str() + position);
		string str = string(letters.c_str() + position, letters.c_str() + position + size);

		result += toLower(str);

		++position;
	}

	return result;
}

string toUpperCase(const string& letters)
{
	string result;
	result.reserve(letters.size() + 1);
	unsigned position = 0;

	while (position < letters.size())
	{
		unsigned short size = getLetterByteSize(
				(const unsigned char*) letters.c_str() + position);
		string str = string(letters.c_str() + position, letters.c_str() + position + size);

		result += toUpper(str);

		++position;
	}

	return result;
}

void normalizeString(std::string& text)
{
	static bool once = true;
	if (once)
	{
		Utf8::initNationalLettersMap();
		once = false;
	}
	for (unsigned i = 0; i < text.length(); ++i)
	{
		int size = getLetterByteSize(reinterpret_cast<const unsigned char* const>(text.c_str() + i));
		if (size > 1)
		{
			string letter(text.c_str() + i, size);
			auto newLetter = m_nationalLettersToASCII[letter];
			if (newLetter.empty())
			{
				newLetter = " ";
			}
			else if (newLetter[0] < 91 && newLetter[0] > 64)
			{
				newLetter[0] += 32;
			}


			text.replace(i, size, newLetter);
		}

		if (text[i] < 91 && text[i] > 64)
		{
			text[i] += 32;
		}
	}
}

bool getNormalizedChar(std::string& text, int offset)
{
	int size = getLetterByteSize(reinterpret_cast<const unsigned char* const>(text.c_str() + offset));
	if (size == 0)
	{
		return false;
	}
	if (size == 1)
	{
		if (text[offset] < 91 && text[offset] > 64)
		{
			text[offset] += 32;
		}
		return true;
	}

	string letter(text.c_str() + offset, size);
	auto newLetter = m_nationalLettersToASCII[letter];
	if (newLetter.empty())
	{
		newLetter = " ";
	}
	else if (newLetter[0] < 91 && newLetter[0] > 64)
	{
		newLetter[0] += 32;
	}

	text.replace(offset, size, newLetter);
	return true;
}

void initNationalLettersMap()
{
	m_nationalLettersToASCII.clear();
	string tab[][2] =
			{
					// Polish
					{  "Ą", "A"}
					, {"ą", "a"}
					, {"Ć", "C"}
					, {"ć", "c"}
					, {"Ę", "E"}
					, {"ę", "e"}
					, {"Ł", "L"}
					, {"ł", "l"}
					, {"Ó", "O"}
					, {"ó", "o"}
					, {"Ń", "N"}
					, {"ń", "n"}
					, {"Ś", "S"}
					, {"ś", "s"}
					, {"Ż", "Z"}
					, {"ż", "z"}
					, {"Ź", "Z"}
					, {"ź", "z"}
					,
					// Spanish and german
					{  "Ñ", "N"}
					, {"ñ", "n"}
					, {"Á", "A"}
					, {"à", "a"}
					, {"À", "A"}
					, {"á", "a"}
					, {"Å", "A"}
					, {"å", "a"}
					, {"Â", "A"}
					, {"â", "a"}
					, {"Ä", "A"}
					, {"ä", "a"}
					, {"È", "E"}
					, {"è", "e"}
					, {"É", "E"}
					, {"é", "e"}
					, {"Ê", "E"}
					, {"ê", "e"}
					, {"Ë", "E"}
					, {"ë", "e"}
					, {"Ó", "O"}
					, {"ó", "o"}
					, {"Ò", "O"}
					, {"ò", "o"}
					, {"Ö", "O"}
					, {"ö", "o"}
					, {"Ô", "O"}
					, {"ô", "o"}
					, {"Ú", "U"}
					, {"ú", "u"}
					, {"Ü", "U"}
					, {"ü", "u"}
					, {"Ù", "U"}
					, {"ù", "u"}
					, {"Û", "U"}
					, {"û", "u"}
					, {"Í", "I"}
					, {"í", "i"}
					, {"Ï", "I"}
					, {"ï", "i"}
					, {"Ì", "I"}
					, {"ì", "i"}
					, {"Î", "I"}
					, {"î", "i"}
					, {"ß", "B"}
			};

	for (auto&& pair : tab)
	{
		m_nationalLettersToASCII[pair[0]] = pair[1];
	}
}

string removeNationalLetters(const string& input)
{
	string result = input;

	if (m_nationalLettersToASCII.size() == 0)
	{
		initNationalLettersMap();
		assert(m_nationalLettersToASCII.size() > 0);
	}

	for (const auto& pair : m_nationalLettersToASCII)
	{
		auto it = result.begin();

		do
		{
			it = std::search(it, result.end(), pair.first.begin(), pair.first.end());

			if (it != result.end())
			{
				result.replace(it, it + pair.first.size(), pair.second);
				std::advance(it, pair.first.size());
			}
		}
		while (it != result.end());
	}

	return result;
}

}
