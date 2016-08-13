package com.cross.mobile.component.view;

import android.support.annotation.Keep;
import android.widget.ImageView;

/**
 * Created by Dawid Drozd aka Gelldur on 8/13/16.
 */
@Keep
public class Image {

	@Keep
	@SuppressWarnings("unused")// used in JNI
	public static void setDrawableImage(ImageView imageView, String imageName) {
		int resourceId =
				imageView.getResources().getIdentifier(imageName, "drawable", imageView.getContext().getPackageName());
		imageView.setImageResource(resourceId);
	}
}
