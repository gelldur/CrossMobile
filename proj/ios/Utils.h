//
// Created by Dawid Drozd aka Gelldur on 5/10/16.
//

#pragma once

#import <Foundation/Foundation.h>

#include <vector>
#include <string>

#define stringConvert(stdString) ((NSString * _Nonnull)[NSString stringWithUTF8String:stdString.c_str()])

NSArray* vectorConvert(const std::vector<std::string>& vec);
