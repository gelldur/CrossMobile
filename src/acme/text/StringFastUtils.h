//
// Created by dawid on 10/29/15.
//

#pragma once

#include <vector>
#include <string>

const std::vector<std::string> processTags(
		const char* text
		, long minimumTagLength = 2
		, const std::vector<long>& skipPosition = {1000000, 10});

const std::vector<std::string> processTagsStripHtml(const char* nativeString, long minimumTagLength = 2);
