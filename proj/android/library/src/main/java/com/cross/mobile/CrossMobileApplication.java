package com.cross.mobile;

import android.support.annotation.Keep;

/**
 * Created by Dawid Drozd aka Gelldur on 8/9/16.
 */

@SuppressWarnings("JniMissingFunction")
@Keep
public class CrossMobileApplication {
	@Keep
	public native void onCreate();
}
