//
// Created by Dawid Drozd aka Gelldur on 8/10/16.
//
#include <Android.h>

#include <Application.h>
#include <Director.h>
#include <JniObject.h>
#include <platform/Context.h>

#include <component/common/Pool.h>
#include <component/NodectBuilder.h>

#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT void JNICALL Java_com_cross_mobile_ActivityComponent_onCreate(JNIEnv* env
		, jobject activityComponentRaw
		, jobject context
		, jstring screenName)
{
	auto name = JniObject::convertFromJavaObject<std::string>(screenName);

	auto& director = Director::getInstance();
	auto screen = director.getApp()->getScreenCreator()->create(name, NodectBuilder::create(name, context)
			.addComponent<Container>().addComponent<Pool>().build());

	JniObject activityComponent(activityComponentRaw);
	activityComponent.callVoid("setNative", &screen->getNativeScreen());

	Director::getInstance().pushScreen(screen);
	Director::getInstance().onCreateScreen(name);
}

JNIEXPORT void JNICALL
Java_com_cross_mobile_ActivityComponent_onResume(JNIEnv* env
		, jobject activityComponent
		, jobject context
		, jstring screenName)
{
	auto name = JniObject::convertFromJavaObject<std::string>(screenName);
	Director::getInstance().onResumeScreen(name);
}

JNIEXPORT void JNICALL
Java_com_cross_mobile_ActivityComponent_onPause(JNIEnv* env
		, jobject activityComponent
		, jobject context
		, jstring screenName)
{
	auto name = JniObject::convertFromJavaObject<std::string>(screenName);
	Director::getInstance().onPauseScreen(name);
}

JNIEXPORT void JNICALL
Java_com_cross_mobile_ActivityComponent_onDestroy(JNIEnv* env
		, jobject activityComponent
		, jobject context
		, jstring screenName)
{
	auto name = JniObject::convertFromJavaObject<std::string>(screenName);
	Director::getInstance().onDestroyScreen(name);
}

#ifdef __cplusplus
}
#endif
