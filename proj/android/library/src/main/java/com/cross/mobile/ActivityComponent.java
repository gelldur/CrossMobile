package com.cross.mobile;

import android.content.Context;

/**
 * Created by Dawid Drozd aka Gelldur on 1/7/16.
 */
@SuppressWarnings("JniMissingFunction")
public class ActivityComponent {

	public ActivityComponent(String screenName) {
		_screenName = screenName;
	}

	public native void onCreate(Context context, String screenName);

	public native void onResume(Context context, String screenName);

	public native void onPause(Context context, String screenName);

	public native void onDestroy(Context context, String screenName);

	public native void addComponent(String name, Object component);

	public String getScreenName() {
		return _screenName;
	}

	private String _screenName;
}