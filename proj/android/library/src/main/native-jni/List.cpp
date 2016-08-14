//
// Created by Dawid Drozd aka Gelldur on 8/12/16.
//

#include <Android.h>

#include <JniObject.h>
#include <component/common/Pool.h>

#include <component/NodectBridge.h>
#include <component/adapter/AdapterList.h>
#include <exception/Fail.h>
#include <FixAny.h>

AdapterList* extractAdapterList(jlong listObjectPointer)
{
	Poco::Any* listObject = reinterpret_cast<Poco::Any*>(listObjectPointer);
	if (listObject->empty())
	{
		Fail(__FILE__, __func__, __LINE__)
				.add("missing listObject").report();
	}

	std::shared_ptr<AdapterList>* adapterList = FixAny::Android_Fix_AnyCast<std::shared_ptr<AdapterList>>(listObject);
	if (adapterList == nullptr)
	{
		Fail(__FILE__, __func__, __LINE__).add("implement AdapterList").report();
	}
	return adapterList->get();
}

#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     com_cross_mobile_component_adapter_List
 * Method:    getSize
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_com_cross_mobile_component_adapter_List_getSize
		(JNIEnv* env, jclass clazz, jlong listObjectPointer)
{
	AdapterList* adapterList = extractAdapterList(listObjectPointer);
	return static_cast<jint>(adapterList->getSize());
}

/*
 * Class:     com_cross_mobile_component_adapter_List
 * Method:    getIdentifier
 * Signature: (JI)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_cross_mobile_component_adapter_List_getIdentifier
		(JNIEnv* env, jclass clazz, jlong listObjectPointer, jint index)
{
	AdapterList* adapterList = extractAdapterList(listObjectPointer);
	const std::string& id = adapterList->getIdentifier(static_cast<int>(index));

	return (jstring) JniObject::convertToJavaValue(id).l;
}

/*
 * Class:     com_cross_mobile_component_adapter_List
 * Method:    setElement
 * Signature: (JILcom/cross/mobile/component/NodectBuilder;)V
 */
JNIEXPORT void JNICALL Java_com_cross_mobile_component_adapter_List_setElement
		(JNIEnv* env, jclass clazz, jlong listObjectPointer, jint index, jobject nodectRaw)
{
	AdapterList* adapterList = extractAdapterList(listObjectPointer);
	JniObject nodectJni(nodectRaw);
	Nodect nodect = deserializeNodect(nodectJni);

	adapterList->setElement(static_cast<int>(index), nodect);
}

#ifdef __cplusplus
}
#endif
