//
// Created by Dawid Drozd aka Gelldur on 6/30/16.
//

#pragma once

#include "Nodect.h"

namespace NodectHelper
{

Nodect& find(const Nodect& nodect, const std::string& tag);

void nest(Nodect& owner, Nodect&& nodect);

Nodect& remove(Nodect& owner, const std::string& nodectName);

void clear(Nodect& owner);

}


