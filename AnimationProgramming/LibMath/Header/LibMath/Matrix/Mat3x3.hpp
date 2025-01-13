#pragma once

#include <LibMath/Matrix/Mat2x2.h>
#include <LibMath/Matrix/Mat3x3.h>

namespace LibMath
{
	template<class _Type>
	Matrix<3, 3, _Type>::Matrix(_Type v)
	{
		for (size_t index = 0; index < 3; ++index)
			for (size_t jindex = 0; jindex < 3; ++jindex)
				if (index == jindex) (*this)[index][jindex] = v;
				else (*this)[index][jindex] = _Type(0);
	}

	template<class _Type>
	Matrix<3, 3, _Type>::Matrix(const _RowType& a, const _RowType& b, const _RowType& c)
	{
		(*this)[0] = a;
		(*this)[1] = b;
		(*this)[2] = c;
	}

	template<class _Type>
	Matrix<3, 3, _Type> Matrix<3, 3, _Type>::Zero(void)
	{
		Matrix<3, 3, _Type> matrix;

		for (size_t index = 0; index < 3; ++index)
			for (size_t jindex = 0; jindex < 3; ++jindex)
				matrix[index][jindex] = _Type();

		return matrix;
	}

	template<class _Type>
	Matrix<3, 3, _Type> Matrix<3, 3, _Type>::Identity(void) requires (std::is_arithmetic_v<_Type>)
	{
		Matrix<3, 3, _Type> matrix;

		for (size_t index = 0; index < 3; ++index)
			for (size_t jindex = 0; jindex < 3; ++jindex)
				matrix[index][jindex] = std::move((index == jindex) ? _Type(1) : _Type());

		return matrix;
	}

	template<class _Type>
	Matrix<3, 3, _Type> Matrix<3, 3, _Type>::Translate(const LibMath::Vector<2, _Type>& other) requires (std::is_arithmetic_v<_Type>)
	{
		Matrix<3, 3, _Type> matrix = Matrix<3, 3, _Type>::Identity();
		matrix[0][2] = other[0];
		matrix[1][2] = other[1];

		return matrix;
	}

	template<class _Type>
	Matrix<3, 3, _Type> Matrix<3, 3, _Type>::Rotate(const LibMath::Vector<2, _Type>& other) requires (std::is_arithmetic_v<_Type>)
	{
		Matrix<3, 3, _Type> rotate = Matrix<3, 3, _Type>::Identity();
		Matrix<3, 3, _Type> matrix = Matrix<3, 3, _Type>::Identity();

		matrix[1][1] = std::cosf(other[0]);
		matrix[2][2] = std::cosf(other[0]);

		matrix[2][1] = std::sinf(other[0]);
		matrix[1][2] = -std::sinf(other[0]);

		rotate *= matrix;

		matrix.ToIdentity();

		matrix[0][0] = std::cosf(other[1]);
		matrix[2][2] = std::cosf(other[1]);

		matrix[0][2] = -std::sinf(other[1]);
		matrix[2][0] = std::sinf(other[1]);

		rotate *= matrix;
		return rotate;
	}

	template<class _Type>
	Matrix<3, 3, _Type> Matrix<3, 3, _Type>::Scale(const LibMath::Vector<2, _Type>& other) requires (std::is_arithmetic_v<_Type>)
	{
		Matrix<3, 3, _Type> matrix = Matrix<3, 3, _Type>::Identity();
		matrix[0][0] = other[0];
		matrix[2][2] = other[1];

		return matrix;
	}

	template<class _Type>
	Matrix<3, 3, _Type>& Matrix<3, 3, _Type>::ToIdentity(void)
		requires (std::is_arithmetic_v<_Type>)
	{
		for (size_t index = 0; index < 3; ++index)
			for (size_t jindex = 0; jindex < 3; ++jindex)
				(*this)[index][jindex] = std::move((index == jindex) ? _Type(1) : _Type());

		return *this;
	}

	template<class _Type>
	Matrix<3, 3, _Type>& Matrix<3, 3, _Type>::Empty(void)
	{
		for (size_t index = 0; index < 3; ++index)
			for (size_t jindex = 0; jindex < 3; ++jindex)
				(*this)[index][jindex] = std::move(_Type());

		return *this;
	}

	template<class _Type>
	Matrix<3, 3, _Type> Matrix<3, 3, _Type>::GetTranspose(void) const
	{
		Matrix<3, 3, _Type> matrix;

		for (size_t index = 0; index < 3; ++index)
			for (size_t jindex = 0; jindex < 3; ++jindex)
				matrix[jindex][index] = (*this)[index][jindex];

		return matrix;
	}

	template<class _Type>
	Matrix<3, 3, _Type>& Matrix<3, 3, _Type>::ToTranspose(void)
	{
		*this = std::move(this->GetTranspose());
		return *this;
	}

	template<class _Type>
	_Type Matrix<3, 3, _Type>::GetDeterminant(void) const
	{
		return (
			+((*this)[0][0] * (*this)[1][1] * (*this)[2][2])
			+ ((*this)[0][1] * (*this)[1][2] * (*this)[2][0])
			+ ((*this)[0][2] * (*this)[1][0] * (*this)[2][1])
			- ((*this)[0][0] * (*this)[1][2] * (*this)[2][1])
			- ((*this)[0][1] * (*this)[1][0] * (*this)[2][2])
			- ((*this)[0][2] * (*this)[1][1] * (*this)[2][0])
		);
	}

