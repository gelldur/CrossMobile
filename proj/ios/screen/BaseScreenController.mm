#import "BaseScreenController.h"

#include <string>

#include <Director.h>
#include <component/NodectBuilder.h>
#include <platform/Context.h>
#include <screen/Screen.h>

#include <log.h>
#include <screen/ScreenCreator.h>

@implementation BaseScreenController
{
	std::string _screenName;
}

- (id)initWithName:(NSString*)name
{
	self = [super init];
	if (self == nil)
	{
		return nil;
	}

	_screenName = std::string([name UTF8String]);
	auto screen = ScreenCreator::create(_screenName,
		NodectBuilder::create(_screenName, self).addComponent<Container>().build()); // Don't store in proprty!
	Director::getInstance().pushScreen(screen->getName(), std::move(screen));

	return self;
}

- (const char*)getName
{
	return _screenName.c_str();
}

- (void)viewDidLoad
{
	[super viewDidLoad];
	DLOG("native viewDidLoad: %s", _screenName.c_str()); // Like onCreate

	Director::getInstance().onCreateScreen(_screenName);
}

- (void)viewWillAppear:(BOOL)animated
{
	[super viewWillAppear:animated];
	DLOG("native viewWillAppear: %s", _screenName.c_str()); // Like onResume

	Director::getInstance().onResumeScreen(_screenName);
}

- (void)viewWillDisappear:(BOOL)animated
{
	[super viewWillDisappear:animated];
	DLOG("native viewWillDisappear: %s", _screenName.c_str()); // Like onPause

	Director::getInstance().onPauseScreen(_screenName);
}

- (void)didReceiveMemoryWarning
{
	[super didReceiveMemoryWarning];
	DLOG("native didReceiveMemoryWarning: %s", _screenName.c_str()); // Like onDestroy?

	Director::getInstance().onDestroyScreen(_screenName);
}

- (void)dealloc
{
	DLOG("native dealloc: %s", _screenName.c_str()); // Like onDestroy?
	//[super dealloc]; ARC forbids explicit message send of 'dealloc'

	Director::getInstance().onDestroyScreen(_screenName);
}

@end
