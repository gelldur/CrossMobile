//
// Created by Dawid Drozd aka Gelldur on 6/15/16.
//

#pragma once

#include <string>

#include "bridge/NativeObject.h"

namespace ViewHelper
{

void loadImage(NativeObject& view, const std::string& url);
void setText(NativeObject& view, const std::string& text);

}


