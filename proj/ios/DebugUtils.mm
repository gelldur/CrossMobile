#import "DebugUtils.h"

@implementation DebugUtils

+ (UIColor *) getRandomColor
{
	switch (rand() % 8)
	{
		case 0:
			return [UIColor blueColor];
		case 1:
			return [UIColor greenColor];
		case 2:
			return [UIColor cyanColor];
		case 3:
			return [UIColor grayColor];
		case 4:
			return [UIColor redColor];
		case 5:
			return [UIColor yellowColor];
		case 6:
			return [UIColor orangeColor];
		default:
			return [UIColor magentaColor];
	}
}

@end
