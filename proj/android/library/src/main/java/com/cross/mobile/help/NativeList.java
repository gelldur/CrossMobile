package com.cross.mobile.help;

import android.support.annotation.NonNull;

import com.cross.mobile.NativeObject;
import com.cross.mobile.component.NodectBuilder;
import com.cross.mobile.component.adapter.List;

/**
 * Created by Dawid Drozd aka Gelldur on 8/10/16.
 */
public class NativeList {

	public NativeList(@NonNull NativeObject object) {
		if (object == null) {
			throw new NullPointerException("object can't be null");
		}
		_object = object;
	}

	public int getSize() {
		return List.getSize(_object._pointer);
	}

	public void setRow(int position, NodectBuilder nodectBuilder) {
		List.setElement(_object._pointer, position, nodectBuilder);
	}

	private NativeObject _object;
}
