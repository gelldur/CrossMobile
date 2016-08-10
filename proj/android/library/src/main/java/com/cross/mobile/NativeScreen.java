package com.cross.mobile;

import android.app.Activity;
import android.os.Bundle;

/**
 * Created by Dawid Drozd aka Gelldur on 06.02.16.
 */
public abstract class NativeScreen extends Activity {

	public NativeScreen(String screenName) {
		_screenName = screenName;
		_activityComponent = new ActivityComponent();
	}

	@Override
	protected void onPostCreate(final Bundle savedInstanceState) {
		super.onPostCreate(savedInstanceState);
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

	private ActivityComponent _activityComponent;
	private String _screenName;
}
