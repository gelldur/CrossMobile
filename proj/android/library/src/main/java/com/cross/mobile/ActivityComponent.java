package com.cross.mobile;

import android.content.Context;
import android.support.annotation.Keep;

/**
 * Created by Dawid Drozd aka Gelldur on 1/7/16.
 */
@SuppressWarnings("JniMissingFunction")
@Keep
public class ActivityComponent {

	@Keep
	public native void onCreate(Context context, String screenName);

	@Keep
	public native void onResume(Context context, String screenName);

	@Keep
	public native void onPause(Context context, String screenName);

	@Keep
	public native void onDestroy(Context context, String screenName);

	public NativeObject getNativeObject() {
		return _nativeObject;
	}

	@Keep
	public void setNative(final long nativeObjectPointer) {
		System.out.println("Setting native pointer:" + nativeObjectPointer);
		_nativeObject = new NativeObject(nativeObjectPointer);
	}

	private NativeObject _nativeObject;
}