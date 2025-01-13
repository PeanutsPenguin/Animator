#pragma once

#include <iostream>
#include <string>

#include "LibMath/Angle/Radian.h"
#include <LibMath/Vector/Vec3.h>

namespace LibMath
{
	template <typename _Type>
	struct Vector<4, _Type>
	{
		Vector(void);																											//Default constructor

		explicit Vector(_Type value);																							//Construtor with one value

		Vector(_Type x, _Type y, _Type z, _Type w);																				//Constructor with 4 values in parameters 

		Vector(const Vector<1, _Type>& x, const Vector<1, _Type>& y, const Vector<1, _Type>& z, const Vector<1, _Type>& w);		//Construcotr with 4 vec1 in parameters 

		Vector(const Vector<2, _Type>& xy, const Vector<1, _Type>& z, const Vector<1, _Type>& w);								//Constructor with 1 vec2 and 2 vec 1

		Vector(const Vector<1, _Type>& x, const Vector<2, _Type>& yz, const Vector<1, _Type>& w);								//Constructor with 1 vec2 and 2 vec 1

		Vector(const Vector<1, _Type>& x, const Vector<1, _Type>& y, const Vector<2, _Type>& zw);								//Constructor with 1 vec2 and 2 vec 1

		Vector(const Vector<2, _Type>& xy, const Vector<2, _Type>& zw);															//Constructor with 2 vec2 

		Vector(const Vector<3, _Type>& xyz, const Vector<1, _Type>& w);															//Constructor with 1 vec3 and 1 vec1

		Vector(const Vector<1, _Type>& x, const Vector<3, _Type>& yzw);															//Constructor with 1 vec3 and 1 vec1
			
		Vector(const Vector<4, _Type>&) = default;																				//Default copy constructor

		Vector(Vector<4, _Type>&&) = default;																					//Default move constructor 

		~Vector(void) = default;																								//Default destructor 



		static Vector<4, _Type>	Zero(void);		//Return a vector (0, 0, 0)

		static Vector<4, _Type>	One(void);		//Return a vector (1, 1, 1)

		static Vector<4, _Type>	Up(void);		//Return a vector (0, 1, 0)

		static Vector<4, _Type>	Down(void);		//Return a vector (0, -1, 0)

		static Vector<4, _Type>	Left(void);		//Return a vector (-1, 0, 0)
			
		static Vector<4, _Type>	Right(void);	//Return a vector (1, 0, 0)

		static Vector<4, _Type>	Front(void);	//Return a vector (0, 0, 1)

		static Vector<4, _Type>	Back(void);		//Return a vector (0, 0, -1)


		static LibMath::Radian		Angle(const Vector<4, _Type>&, const Vector<4, _Type>&);				//Return the radian angle between two vectors 

		static _Type				Distance(const Vector<4, _Type>&, const Vector<4, _Type>&);				//Return the distance between two vectors
		
		static _Type				Distance2(const Vector<4, _Type>&, const Vector<4, _Type>&);			//Return the 2D distance between two vectors

		static _Type				DistanceSquared(const Vector<4, _Type>&, const Vector<4, _Type>&);		//Return the distance squared between two vectors 

		static _Type				Distance2Squared(const Vector<4, _Type>&, const Vector<4, _Type>&);		//Return the 2D distance squared between two vectors

		static int					Compare(const Vector<4, _Type>&, const Vector<4, _Type>&);				//Compare the magnitude of two vectors

		static bool					IsUnit(const Vector<4, _Type>&);										//Check if the vector is unit
			
		static Vector<4, _Type>		Normalize(const Vector<4, _Type>&);										//Return the normalize version of the vector
			
		static Vector<4, _Type>		Project(const Vector<4, _Type>&, const Vector<4, _Type>&);				//Project a vector on another

		static Vector<4, _Type>		Reflect(const Vector<4, _Type>&, const Vector<4, _Type>&);				//Reflect a vector on another

		static _Type				Dot(const Vector<4, _Type>&, const Vector<4, _Type>&);					//Return the dot product between two vectors 



