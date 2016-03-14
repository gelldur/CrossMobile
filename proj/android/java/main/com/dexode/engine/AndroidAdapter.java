package com.dexode.engine;

import android.content.Context;
import android.content.Intent;
import android.content.pm.ActivityInfo;
import android.content.pm.PackageInfo;
import android.content.pm.PackageManager;

import com.dexode.util.log.Logger;
import com.esportlivescore.ESportLiveScoreApplication;

/**
 * Created by Dawid Drozd aka Gelldur on 06.02.16.
 */
public class AndroidAdapter {

	public static void startScreen(Context context, String screenName) {

		PackageManager pm = ESportLiveScoreApplication.getInstance().getPackageManager();

		ActivityInfo screen = null;
		try {
			PackageInfo info = pm.getPackageInfo(ESportLiveScoreApplication.getInstance().getPackageName(),
												 PackageManager.GET_ACTIVITIES);

			for (ActivityInfo activityInfo : info.activities) {
				System.out.println("Name: " + activityInfo.name);
				if (activityInfo.name.endsWith(screenName)) {
					screen = activityInfo;
					break;
				}
			}


		} catch (PackageManager.NameNotFoundException e) {
			throw new RuntimeException("Fail");
		}

		if (screen == null) {
			Logger.e("No such screen!");
			return;
		}
		try {
			final Class<?> aClass = Class.forName(screen.name);
			Intent intent = new Intent(context, aClass);
			if (context == context.getApplicationContext()) {
				intent.addFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
			}
			context.startActivity(intent);
		} catch (ClassNotFoundException e) {
			throw new RuntimeException("Fail");
		}
	}

}
