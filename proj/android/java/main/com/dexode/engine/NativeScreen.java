package com.dexode.engine;

import android.app.Activity;
import android.os.Bundle;

import com.esportlivescore.R;

import java.lang.reflect.Field;

/**
 * Created by Dawid Drozd aka Gelldur on 06.02.16.
 */
public abstract class NativeScreen extends Activity {

	public NativeScreen() {
		_screenName = getClass().getSimpleName();
		_activityComponent = new ActivityComponent(_screenName);
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

	public Object findViewByTag(String tag) {
		try {
			final Field field = R.id.class.getField(tag);
			final int anInt = field.getInt(null);
			return findViewById(anInt);
		} catch (NoSuchFieldException e) {
			e.printStackTrace();
		} catch (IllegalAccessException e) {
			e.printStackTrace();
		}
		System.out.println("FAIL!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
		return null;
	}

	public void addComponent(String name, Object object) {
		_activityComponent.addComponent(name, object);
	}

	public ActivityComponent getActivityComponent() {
		return _activityComponent;
	}

	private ActivityComponent _activityComponent;
	private String _screenName;
}
