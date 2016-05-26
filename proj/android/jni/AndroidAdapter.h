//
// Created by Dawid Drozd aka Gelldur on 06.02.16.
//

#pragma once

#include <jni.h>
#include <bridge/NativeAdapter.h>
#include "JniObject.h"

class AndroidAdapter : public NativeAdapter
{
public:
	AndroidAdapter(JNIEnv* env, jobject applicationContext);
	virtual ~AndroidAdapter() = default;

	void onCreate(jobject activity);
	void onResume(jobject activity);
	void onPause(jobject activity);
	void onDestroy(jobject activity);

	virtual void onStartScreen(Screen* screen) override;

	virtual NativeView* findViewByTag(const std::string& tag) override;
private:
	JNIEnv* _env = nullptr;
	jclass _helper = nullptr;
	jobject _activity = nullptr;
	jobject _applicationContext = nullptr;

	jobject getBestContext();
};


