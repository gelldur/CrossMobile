#import "SelectorWrapper.h"

#include <log.h>

@implementation SelectorWrapper
{
	std::function<void()> _lambda;
}

- (id)init:(const std::function<void()>&)lambda
{
	self = [super init];
	if (self == nil)
	{
		return nil;
	}
	_lambda = lambda;

	return self;
}

- (void)onWrapperClick:(UITapGestureRecognizer *)recognizer
{
	DLOG("Wrapper!!!!!!!!!!!!!!!!!!!!");
	_lambda();
}

@end
