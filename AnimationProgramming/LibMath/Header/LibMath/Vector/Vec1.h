#pragma once

#include <LibMath/Vector/Vector.h>

namespace LibMath
{
	template <typename _Type>
	struct Vector<1, _Type>
	{
		Vector(void);														//Default constructor

		explicit Vector(_Type value);										//Constructor with a value

		Vector(const Vector<1, _Type>&) = default;							//Default copy constructor

		Vector(Vector<1, _Type>&&) = default;								//Default move constructor

		~Vector(void) = default;											//Default destructor

		static Vector<1, _Type>	Zero(void);									//Fill the vector with 0

		static Vector<1, _Type>	One(void);									//Fill the vector with one

		Vector<1, _Type>& operator=(const Vector<1, _Type>&) = default;		//Operator equal to copy the value from another vector(with const)

		Vector<1, _Type>& operator=(Vector<1, _Type>&&) = default;			//Operator equal to copy the value from another vector

		_Type&	operator[](size_t index);									//Operator [] to get a value

		const _Type&	operator[](size_t index) const;						//Operator [] to get a value with const

		union { _Type x, r, s; };
	};

	using Vector1 = typename Vector<1, float>;								//Define the name of the vector
}

#include <LibMath/Vector/Vec1.hpp>