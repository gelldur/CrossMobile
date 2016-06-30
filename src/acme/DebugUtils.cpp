//
// Created by Dawid Drozd aka Gelldur on 5/23/16.
//

#include "DebugUtils.h"
#include <log.h>
#include <sstream>

namespace Debug
{

std::string print(std::istream& stream)
{
	std::string tmpContent(std::istreambuf_iterator<char>(stream), {});
	DLOG("%s", tmpContent.c_str());

	return tmpContent;
}

}
