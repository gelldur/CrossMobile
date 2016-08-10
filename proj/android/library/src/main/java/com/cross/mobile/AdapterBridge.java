package com.cross.mobile;

/**
 * Created by Dawid Drozd aka Gelldur on 1/12/16.
 */
@SuppressWarnings("JniMissingFunction")
public class AdapterBridge {

	public AdapterBridge(final String name, final ActivityComponent activityComponent) {
		_name = name;
		_activityComponent = activityComponent;
	}

	public int getCount() {
		return nGetCount(_activityComponent.getScreenName(), _name);
	}

	public int getItem(final int position) {
		return nGetItem(_activityComponent.getScreenName(), _name, position);
	}

	private native int nGetCount(String screenName, String name);

	private native int nGetItem(String screenName, String name, final int position);

	private String _name;
	private ActivityComponent _activityComponent;
}
