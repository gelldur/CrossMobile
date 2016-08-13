package com.cross.mobile.help;

import android.app.Activity;
import android.os.Bundle;
import android.support.annotation.Nullable;

import com.cross.mobile.ActivityComponent;
import com.cross.mobile.Extractor;
import com.cross.mobile.NativeObject;
import com.cross.mobile.component.NodectBridge;
import com.cross.mobile.component.NodectBuilder;

/**
 * Created by Dawid Drozd aka Gelldur on 06.02.16.
 */
public abstract class NativeScreen extends Activity {

	public NativeScreen(String screenName) {
		_screenName = screenName;
		_extractor = new Extractor(screenName);
	}

	@Override
	protected void onCreate(final Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		_activityComponent = new ActivityComponent();

		_activityComponent.onCreate(this, _screenName);
	}

	@Override
	protected void onResume() {
		super.onResume();
		_activityComponent.onResume(this, _screenName);
	}

	@Override
	protected void onPause() {
		_activityComponent.onPause(this, _screenName);
		super.onPause();
	}

	@Override
	protected void onDestroy() {
		_activityComponent.onDestroy(this, _screenName);
		super.onDestroy();
	}

	protected void nestNodect(NodectBuilder nodectBuilder) {
		NodectBridge.nest(_activityComponent.getNativeObject()._pointer, nodectBuilder);
	}

	@Nullable
	protected NativeObject findNative(String tag) {
		return _extractor.find(tag);
	}

	protected NativeObject getNativeObject() {
		return _activityComponent.getNativeObject();
	}

	private ActivityComponent _activityComponent;
	private String _screenName;
	private Extractor _extractor;
}
