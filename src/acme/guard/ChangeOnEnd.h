//
// Created by Dawid Drozd aka Gelldur on 8/3/16.
//

#pragma once

template<class T, class V>
class ChangeOnEnd
{
public:
	ChangeOnEnd(T& value, const V& changeToValue)
			: _value(value)
			, _change(changeToValue)
	{
	}

	~ChangeOnEnd()
	{
		_value = _change;
	}

private:
	T& _value;
	const V& _change;
};


