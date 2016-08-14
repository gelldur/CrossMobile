//
// Created by Dawid Drozd aka Gelldur on 8/14/16.
//
#include <component/NodectBridge.h>

#include <Android.h>
#include <platform/Context.h>

#include <component/NodectHelper.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Class:     com_cross_mobile_component_NodectBridge
 * Method:    nest
 * Signature: (JLcom/cross/mobile/component/NodectHelper;)V
 */
JNIEXPORT void JNICALL Java_com_cross_mobile_component_NodectBridge_nest
		(JNIEnv* env, jclass clazz, jlong nativeObjectPointer, jobject nodectHelperRaw)
{
	Nodect* nodect = reinterpret_cast<Nodect*>(nativeObjectPointer);

	JniObject nodectHelper(nodectHelperRaw);
	NodectHelper::nest(*nodect, deserializeNodect(nodectHelper));
}

#ifdef __cplusplus
}
#endif