		operator Vector<3, _Type>() const;		//Convertion operator into a vector3

		operator Vector<2, _Type>() const;		//Convertion operator into a vector2
		
		operator Vector<1, _Type>() const;		//Convertion operator into a vector1


		Vector<4, _Type>&	operator=(const Vector<4, _Type>&) = default;		//Default operator = to assign values of another vector

		Vector<4, _Type>&	operator=(Vector<4, _Type>&&) = default;			//Default operator = to move another vector into this one

		_Type&				operator[](size_t index);							//Operator [] to acces values 

		const _Type&		operator[](size_t index) const;						//Operator [] to acces values with

		bool				operator==(const Vector<4, _Type>&) const;			//Operator == to see if the vector is equal to another

		bool				operator!=(const Vector<4, _Type>&) const;			//Operator != to see if the vector is different than another

		Vector<4, _Type>&	operator++(void);									//Operator ++ to increment by one everything

		Vector<4, _Type>	operator++(int) const;								//Operator ++ to increment by one everything with const

		Vector<4, _Type>&	operator--(void);									//Operator -- to decrement by one everything

		Vector<4, _Type>	operator--(int) const;								//Operator -- to decrement by one everything with const

		Vector<4, _Type>	operator+(const Vector<4, _Type>&) const;			//Operator + to add a vector 4 to the current one

		Vector<4, _Type>&	operator+=(const Vector<4, _Type>&);				//Operator += to add a vector 4 to the current one with const

		Vector<4, _Type>	operator+(_Type) const;								//Operator + to add a vector 4 to the current one with const

		Vector<4, _Type>&	operator+=(_Type);									//Operator += to add a vector 4 to the current one 

		Vector<4, _Type>	operator-(const Vector<4, _Type>&) const;			//Operator - to substract by vector 4 to the current one

		Vector<4, _Type>&	operator-=(const Vector<4, _Type>&);				//Operator -= to substract by vector 4 to the current one

		Vector<4, _Type>	operator-(void) const;								//Operator - to negate the vector 4

		Vector<4, _Type>	operator-(_Type) const;								//Operator - to substract by a constant
			
		Vector<4, _Type>&	operator-=(_Type);									//Operator -= to substract by constant

		Vector<4, _Type>&	operator*=(const Vector<4, _Type>&);				//Operator *= to multiply by vector 4 to the current one

		Vector<4, _Type>	operator*(const Vector<4, _Type>&) const;			//Operator * to multiply by vector 4 to the current one
			
		Vector<4, _Type>&	operator*=(_Type);									//Operator *= to multiply by a constant

		Vector<4, _Type>	operator*(_Type) const;								//Operator * to multiply by a constant

		Vector<4, _Type>&	operator/=(const Vector<4, _Type>&);				//Operator /= to divide by a vector 4 to the current one

		Vector<4, _Type>	operator/(const Vector<4, _Type>&) const;			//Operator / to divide by a vector 4 to the current one

		Vector<4, _Type>&	operator/=(_Type);									//Operator /= to divide by a constan

		Vector<4, _Type>	operator/(_Type) const;								//Operator / to divide by a constant

	



		_Type	Magnitude(void) const;				//Return the magnitude of the vector

		_Type	MagnitudeSquared(void) const;		//Return the squared magnitude of the vector



		union { _Type x, r, s; };		//Union for the naming 
		union { _Type y, g, t; };		//Union for the naming 
		union { _Type z, b, p; };		//Union for the naming 
		union { _Type w, a, q; };		//Union for the naming 
	};

	template <typename _Type>
	std::ostream& operator<<(std::ostream&, const Vector<4, _Type>&);		//Operator << to debug a vector in the console

	template <typename _Type>
	std::istream& operator>>(std::istream&, Vector<4, _Type>&);				//Operator >> to create a vector by a string	


	using Vector4 = typename Vector<4, float>;		//Set the name of the vector
}

#include <LibMath/Vector/Vec4.hpp>
