//
// Created by Dawid Drozd aka Gelldur on 8/12/16.
//

#pragma once

#include <JniObject.h>
#include <component/NodectBuilder.h>

void deserializeComponents(NodectBuilder::create& builder, JniObject& nodectHelper);

Nodect deserializeNodect(JniObject& nodectHelper);
