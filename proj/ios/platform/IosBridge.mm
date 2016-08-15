//
// Created by Dawid Drozd aka Gelldur on 7/28/16.
//

#include "IosBridge.h"

#import <UIKit/UIKit.h>

namespace CrossMobile
{

namespace Platform
{

std::string IosBridge::getWritablePathNative() const
{
	NSArray *paths = NSSearchPathForDirectoriesInDomains(NSLibraryDirectory, NSUserDomainMask, YES);
	NSString *libraryDirectory = [paths objectAtIndex:0];
	return std::string([libraryDirectory UTF8String]);
}

}
}

