//
// Created by dawid on 10/29/15.
//

#pragma once

#include <vector>
#include <string>

const std::vector<std::string> processTags(const char* text, int minimumTagLength = 2
										   , const std::vector<int>& skipPosition = {1000000, 10});

const std::vector<std::string> processTagsStripHtml(const char* nativeString, int minimumTagLength = 2);