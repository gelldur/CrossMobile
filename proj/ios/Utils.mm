#import "Utils.h"
#import <UIKit/UIKit.h>

NSArray* vectorConvert(const std::vector<std::string>& vec)
{
	NSMutableArray* array = [NSMutableArray arrayWithCapacity:vec.size()];
	for(auto& element : vec)
	{
		[array addObject:stringConvert(element)];
	}
	return array;
}
