package com.cross.mobile;

import android.app.Activity;
import android.content.Context;
import android.os.Bundle;

/**
 * Created by Dawid Drozd aka Gelldur on 05.02.16.
 */
@SuppressWarnings("JniMissingFunction")
public class BootActivity extends Activity {

	@Override
	protected void onCreate(final Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		onStartApplication(getApplicationContext());
	}

	private native void onStartApplication(Context applicationContext);
}
