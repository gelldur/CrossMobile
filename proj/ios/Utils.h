//
// Created by Dawid Drozd aka Gelldur on 5/10/16.
//

#pragma once

#define NSString(cppString) [NSString stringWithUTF8String:cppString.c_str()]
#import <Foundation/Foundation.h>

#include <vector>
#include <string>

NSArray* vectorConvert(const std::vector<std::string>& vec);
