#pragma once

#include <iostream>
#include <string>

#include "LibMath/Angle/Radian.h"
#include <LibMath/Vector/Vec2.h>

namespace LibMath
{
	template <typename _Type>
	struct Vector<3, _Type>
	{
		Vector(void);									//Default constructor

		explicit Vector(_Type value);					//Fill the vector with one value

		Vector(_Type x, _Type y, _Type z);				//Constructor with three float in parameters to set values

		Vector(const Vector<3, _Type>&) = default;		//Default copy constructor

		Vector(Vector<3, _Type>&&) = default;			//Default move constructor 

		~Vector(void) = default;



		static Vector<3, _Type>	zero(void);				//Return a vector (0, 0, 0)

		static Vector<3, _Type>	one(void);				//Return a vector (1, 1, 1)
			
		static Vector<3, _Type>	up(void);				//Return a vector (0, 1, 0)

		static Vector<3, _Type>	down(void);				//Return a vector (0, -1, 0)

		static Vector<3, _Type>	left(void);				//Return a vector (-1, 0, 0)

		static Vector<3, _Type>	right(void);			//Return a vector (1, 0, 0)

		static Vector<3, _Type>	front(void);			//Return a vector (0, 0, 1)

		static Vector<3, _Type>	back(void);				//Return a vector (0, 0, -1)


		static LibMath::Radian		Angle(const Vector<3, _Type>&, const Vector<3, _Type>&);				//Return the radian angle between two vectors 

		static LibMath::Radian		Angle(const Vector<3, _Type>&, const Vector<3, _Type>&, const Vector<3, _Type>&);

		Radian						angleFrom(const Vector<3, _Type>& other, bool range) const;

		static _Type				distance(const Vector<3, _Type>&, const Vector<3, _Type>&);				//Return the distance between two vectors

		static _Type				distance2(const Vector<3, _Type>&, const Vector<3, _Type>&);			//Return the 2D distance between two vectors

		static _Type				distanceSquared(const Vector<3, _Type>&, const Vector<3, _Type>&);		//Return the distance squared between two vectors 
		
		static _Type				distance2Squared(const Vector<3, _Type>&, const Vector<3, _Type>&);		//Return the 2D distance squared between two vectors

		static int					compare(const Vector<3, _Type>&, const Vector<3, _Type>&);				//Compare the magnitude of two vectors

		static bool					IsUnit(const Vector<3, _Type>&);										//Check if the vector is unit

		static Vector<3, _Type>		normalize(const Vector<3, _Type>&);										//Return the normalize version of the vector 

		static Vector<3, _Type>		Project(const Vector<3, _Type>&, const Vector<3, _Type>&);				//Project a vector on another

		static Vector<3, _Type>		Reflect(const Vector<3, _Type>&, const Vector<3, _Type>&);				//Reflect a vector on another

		static _Type				dot(const Vector<3, _Type>&, const Vector<3, _Type>&);					//Return the dot product between two vectors 

		static Vector<3, _Type>		cross(const Vector<3, _Type>&, const Vector<3, _Type>&);				//Retunr the cross product between two vectors


		operator Vector<4, _Type>() const;		//Convertion operator into a vector4

		operator Vector<2, _Type>() const;		//Convertion operator into a vector2

		operator Vector<1, _Type>() const;		//Convertion operator into a vector1


		bool					isLongerThan(const Vector<3, _Type>&);												//Check if a vector is longer than another(same as compare but without static)

		bool					isShorterThan(const Vector<3, _Type>&);												//Check if a vector is shorter than another(same as compare but without static)

		bool					compareSign(const Vector<3, _Type>&);												//Compare the signe of the x, y and z of the vector 

		void					translate(const Vector<3, _Type>&);													//Translate the vector

		void					scale(const Vector<3, _Type>&);														//Scale the vector 

		void					rotate(const LibMath::Radian&, const LibMath::Radian&, const LibMath::Radian&);		//Rotate the vector with three radian for each axis

