package com.cross.mobile.component;

import android.support.annotation.Keep;

/**
 * Created by Dawid Drozd aka Gelldur on 8/10/16.
 */

@SuppressWarnings("JniMissingFunction")
@Keep
public class NodectBridge {
	@Keep
	public static native void nest(long nodectPointer, NodectBuilder nodectBuilder);
}
