#pragma once

#include "LibMath/Trigonometry.h"

#include "exception"
#include <iostream>

#include <type_traits>
#include <initializer_list>

#include <LibMath/Vector/Vec2.h>
#include <LibMath/Matrix/Matrix.h>

namespace LibMath
{
	template <class _Type>
	struct Matrix<2, 2, _Type>
	{
		typedef LibMath::Vector<2, _Type> _ColumnType;
		typedef LibMath::Vector<2, _Type> _RowType;

	public:

		Matrix(void) = default;						//Default Matrix constructor 

		Matrix(const Matrix&) = default;			//Default copy constructor

		Matrix(Matrix&&) = default;					//Default move constructor

		~Matrix(void) = default;					//Default destructor

		explicit Matrix(_Type v);					//Create a matrix with a specific value on the diagonal

		Matrix(const _RowType&, const _RowType&);	//Create a matrix with specified value in parameters


		Matrix<2, 2, _Type>& ToIdentity(void) requires (std::is_arithmetic_v<_Type>);		//Change the matrix into an identity matrix (requires to check if the template type is a number)

		Matrix<2, 2, _Type>& Empty(void);													//Empty the matrix (or full it with 0)

		Matrix<2, 2, _Type> GetTranspose(void) const;										//Get the transpose matrix (reverse the line and columns of the matrix)

		Matrix<2, 2, _Type>& ToTranspose(void);												//Modify the matrix into its transpose

		_Type GetDeterminant(void) const;													//Get the determinant of the matrix


		static Matrix<2, 2, _Type> Zero(void);													//Return a matrix 2 by 2 full of 0

		static Matrix<2, 2, _Type> Identity(void) requires (std::is_arithmetic_v<_Type>);		//Return an identity matrix 2 by 2


		bool operator==(const Matrix<2, 2, _Type>&) const;							//Operator == to check if a matrix is the same as another

		bool operator!= (const Matrix<2, 2, _Type>&) const;							//Operator == to check if a matrix is different than another

		Matrix<2, 2, _Type>& operator=(const Matrix<2, 2, _Type>&) = default;		//Default operator = with another matrix

		Matrix<2, 2, _Type>& operator=(Matrix<2, 2, _Type>&&) = default;			//Default operator = to move a matrix


		_ColumnType& operator[](size_t index) noexcept { return this->m_matrix[index]; }					//operator [] to get a specific number in the matrix

		const _ColumnType& operator[](size_t index) const noexcept { return this->m_matrix[index]; }		//operator [] to get a specific number in the matrix (with const specifier)

		template <size_t _C>
		Matrix<2, _C, _Type> operator*(const Matrix<2, _C, _Type>& rhs) const;		//Multiply operator with any matri that has 2 column

		Matrix<2, 2, _Type>& operator*=(const Matrix<2, 2, _Type>& rhs);			//Operator *= for any other 2 by 2 matrix 

		Matrix<2, 2, _Type> operator*(_Type rhs) const;								//Operator * with a constant value

		Matrix<2, 2, _Type>& operator*=(_Type rhs);									//Operator *= with a constant value

		Matrix<2, 2, _Type> operator+(const Matrix<2, 2, _Type>& rhs) const;		//Operator + with any other 2 by 2 matrix

		Matrix<2, 2, _Type>& operator+=(const Matrix<2, 2, _Type>& rhs);			//Operator += with any other 2 by 2 matrix

		Matrix<2, 2, _Type> operator-(const Matrix<2, 2, _Type>& rhs) const;		//Operator - with any other 2 by 2 matrix

		Matrix<2, 2, _Type>& operator-=(const Matrix<2, 2, _Type>& rhs);			//Operator -= with any other 2 by 2 matrix

	private:
		_ColumnType m_matrix[2];		//Member of the matrix is a Vector 2 of Vector 2
	};

	template <class _Type = float>
	std::ostream& operator<<(std::ostream& os, const Matrix<2, 2, _Type>& matrix);		//Operator << to print a matrix in the console

	using Mat2 = typename Matrix<2, 2, float>;		//Define the name of the Matrix
}

#include <LibMath/Matrix/Mat2x2.hpp>