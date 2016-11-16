package com.cross.mobile;

import android.content.Context;
import android.support.annotation.Keep;

/**
 * Created by Dawid Drozd aka Gelldur on 8/9/16.
 */

@Keep
public class CrossMobileApplication {
	@Keep
	public native void onCreate(Context appContext);
}
