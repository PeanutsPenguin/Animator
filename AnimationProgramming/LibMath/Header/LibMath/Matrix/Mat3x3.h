#pragma once

#include "LibMath/Trigonometry.h"

#include "exception"
#include <iostream>

#include <type_traits>
#include <initializer_list>

#include <LibMath/Vector/Vec3.h>
#include <LibMath/Matrix/Matrix.h>

namespace LibMath
{
	template <class _Type>
	struct Matrix<3, 3, _Type>
	{
		typedef LibMath::Vector<3, _Type> _ColumnType;
		typedef LibMath::Vector<3, _Type> _RowType;

	public:

		Matrix(void) = default;											//Default Matrix3 constructor 

		Matrix(const Matrix&) = default;								//Default Matrix3 copy constructor

		Matrix(Matrix&&) = default;										//Default Matrix3 move constructor 

		~Matrix(void) = default;										//Default Matrix3 destructor

		explicit Matrix(_Type v);										//Matrix3 constructor with a constant number in diagonal

		Matrix(const _RowType&, const _RowType&, const _RowType&);		//Matrix3 constructor with 3 vector in parameters to initialize the entire matrix

		Matrix<3, 3, _Type>& ToIdentity(void) requires (std::is_arithmetic_v<_Type>);		//Transform the matrix into an identity matrix

		Matrix<3, 3, _Type>& Empty(void);													//Fill the matrix with 0

		Matrix<3, 3, _Type> GetTranspose(void) const;										//Get the transpose matrix (invert rows and columns)

		Matrix<3, 3, _Type>& ToTranspose(void);												//Transpose the matrix (invert rows and columns)

		_Type GetDeterminant(void) const;													//Get the determinant of the matrix 

		Matrix<2, 2, _Type> GetMinor(size_t row, size_t column) const;						//Get the minor matrix depemding on a row and a column

		Matrix<3, 3, _Type> GetMinorsDeterminant(void) const;								//Get a matrix with every determinant of minors matrix 

		Matrix<3, 3, _Type> GetCofactors(void) const;										//Get the determinant of the minor matrix

		Matrix<3, 3, _Type> GetInverse(void) const;											//Get the inverse matrix (AB and BA are equals)


		static Matrix<3, 3, _Type> Zero(void);																								//Return a matrix full of Zero

		static Matrix<3, 3, _Type> Identity(void) requires (std::is_arithmetic_v<_Type>);													//Return a matrix with one in diagonal

		static Matrix<3, 3, _Type> Translate(const LibMath::Vector<2, _Type>&) requires (std::is_arithmetic_v<_Type>);						//Return a translate matrix with the specified Vector2 translator

		static Matrix<3, 3, _Type> Rotate(const LibMath::Vector<2, _Type>&) requires (std::is_arithmetic_v<_Type>);							//Return a rotate matrix with the specified Vector2 rotator

		static Matrix<3, 3, _Type> Scale(const LibMath::Vector<2, _Type>&) requires (std::is_arithmetic_v<_Type>);							//Return a scale matrix with the specified Vector2 scaler

		static Matrix<3, 3, _Type> Perspective(_Type fov, _Type aspect, _Type near, _Type far) requires (std::is_arithmetic_v<_Type>);		//Return a perspective matrix with a specified FOV, near and far


		bool operator==(const Matrix<3, 3, _Type>&) const;							//Operator == to check if the matrix is equal to another

		bool operator!= (const Matrix<3, 3, _Type>&) const;							//Operator != to check if the matrix is different than another

		Matrix<3, 3, _Type>& operator=(const Matrix<3, 3, _Type>&) = default;		//Default operator equal with another matrix 3 by 3

		Matrix<3, 3, _Type>& operator=(Matrix<3, 3, _Type>&&) = default;			//Default move operator equal with another matrix 3 by 3 


		_ColumnType& operator[](size_t index) noexcept { return this->m_matrix[index]; }					//Operator [] to get a a specified row in the matrix 

		const _ColumnType& operator[](size_t index) const noexcept { return this->m_matrix[index]; }		//const operator [] to get a specified row in the matrix


		template <size_t _C>
		Matrix<3, _C, _Type> operator*(const Matrix<3, _C, _Type>& rhs) const;		//Operator * with any matrix that has 3 rows

		Matrix<3, 3, _Type>& operator*=(const Matrix<3, 3, _Type>& rhs);			//Operator *= with another 3 by 3 matrix

		Matrix<3, 3, _Type> operator*(_Type rhs) const;								//Operator * with a constant number 

		Matrix<3, 3, _Type>& operator*=(_Type rhs);									//Opeartor *= with a constant number

		Matrix<3, 3, _Type> operator+(const Matrix<3, 3, _Type>& rhs) const;		//Operator + with another 3 by 3 matrix 

		Matrix<3, 3, _Type>& operator+=(const Matrix<3, 3, _Type>& rhs);			//Operator += with another 3 by 3 matrix

		Matrix<3, 3, _Type> operator-(const Matrix<3, 3, _Type>& rhs) const;		//Operator - with another 3 by 3 matrix

		Matrix<3, 3, _Type>& operator-=(const Matrix<3, 3, _Type>& rhs);			//Operator -= with another 3 by 3 matrix

	private:
		_ColumnType m_matrix[3];		//Matrix member is an array of Vector 3
	};

	template <class _Type = float>
	std::ostream& operator<<(std::ostream& os, const Matrix<3, 3, _Type>& matrix);		//Operator << to print a matrix in the console

	using Mat3 = typename Matrix<3, 3, float>;		//Define the name of the Matrix
}

#include <LibMath/Matrix/Mat3x3.hpp>