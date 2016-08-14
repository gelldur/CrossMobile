//
// Created by Dawid Drozd aka Gelldur on 8/12/16.
//

#include <Android.h>

#include <JniObject.h>
#include <Director.h>
#include <component/common/Pool.h>

#ifdef __cplusplus
extern "C" {
#endif
/**
 * Class:     com_cross_mobile_Extractor
 * Method:    findNative
 * Signature: (Ljava/lang/String;Ljava/lang/String;)J
 *
 * @return Poco::Any*
 */
JNIEXPORT jlong JNICALL Java_com_cross_mobile_Extractor_findNative
		(JNIEnv* env, jobject extractorObject, jstring screenNameRaw, jstring tagRaw)
{
	std::string screenName = JniObject::convertFromJavaObject<std::string>(screenNameRaw);
	std::string tag = JniObject::convertFromJavaObject<std::string>(tagRaw);

	auto screen = Director::getInstance().findScreen(screenName);

	auto anyObject = screen->getNativeScreen().getComponent<Pool>().getObject(tag);
	return reinterpret_cast<jlong>(anyObject);
}

#ifdef __cplusplus
}
#endif
