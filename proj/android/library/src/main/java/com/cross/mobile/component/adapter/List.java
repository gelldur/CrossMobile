package com.cross.mobile.component.adapter;

import android.support.annotation.Keep;

import com.cross.mobile.component.NodectBuilder;

/**
 * Created by Dawid Drozd aka Gelldur on 8/11/16.
 */

@SuppressWarnings("JniMissingFunction")
@Keep
public class List {
	@Keep
	public static native int getSize(final long listObjectPointer);

	@Keep
	public static native String getIdentifier(final long listObjectPointer, int position);

	@Keep
	public static native void setElement(final long listObjectPointer, int position, NodectBuilder object);
}