		void					rotate(const LibMath::Radian&, const LibMath::Vector<3, _Type>&);					//Rotate the vector with a specific radian and a vec 3 for wich axis 


		Vector<3, _Type>&		operator=(const Vector<3, _Type>&) = default;			//Default operator = to assign values of another vector

		Vector<3, _Type>&		operator=(Vector<3, _Type>&&) = default;				//Default operator = to move another vector into this one

		_Type&					operator[](size_t index);								//Operator [] to acces values 

		const _Type&			operator[](size_t index) const;							//Operator [] to acces values with const

		bool					operator==(const Vector<3, _Type>&) const;				//Operator == to see if the vector is equal to another
			
		bool					operator!=(const Vector<3, _Type>&) const;				//Operator != to see if the vector is different than another

		Vector<3, _Type>&		operator++(void);										//Operator ++ to increment by one everything

		Vector<3, _Type>		operator++(int) const;									//Operator ++ to increment by one everything with const

		Vector<3, _Type>&		operator--(void);										//Operator -- to decrement by one everything

		Vector<3, _Type>		operator--(int) const;									//Operator -- to decrement by one everything with const

		Vector<3, _Type>		operator+(const Vector<3, _Type>&) const;				//Operator + to add a vector 3 to the current one

		Vector<3, _Type>&		operator+=(const Vector<3, _Type>&);					//Operator += to add a vector 3 to the current one with const

		Vector<3, _Type>		operator+(_Type) const;									//Operator + to add a vector 3 to the current one with const

		Vector<3, _Type>&		operator+=(_Type);										//Operator += to add a vector 3 to the current one 
			
		Vector<3, _Type>		operator-(const Vector<3, _Type>&) const;				//Operator - to substract by vector 3 to the current one

		Vector<3, _Type>&		operator-=(const Vector<3, _Type>&);					//Operator -= to substract by vector 3 to the current one

		Vector<3, _Type>		operator-(void) const;									//Operator - to negate the vector 3
		
		Vector<3, _Type>		operator-(_Type) const;									//Operator - to substract by a constant 

		Vector<3, _Type>&		operator-=(_Type);										//Operator -= to substract by constant
			
		Vector<3, _Type>&		operator*=(const Vector<3, _Type>&);					//Operator *= to multiply by vector 3 to the current one

		Vector<3, _Type>		operator*(const Vector<3, _Type>&) const;				//Operator * to multiply by vector 3 to the current one

		Vector<3, _Type>&		operator*=(_Type);										//Operator *= to multiply by a constant

		Vector<3, _Type>		operator*(_Type) const;									//Operator * to multiply by a constant

		Vector<3, _Type>&		operator/=(const Vector<3, _Type>&);					//Operator /= to divide by a vector 3 to the current one
			
		Vector<3, _Type>		operator/(const Vector<3, _Type>&) const;				//Operator / to divide by a vector 3 to the current one

		Vector<3, _Type>&		operator/=(_Type);										//Operator /= to divide by a constan

		Vector<3, _Type>		operator/(_Type) const;									//Operator / to divide by a constant


		_Type	Magnitude(void) const;				//Return the magnitude of the vector

		_Type	MagnitudeSquared(void) const;		//Return the squared magnitude of the vector



		union { _Type x, r, s; };		//Union for the naming 
		union { _Type y, g, t; };		//Union for the naming 
		union { _Type z, b, p; };		//Union for the naming 
	};

	template <typename _Type>
	std::ostream& operator<<(std::ostream&, const Vector<3, _Type>&);		//Operator << to debug a vector in the console

	template <typename _Type>
	std::istream& operator>>(std::istream&, Vector<3, _Type>&);				//Operator >> to create a vector by a string	


	using Vector3 = typename Vector<3, float>;		//Set the name of the vector
}

#include <LibMath/Vector/Vec3.hpp>