//
// Created by Dawid Drozd aka Gelldur on 05.04.16.
//

#pragma once

namespace Acme
{

namespace RGBA
{

inline int red(int value)
{
	return value & 0xff;
}

inline int green(int value)
{
	return (value >> 8) & 0xff;
}

inline int blue(int value)
{
	return (value >> 16) & 0xff;
}

inline int alpha(int value)
{
	return (value >> 24) & 0xff;
}

}

}