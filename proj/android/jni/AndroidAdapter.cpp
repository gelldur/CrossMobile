//
// Created by Dawid Drozd aka Gelldur on 06.02.16.
//

#include <Director.h>
#include <log.h>
#include "AndroidAdapter.h"
#include "AndroidView.h"

jstring convert(JNIEnv* env, const std::string& string)
{
	return env->NewStringUTF(string.c_str());
}


AndroidAdapter::AndroidAdapter(JNIEnv* env, jobject applicationContext)
		: _env(env)
		, _applicationContext(applicationContext)
{
	_helper = _env->FindClass("com/dexode/engine/AndroidAdapter");
	if (_helper == nullptr)
	{
		FLOG("Can't find AndroidAdapter!");
	}
}


void AndroidAdapter::onStartScreen(Screen* screen)
{
	//TODO start android activity
	//create intent -> if no current activity start on app context
	auto methodId = _env->GetStaticMethodID(_helper, "startScreen", "(Landroid/content/Context;Ljava/lang/String;)V");

	_env->CallStaticVoidMethod(_helper, methodId, getBestContext(), convert(_env, screen->getName()));
}

void AndroidAdapter::onCreate(jobject activity)
{
	_activity = activity;
}

void AndroidAdapter::onResume(jobject activity)
{
	_activity = activity;
}

void AndroidAdapter::onPause(jobject activity)
{
	_activity = nullptr;
}

void AndroidAdapter::onDestroy(jobject activity)
{
	_activity = nullptr;
}

jobject AndroidAdapter::getBestContext()
{
	return _activity == nullptr ? _applicationContext : _activity;
}

NativeView* AndroidAdapter::findViewByTag(const std::string& tag)
{
	if (_activity == nullptr)
	{
		ELOG("No activity!");
		return nullptr;
	}

	JniObject activity(_activity);

	JniObject defRet("java.lang.Object");

	auto returned = activity.call("findViewByTag", defRet, tag);
	if (returned.getInstance() != nullptr)
	{
		return new AndroidView(returned);
	}
	WLOG("View [%s] not found!", tag.c_str());
	return nullptr;
}
