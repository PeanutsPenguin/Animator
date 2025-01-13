#pragma once

#include <LibMath/Vector/Vec1.h>

#include <float.h>


namespace LibMath
{
	template<typename _Type>
	inline LibMath::Vector<1, _Type>::Vector(void) : LibMath::Vector<1, _Type>(_Type(0)) {}

	template<typename _Type>
	inline LibMath::Vector<1, _Type>::Vector(_Type value) : x(value) {}

	template<typename _Type>
	inline Vector<1, _Type> LibMath::Vector<1, _Type>::Zero(void)
	{
		return Vector<1, _Type>();
	}

	template<typename _Type>
	inline Vector<1, _Type> LibMath::Vector<1, _Type>::One(void)
	{
		return Vector<1, _Type>(_Type(1));
	}

	template<typename _Type>
	inline _Type& LibMath::Vector<1, _Type>::operator[](size_t index)
	{
		switch (index)
		{
		default:
		case 0:
			return this->x;
		}
	}

	template<typename _Type>
	inline const _Type& LibMath::Vector<1, _Type>::operator[](size_t index) const
	{
		switch (index)
		{
		default:
		case 0:
			return this->x;
		}
	}
}