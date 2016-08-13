package com.cross.mobile;

import android.support.annotation.Keep;
import android.support.annotation.Nullable;

/**
 * Created by Dawid Drozd aka Gelldur on 8/10/16.
 */

@SuppressWarnings("JniMissingFunction")
@Keep
public class Extractor {

	public Extractor(String screenName) {
		_screenName = screenName;
	}

	@Nullable
	public NativeObject find(String tag) {
		long nativePointer = findNative(_screenName, tag);
		if (nativePointer == 0) {
			return null;
		}
		return new NativeObject(nativePointer);
	}

	@Keep
	private native long findNative(String screenName, String name);

	private String _screenName;
}
