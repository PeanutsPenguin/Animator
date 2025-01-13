#pragma once

#include "LibMath/Trigonometry.h"

#include "exception"
#include <iostream>

#include <type_traits>
#include <initializer_list>

#include <LibMath/Vector/Vec4.h>
#include <LibMath/Matrix/Matrix.h>

namespace LibMath
{
	template <class _Type>
	struct Matrix<4, 4, _Type> 
	{
		typedef LibMath::Vector<4, _Type> _ColumnType;
		typedef LibMath::Vector<4, _Type> _RowType;

	public:

		Matrix(void) = default;															//Default constructor

		Matrix(const Matrix&) = default;												//Default copy constructor

		Matrix(Matrix&&) = default;														//Default move contructor

		~Matrix(void) = default;														//Default destructor

		explicit Matrix(_Type v);														//Constructor with a specified constant in diagonal

		Matrix(const _RowType&, const _RowType&, const _RowType&, const _RowType&);		//Constructor with 4 Vector 4 specified to intialize the entire matrix

		//Matrix<4, 4, _Type>::Matrix(std::initializer_list<_Type> initList);

		Matrix<4, 4, _Type>& ToIdentity(void) requires (std::is_arithmetic_v<_Type>);		//Change the matrice in an identity matrix

		Matrix<4, 4, _Type>& Empty(void);													//Fill the matrix with 0

		Matrix<4, 4, _Type> GetTranspose(void) const;										//Return the transpose matrix (inverse rows and columns)

		Matrix<4, 4, _Type>& ToTranspose(void);												//Change the matrix into its transpose matrix

		_Type GetDeterminant(void) const;													//Get the determinant of the matrix

		Matrix<3, 3, _Type> GetMinor(size_t row, size_t column) const;						//Get the minor matrix with specified column and rows

		Matrix<4, 4, _Type> GetMinorsDeterminant(void) const;								//Get the determinant of a minor matrix

		Matrix<4, 4, _Type> GetCofactors(void) const;										//

		Matrix<4, 4, _Type> GetInverse(void) const;											//Get the inverse matrix (AB = BA)


		static Matrix<4, 4, _Type> Zero(void);																								//Return a matrix full of 0
		
		static Matrix<4, 4, _Type> Identity(void) requires (std::is_arithmetic_v<_Type>);													//Return an identity matrix (1 in diagonal)

		static Matrix<4, 4, _Type> Translate(const LibMath::Vector<3, _Type>&) requires (std::is_arithmetic_v<_Type>);						//Return a translate matrix with a specified vector 3 (for axis)

		static Matrix<4, 4, _Type> Rotate(const LibMath::Vector<3, _Type>&) requires (std::is_arithmetic_v<_Type>);							//Return a Rotate matrix with a specified vector 3 (for axis)

		static Matrix<4, 4, _Type> Scale(const LibMath::Vector<3, _Type>&) requires (std::is_arithmetic_v<_Type>);							//Return a scale matrix with a specified vector 3 (for axis)

		static Matrix<4, 4, _Type> Perspective(_Type fov, _Type aspect, _Type near, _Type far) requires (std::is_arithmetic_v<_Type>);		//Return a perspective matrix with a specified fov, near and far

		static Matrix<4, 4, _Type> LookAt(const LibMath::Vector3&, const LibMath::Vector3&, const LibMath::Vector3&);						//Return a lookAt matrix useful for Camera

		static Matrix<4, 4, _Type> Ortho(_Type left, _Type right, _Type bottom, _Type top);													

		static Matrix<4, 4, _Type> Ortho(_Type left, _Type right, _Type bottom, _Type top, _Type near, _Type far);

		Matrix<4, 4, _Type>& operator=(const Matrix<4, 4, _Type>&) = default;		//Operator equal with any other 4 by 4 matrix

		bool operator==(const Matrix<4, 4, _Type>&) const = default;				//Operator == with any other 4 by 4 matrix

		Matrix<4, 4, _Type>& operator=(Matrix<4, 4, _Type>&&) = default;			//Move operator equal fir any ither 4 by 4 matrix


		_ColumnType& operator[](size_t index) noexcept { return this->m_matrix[index]; }					//operator [] to get a specified number in the matrix

		const _ColumnType& operator[](size_t index) const noexcept { return this->m_matrix[index]; }		//const operator [] to get a specified number in the matrix


		template <size_t _C>
		Matrix<4, _C, _Type> operator*(const Matrix<4, _C, _Type>& rhs) const;		//Operator * with any other matrix that has 4 rows

		Matrix<4, 4, _Type>& operator*=(const Matrix<4, 4, _Type>& rhs);			//Operator *= with any other 4 by 4 matrix

		Matrix<4, 4, _Type> operator*(_Type rhs) const;								//operator * with a constant value

		Matrix<4, 4, _Type>& operator*=(_Type rhs);									//Operator *= with a constant value

		Matrix<4, 4, _Type> operator+(const Matrix<4, 4, _Type>& rhs) const;		//Operator + with any other 4 by 4 matrix

		Matrix<4, 4, _Type>& operator+=(const Matrix<4, 4, _Type>& rhs);			//Operator += with any ther 4 by 4 matrix

		Matrix<4, 4, _Type> operator-(const Matrix<4, 4, _Type>& rhs) const;		//Operator - with any other 4 by 4 matrix
			
		Matrix<4, 4, _Type>& operator-=(const Matrix<4, 4, _Type>& rhs);			//Operator -= with any other 4 by 4 matrix
				
	private:
		_ColumnType m_matrix[4];		//Array of 4 vector 4 to create the matrix
	};

	template <class _Type>
	Vector<4, _Type> operator*(const Vector<4, _Type>&, const Matrix<4, 4, _Type>&);		//Operator * with a vector 4 

	template <class _Type = float>
	std::ostream& operator<<(std::ostream& os, const Matrix<4, 4, _Type>& matrix);			//Operator << to print a matrix in the console

	using Mat4 = typename Matrix<4, 4, float>;		//Define the name of the matrix
}

#include <LibMath/Matrix/Mat4x4.hpp>