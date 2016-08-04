/*
 * Utf8.h
 *
 *  Created on: Jul 16, 2013
 *      Author: Dawid Drozd
 */

#ifndef UTF8_H_
#define UTF8_H_

#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>

namespace Utf8
{

/**
 * @param text
 * @return text in lower case
 */
std::string toLowerCase(const std::string& letters);
std::string toUpperCase(const std::string& letters);

/**
 * @param text
 * @return letters count in text. No matter what language it must only be coded in UTF-8
 */
size_t length(const std::string& text);

/**
 * Remove last letter from std::string. This method support UTF-8
 * @param text this text will be erased. You can pass here even empty std::string :)
 * @return true if erase was successful
 */
bool pop(std::string& text);

bool getNormalizedChar(std::string& text, int offset);

void normalizeString(std::string& text);

/**
 * Gets last letter from std::string. This method support UTF-8
 * @param text any std::string, can be empty
 * @return last letter from std::string, if std::string is empty returns empty std::string
 */
std::string getLastLetter(const std::string& text);

/**
 * Gets first letter from std::string. This method supports UTF-8
 * @param text any std::string, can be empty
 * @return first letter from std::string, if std::string is empty returns that std::string
 */
std::string getFirstLetter(const std::string& text);

unsigned short getLetterByteSize(const unsigned char* const pPosition);
size_t getPositionBeforeLastLetter(const std::string& text);

void initNationalLettersMap();

std::string removeNationalLetters(const std::string& input);

}

#endif /* UTF8_H_ */
