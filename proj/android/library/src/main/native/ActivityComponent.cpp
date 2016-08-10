//
// Created by Dawid Drozd aka Gelldur on 8/10/16.
//

#include <Application.h>
#include <component/NodectBuilder.h>
#include <Director.h>
#include <log.h>
#include <platform/Context.h>
#include <screen/Screen.h>
#include <screen/ScreenCreator.h>

#include "Android.h"

jmethodID gHashCodeMethod = nullptr;
jmethodID gGetComponentNameMethod = nullptr;
jmethodID gInitComponentNameMethod = nullptr;

std::string convert(JNIEnv* env, jstring javaString)
{
	if (javaString == nullptr)
	{
		return "";
	}

	const jsize len = env->GetStringUTFLength(javaString);
	const char* strChars = env->GetStringUTFChars(javaString, JNI_FALSE);

	std::string converted(strChars, len);

	env->ReleaseStringUTFChars(javaString, strChars);

	return converted;
}

#ifdef __cplusplus
extern "C" {
#endif

void Java_com_cross_mobile_ActivityComponent_onCreate(JNIEnv* env
		, jobject activityComponent
		, jobject context
		, jstring screenName)
{
	auto name = convert(env, screenName);

	auto& director = Director::getInstance();
	auto screen = director.getApp()->getScreenCreator()->create(name, NodectBuilder::create(name, context)
			.addComponent<Container>().build());
	Director::getInstance().pushScreen(screen->getName(), std::move(screen));

	Director::getInstance().onCreateScreen(name);
}

void Java_com_cross_mobile_ActivityComponent_onResume(JNIEnv* env, jobject activityComponent, jobject context
		, jstring screenName)
{
	auto name = convert(env, screenName);
	Director::getInstance().onResumeScreen(name);
}

void Java_com_cross_mobile_ActivityComponent_onPause(JNIEnv* env, jobject activityComponent, jobject context
		, jstring screenName)
{
	DLOG("native onPause");
	auto name = convert(env, screenName);
	Director::getInstance().onPauseScreen(name);
}

void Java_com_cross_mobile_ActivityComponent_onDestroy(JNIEnv* env, jobject activityComponent, jobject context
		, jstring screenName)
{
	DLOG("native onDestroy");
	auto name = convert(env, screenName);
	Director::getInstance().onDestroyScreen(name);
}

#ifdef __cplusplus
}
#endif
