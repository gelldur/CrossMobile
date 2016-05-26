//
// Created by Dawid Drozd aka Gelldur on 09.03.16.
//

#pragma once

#include <bridge/NativeView.h>
#include "JniObject.h"

class AndroidView : public NativeView
{
public:
	AndroidView(JniObject jniObject)
			: _jniObject(jniObject)
	{

	}

private:
	JniObject _jniObject;
};


