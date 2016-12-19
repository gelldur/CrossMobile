#import "BaseScreenController.h"

#include <string>

#include <Application.h>
#include <Director.h>
#include <component/NodectBuilder.h>
#include <platform/Context.h>
#include <platform/ContextHelper.h>
#include <screen/Screen.h>

#include <log.h>

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

	auto& director = Director::getInstance();
	auto screen = director.getApp()->getScreenCreator()->create(_screenName,
			NodectBuilder::createIos(_screenName, self).addComponent<Container>().build()); // Don't store in proprty!

	director.pushScreen(screen);

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
	//Not shure what should happen here. If I uncomment this, it will be a bug.
	//Director::getInstance().onDestroyScreen(_screenName);
}

- (void)dealloc
{
	DLOG("native dealloc: %s", _screenName.c_str()); // Like onDestroy?
	//[super dealloc]; ARC forbids explicit message send of 'dealloc'

	Director::getInstance().onDestroyScreen(_screenName);
}

@end