	template<class _Type>
	Matrix<2, 2, _Type> Matrix<3, 3, _Type>::GetMinor(size_t row, size_t column) const
	{
		Matrix<2, 2, _Type> matrix;

		size_t zindex = 0;
		for (size_t index = 0; index < 3; ++index)
		{
			size_t kindex = 0;
			for (size_t jindex = 0; jindex < 3; ++jindex)
			{
				if (index == row || jindex == column) continue;

				matrix[zindex][kindex] = (*this)[index][jindex];
				++kindex;
			}

			if (index != row) ++zindex;
		}

		return matrix;
	}

	template<class _Type>
	Matrix<3, 3, _Type> Matrix<3, 3, _Type>::GetMinorsDeterminant(void) const
	{
		Matrix<3, 3, _Type> matrix;

		for (size_t index = 0; index < 3; ++index)
		{
			for (size_t jindex = 0; jindex < 3; ++jindex)
			{
				matrix[index][jindex] = this->GetMinor(index, jindex).GetDeterminant();
			}
		}

		return matrix;
	}

	template<class _Type>
	Matrix<3, 3, _Type> Matrix<3, 3, _Type>::GetCofactors(void) const
	{
		Matrix<3, 3, _Type> matrix = std::move(this->GetMinorsDeterminant());

		for (size_t index = 0; index < 3; ++index)
		{
			for (size_t jindex = 0; jindex < 3; ++jindex)
			{
				matrix[index][jindex] *= ((index + jindex) % 2 > 0 ? -1 : 1);
			}
		}

		return matrix;
	}

	template<class _Type>
	Matrix<3, 3, _Type> Matrix<3, 3, _Type>::GetInverse(void) const
	{
		Matrix<3, 3, _Type> matrix = this->GetCofactors().ToTranspose();
		matrix *= (1 / this->GetDeterminant());

		return matrix;
	}

	template <class T> bool Matrix<3, 3, T>::operator==(const Matrix<3, 3, T>& rhs) const {
		return this->m_matrix[0] == rhs.m_matrix[0] && this->m_matrix[1] == rhs.m_matrix[1] && this->m_matrix[2] == rhs.m_matrix[2];
	}

	template <class T> bool Matrix<3, 3, T>::operator!=(const Matrix<3, 3, T>& rhs) const {
		return this->m_matrix[0] != rhs.m_matrix[0] || this->m_matrix[1] != rhs.m_matrix[1] || this->m_matrix[2] != rhs.m_matrix[2];
	}

	template<class _Type>
	Matrix<3, 3, _Type> Matrix<3, 3, _Type>::operator*(_Type rhs) const
	{
		Matrix<3, 3, _Type> matrix = *this;

		for (size_t index = 0; index < 3; ++index)
			matrix[index] *= rhs;

		return matrix;
	}

	template<class _Type>
	Matrix<3, 3, _Type> Matrix<3, 3, _Type>::operator+(const Matrix<3, 3, _Type>& rhs) const
	{
		Matrix<3, 3, _Type> matrix = *this;

		for (size_t index = 0; index < 3; ++index)
			matrix[index] += rhs[index];

		return matrix;
	}

	template<class _Type>
	Matrix<3, 3, _Type>& Matrix<3, 3, _Type>::operator+=(const Matrix<3, 3, _Type>& rhs)
	{
		*this = std::move(this->operator+(rhs));
		return *this;
	}

	template<class _Type>
	Matrix<3, 3, _Type> Matrix<3, 3, _Type>::operator-(const Matrix<3, 3, _Type>& rhs) const
	{
		Matrix<3, 3, _Type> matrix = *this;

		for (size_t index = 0; index < 3; ++index)
			matrix[index] -= rhs[index];

		return matrix;
	}

	template<class _Type>
	Matrix<3, 3, _Type>& Matrix<3, 3, _Type>::operator-=(const Matrix<3, 3, _Type>& rhs)
	{
		*this = std::move(this->operator-(rhs));
		return *this;
	}

	template<class _Type>
	template<size_t _C>
	Matrix<3, _C, _Type> Matrix<3, 3, _Type>::operator*(const Matrix<3, _C, _Type>& rhs) const
	{
		Matrix<3, _C, _Type> matrix;

		for (size_t index = 0; index < 3; ++index)
		{
			for (size_t jindex = 0; jindex < _C; ++jindex)
			{
				matrix[jindex][index] = std::move(_Type());
				for (size_t kindex = 0; kindex < 3; ++kindex)
					matrix[jindex][index] += (*this)[kindex][index] * rhs[jindex][kindex];
			}
		}
		return matrix;
	}

	template<class _Type>
	Matrix<3, 3, _Type>& Matrix<3, 3, _Type>::operator*=(const Matrix<3, 3, _Type>& rhs)
	{
		*this = std::move(this->operator*(rhs));
		return *this;
	}

	template<class _Type>
	Matrix<3, 3, _Type>& Matrix<3, 3, _Type>::operator*=(_Type rhs)
	{
		*this = std::move(this->operator*(rhs));
		return *this;
	}

	template<class _Type>
	std::ostream& operator<<(std::ostream& os, const Matrix<3, 3, _Type>& matrix)
	{
		for (size_t index = 0; index < 3; ++index)
		{
			for (size_t jindex = 0; jindex < 3; ++jindex)
				os << matrix[index][jindex] << '\t';

			os << '\n';
		}

		return os;
	}
}