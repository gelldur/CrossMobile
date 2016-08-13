package com.cross.mobile;

/**
 * Created by Dawid Drozd aka Gelldur on 8/10/16.
 */

/**
 * Life of such object is on C++ side
 */
public class NativeObject {

	NativeObject(final long nativePointer) {
		_pointer = nativePointer;
	}

	public long _pointer;
}
