//
// Created by pingu on 1/12/16.
//

#include <Director.h>
#include <log.h>
#include "AndroidAdapter.h"
#include <interface/DataSetAdapter.h>
#include <init.h>

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

int getHashCode(JNIEnv* env, jobject activityComponent)
{
	if (gHashCodeMethod == nullptr)
	{
		gHashCodeMethod = env->GetMethodID(env->GetObjectClass(activityComponent), "hashCode", "()I");
	}
	return env->CallIntMethod(activityComponent, gHashCodeMethod);
}

extern "C" {

jint JNI_OnLoad(JavaVM* vm, void* reserved)
{
	JNIEnv* env;
	if (vm->GetEnv(reinterpret_cast<void**>(&env), JNI_VERSION_1_6) != JNI_OK)
	{
		return -1;
	}

	Jni::get().onLoad(vm);

	return JNI_VERSION_1_6;
}

void Java_com_dexode_engine_BootActivity_onStartApplication(JNIEnv* env, jobject bootActivity
															, jobject applicationContext)
{
	DLOG("######################################################################################################");
	DLOG("######################################################################################################");
	DLOG("######################################################################################################");
	DLOG("native onStartApplication");

	auto app = createApplication(new AndroidAdapter(env, applicationContext));
	Director::getInstance().onStartApplication(app);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Java_com_dexode_engine_ActivityComponent_onCreate(JNIEnv* env, jobject activityComponent, jobject context
													   , jstring screenName)
{
	DLOG("native onCreate");
	auto name = convert(env, screenName);
	auto screen = Director::getInstance().findScreen(name);
	if (screen == nullptr)
	{
		return;
	}
	auto adapter = dynamic_cast<AndroidAdapter*>(screen->getNativeAdapter());
	adapter->onCreate(context);
	screen->onCreate();
}

void Java_com_dexode_engine_ActivityComponent_onResume(JNIEnv* env, jobject activityComponent, jobject context
													   , jstring screenName)
{
	DLOG("native onResume");
	auto name = convert(env, screenName);
	auto screen = Director::getInstance().findScreen(name);
	if (screen == nullptr)
	{
		return;
	}
	auto adapter = dynamic_cast<AndroidAdapter*>(screen->getNativeAdapter());
	adapter->onResume(context);
	screen->onResume();
}

void Java_com_dexode_engine_ActivityComponent_onPause(JNIEnv* env, jobject activityComponent, jobject context
													  , jstring screenName)
{
	DLOG("native onPause");
	auto name = convert(env, screenName);
	auto screen = Director::getInstance().findScreen(name);
	if (screen == nullptr)
	{
		return;
	}
	auto adapter = dynamic_cast<AndroidAdapter*>(screen->getNativeAdapter());
	adapter->onPause(context);
	screen->onPause();
}

void Java_com_dexode_engine_ActivityComponent_onDestroy(JNIEnv* env, jobject activityComponent, jobject context
														, jstring screenName)
{
	DLOG("native onDestroy");
	auto name = convert(env, screenName);
	auto screen = Director::getInstance().findScreen(name);
	if (screen == nullptr)
	{
		return;
	}
	auto adapter = dynamic_cast<AndroidAdapter*>(screen->getNativeAdapter());
	adapter->onDestroy(context);
	Director::getInstance().onDestroyScreen(convert(env, screenName));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

jint Java_com_dexode_engine_AdapterBridge_nGetCount(JNIEnv* env, jobject component, jstring screenName, jstring name)
{
	DLOG("AdapterComponent(native) nGetCount()");

	auto stringScreenName = convert(env, screenName);
	auto screen = Director::getInstance().findScreen(stringScreenName);
	if (screen == nullptr)
	{
		WLOG("No such screen: %s",stringScreenName.c_str());
		return 0;
	}

	auto componentName = convert(env, name);

	auto adapter = dynamic_cast<DataSetAdapter<int>*>(screen->findComponent(componentName));
	if (adapter == nullptr)
	{
		WLOG("No such component %s", componentName.c_str());
		return 0;
	}

	return adapter->getCount();
}


jint Java_com_dexode_engine_AdapterBridge_nGetItem(JNIEnv* env, jobject component, jstring screenName, jstring name
												   , jint position)
{
	DLOG("AdapterComponent(native) nGetItem()");
	auto stringScreenName = convert(env, screenName);
	auto screen = Director::getInstance().findScreen(stringScreenName);
	if (screen == nullptr)
	{
		WLOG("No such screen: %s",stringScreenName.c_str());
		return 0;
	}

	auto componentName = convert(env, name);
	auto adapter = dynamic_cast<DataSetAdapter<int>*>(screen->findComponent(componentName));
	if (adapter == nullptr)
	{
		WLOG("No such component %s", componentName.c_str());
		return 0;
	}

	return adapter->getItem(position);
}

}
