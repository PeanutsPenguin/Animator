#pragma once

#include "LibMath/Angle/Radian.h"
#include <LibMath/Vector/Vec1.h>

namespace LibMath
{
	template <typename _Type>
	struct Vector<2, _Type>
	{
		Vector(void);									//Default constructor 

		explicit Vector(_Type value);					//Construcor with only one values 

		Vector(_Type x, _Type y);						//Constructor with values 

		Vector(const Vector<1, _Type>& a, const Vector<1, _Type>& b);		//Constructor with two Vector 1 in parameters

		Vector(const Vector<2, _Type>&) = default;		//Default copy constructor

		Vector(Vector<2, _Type>&&) = default;			//Default move constructor

		~Vector(void) = default;						//Default destructor 



		static Vector<2, _Type>	Zero(void);			//Return a vector (0, 0)

		static Vector<2, _Type>	One(void);			//Return a vector (1, 1)

		static Vector<2, _Type>	Down(void);			//Return a vector (0,-1)

		static Vector<2, _Type>	Left(void);			//Return a vector (-1, 0)

		static Vector<2, _Type>	Right(void);		//Return a vector (1, 0)

		static Vector<2, _Type> Up(void);			//Return a vector (0, 1)


		static LibMath::Radian		Angle(const Vector<2, _Type>&, const Vector<2, _Type>&);										//Return the radian angle between two vectors 

		static LibMath::Radian		Angle(const Vector<2, _Type>&, const Vector<2, _Type>&, const Vector<2, _Type>&);				//Return the radian angle between three vectors 

		static _Type				Distance(const Vector<2, _Type>&, const Vector<2, _Type>&);										//Return the distance between two vectors 

		static _Type				DistanceSquared(const Vector<2, _Type>&, const Vector<2, _Type>&);		//Return the square distance between two vectors

		static int					Compare(const Vector<2, _Type>&, const Vector<2, _Type>&);				//Compare the magnitude of two vectors 

		static bool					IsUnit(const Vector<2, _Type>&);										//Check if the vector is a unit vector

		static Vector<2, _Type>		Normalize(const Vector<2, _Type>&);										//Return the normalize version of the vector in parameters

		static Vector<2, _Type>		Project(const Vector<2, _Type>&, const Vector<2, _Type>&);				//Project the vector on another

		static Vector<2, _Type>		Reflect(const Vector<2, _Type>&, const Vector<2, _Type>&);				//Reflect the vector on another

		static _Type				Dot(const Vector<2, _Type>&, const Vector<2, _Type>&);					//Return the dot product between two vectors

		static _Type				Cross(const Vector<2, _Type>&, const Vector<2, _Type>&);				//Return the croos product between two vectors 

		static Vector<2, _Type>		toNormal(const Vector<2, _Type>&);										//Return the normal version of the vector in parameters 


		bool						isLongerThan(const Vector<2, _Type>&);									//Check if the vector is longer than another (same as compare but not static)

		bool						isShorterThan(const Vector<2, _Type>&);									//Check if the vector is shorte than another (same as compare but not static)

		void						translate(const Vector<2, _Type>& vec);									//Translate the vector with the given vector2

		void						scale(const Vector<2, _Type>& vec);										//Scale the vector with the given vector 2


		operator Vector<4, _Type>() const;		//Convertion operator into a vector4

		operator Vector<3, _Type>() const;		//Convertion operator into a vector3

		operator Vector<1, _Type>() const;		//Convertion operator into a vector1


		Vector<2, _Type>&	operator=(const Vector<2, _Type>&) = default;		//Default operator = to assign values of another vector

		Vector<2, _Type>&	operator=(Vector<2, _Type>&&) = default;			//Default operator = to move another vector into this one

		_Type&				operator[](size_t index);							//Operator [] to acces values 

		const _Type&		operator[](size_t index) const;						//Operator [] to acces values with const

		bool				operator==(const Vector<2, _Type>&) const;			//Operator == to see if the vector is equal to another

		bool				operator!=(const Vector<2, _Type>&) const;			//Operator != to see if the vector is different than another

		Vector<2, _Type>&	operator++(void);									//Operator ++ to increment by one everything

		Vector<2, _Type>	operator++(int) const;								//Operator ++ to increment by one everything with const

		Vector<2, _Type>&	operator--(void);									//Operator -- to decrement by one everything

		Vector<2, _Type>	operator--(int) const;								//Operator -- to decrement by one everything with const

		Vector<2, _Type>	operator+(const Vector<2, _Type>&) const;			//Operator + to add a vector 2 to the current one

		Vector<2, _Type>&	operator+=(const Vector<2, _Type>&);				//Operator += to add a vector 2 to the current one
			
		Vector<2, _Type>	operator+(_Type) const;								//Operator + to add a vector 2 to the current one with const

		Vector<2, _Type>&	operator+=(_Type);									//Operator += to add a vector 2 to the current one 

		Vector<2, _Type>	operator-(const Vector<2, _Type>&) const;			//Operator - to substract by vector 2 to the current one

		Vector<2, _Type>&	operator-=(const Vector<2, _Type>&);				//Operator -= to substract by vector 2 to the current one

		Vector<2, _Type>	operator-(void) const;								//Operator - to negate the vector 2
			
		Vector<2, _Type>	operator-(_Type) const;								//Operator - to substract by a constant 

		Vector<2, _Type>&	operator-=(_Type);									//Operator -= to substract by constant

		Vector<2, _Type>&	operator*=(const Vector<2, _Type>&);				//Operator *= to multiply by vector 2 to the current one

		Vector<2, _Type>	operator*(const Vector<2, _Type>&) const;			//Operator * to multiply by vector 2 to the current one

		Vector<2, _Type>&	operator*=(_Type);									//Operator *= to multiply by a constant

		Vector<2, _Type>	operator*(_Type) const;								//Operator * to multiply by a constant

		Vector<2, _Type>&	operator/=(const Vector<2, _Type>&);				//Operator /= to divide by a vector 2 to the current one
			
		Vector<2, _Type>	operator/(const Vector<2, _Type>&) const;			//Operator / to divide by a vector 2 to the current one

		Vector<2, _Type>&	operator/=(_Type);									//Operator /= to divide by a constant

		Vector<2, _Type>	operator/(_Type) const;								//Operator / to divide by a constant


			
		_Type	Magnitude(void) const;											//Return the magnitude of the vector

		_Type	MagnitudeSquared(void) const;									//Return the squared magnitude of the vector

		union { _Type x, r, s; };												//Union for the naming 
		union { _Type y, g, t; };												//Union for the naming 
	};	

	template <typename _Type>
	std::ostream& operator<<(std::ostream&, const Vector<2, _Type>&);			//Operator << to debug a vector in the console

	template <typename _Type>
	std::istream& operator>>(std::istream&, Vector<2, _Type>&);					//Operator >> to create a vector by a string	


	using Vector2 = typename Vector<2, float>;		//Set the name of the vector
}

#include <LibMath/Vector/Vec2.hpp>