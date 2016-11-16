//
// Created by Dawid Drozd aka Gelldur on 8/12/16.
//

#pragma once

#include <Poco/Any.h>
#include <exception/Fail.h>

namespace FixAny
{

/**
 * On android i experienced some errors using typeid.operator==
 *
 * Sample:
 * 	DLOG("I have: %s -> %s == %d", listObject->type().name(), typeid(std::shared_ptr<AdapterList>).name()
 *	 , listObject->type() == typeid(std::shared_ptr<AdapterList>));
 *
 *	Strings were the same but == returns false
 *
 */
template<typename ValueType>
ValueType* Android_Fix_AnyCast(Poco::Any* operand)
{
	if (strcmp(operand->type().name(), typeid(ValueType).name()) == 0)
	{
		return Poco::UnsafeAnyCast<ValueType>(operand);
	}
	Fail(__FILE__, __func__, __LINE__).add("Can't AnyCast from ").add(operand->type().name()).add(" to ")
			.add(typeid(ValueType).name()).report();
	return nullptr;
}
}
