#pragma once

#include <LibMath/Matrix/Mat3x3.h>
#include <LibMath/Matrix/Mat4x4.h>

namespace LibMath
{
	template<class _Type>
	Matrix<4, 4, _Type>::Matrix(_Type v)
	{
		for (size_t index = 0; index < 4; ++index)
			for (size_t jindex = 0; jindex < 4; ++jindex)
				if (index == jindex) (*this)[index][jindex] = v;
				else (*this)[index][jindex] = _Type(0);
	}

	template<class _Type>
	Matrix<4, 4, _Type>::Matrix(const _RowType& a, const _RowType& b, const _RowType& c, const _RowType& d)
	{
		(*this)[0] = a;
		(*this)[1] = b;
		(*this)[2] = c;
		(*this)[3] = d;
	}

	template<class _Type>
	Matrix<4, 4, _Type> Matrix<4, 4, _Type>::Zero(void)
	{
		Matrix<4, 4, _Type> matrix;

		for (size_t index = 0; index < 4; ++index)
			for (size_t jindex = 0; jindex < 4; ++jindex)
				matrix[index][jindex] = _Type();

		return matrix;
	}

	//template<class _Type>
	//Matrix<4, 4, _Type>::Matrix(std::initializer_list<_Type> initList)
	//{
	//	if (initList.size() != 4 * 4) {
	//		throw std::invalid_argument("Invalid initializer list dimensions");
	//	}

	//	size_t index = 0;
	//	for (auto& element : initList)
	//	{
	//		for (int jindex = 0; jindex < 4; ++jindex)
	//			this->m_matrix[index][jindex] = std::move(element);

	//		++index;
	//	}
	//}

	template<class _Type>
	Matrix<4, 4, _Type> Matrix<4, 4, _Type>::Identity(void) requires (std::is_arithmetic_v<_Type>)
	{
		Matrix<4, 4, _Type> matrix;

		for (size_t index = 0; index < 4; ++index)
			for (size_t jindex = 0; jindex < 4; ++jindex)
				matrix[index][jindex] = std::move((index == jindex) ? _Type(1) : _Type());

		return matrix;
	}

	template<class _Type>
	Matrix<4, 4, _Type> Matrix<4, 4, _Type>::Translate(const LibMath::Vector<3, _Type>& other) requires (std::is_arithmetic_v<_Type>)
	{
		Matrix<4, 4, _Type> matrix = Matrix<4, 4, _Type>::Identity();
		matrix[3][0] = other[0];
		matrix[3][1] = other[1];
		matrix[3][2] = other[2];

		return matrix;
	}

	template<class _Type>
	Matrix<4, 4, _Type> Matrix<4, 4, _Type>::Rotate(const LibMath::Vector<3, _Type>& other) requires (std::is_arithmetic_v<_Type>)
	{
		Matrix<4, 4, _Type> rotate = Matrix<4, 4, _Type>::Identity();
		Matrix<4, 4, _Type> matrix = Matrix<4, 4, _Type>::Identity();

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

		matrix.ToIdentity();

		matrix[0][0] = std::cosf(other[2]);
		matrix[1][1] = std::cosf(other[2]);

		matrix[0][1] = std::sinf(other[2]);
		matrix[1][0] = -std::sinf(other[2]);

		rotate *= matrix;
		return rotate;
	}

	template<class _Type>
	Matrix<4, 4, _Type> Matrix<4, 4, _Type>::Scale(const LibMath::Vector<3, _Type>& other) requires (std::is_arithmetic_v<_Type>)
	{
		Matrix<4, 4, _Type> matrix = Matrix<4, 4, _Type>::Identity();
		matrix[0][0] = other[0];
		matrix[1][1] = other[1];
		matrix[2][2] = other[2];

		return matrix;
	}

	template<class _Type>
	Matrix<4, 4, _Type> Matrix<4, 4, _Type>::Perspective(_Type fov, _Type aspect, _Type near, _Type far) requires (std::is_arithmetic_v<_Type>)
	{
		Matrix<4, 4, _Type> matrix = Matrix<4, 4, _Type>::Zero();

		const _Type S = std::tan(fov / static_cast<_Type>(2));

		matrix[0][0] = static_cast<_Type>(1) / (aspect * S);
		matrix[1][1] = static_cast<_Type>(1) / (S);
		matrix[2][2] = - (far + near) / (far - near);
		matrix[2][3] = - static_cast<_Type>(1);
		matrix[3][2] = - (static_cast<_Type>(2) * far * near) / (far - near);

		return matrix;
	}

	template<class _Type>
	Matrix<4, 4, _Type> Matrix<4, 4, _Type>::LookAt(const LibMath::Vector3& eye, const LibMath::Vector3& center, const LibMath::Vector3& up)
	{
		LibMath::Mat4 mat = LibMath::Mat4::Identity();

		LibMath::Vector3 f = LibMath::Vector3::normalize(center - eye);
		LibMath::Vector3 s = LibMath::Vector3::normalize(LibMath::Vector3::cross(up, f));
		LibMath::Vector3 u = LibMath::Vector3::cross(f, s);

		mat[0][0] = s.x;
		mat[1][0] = s.y;
		mat[2][0] = s.z;

		mat[0][1] = u.x;
		mat[1][1] = u.y;
		mat[2][1] = u.z;

		mat[0][2] = f.x;
		mat[1][2] = f.y;
		mat[2][2] = f.z;

		mat[3][0] = -LibMath::Vector3::dot(s, eye);
		mat[3][1] = -LibMath::Vector3::dot(u, eye);
		mat[3][2] = -LibMath::Vector3::dot(f, eye);

		return mat;
	}

	template <class T> 
	Matrix<4, 4, T> Matrix<4, 4, T>::Ortho(T left, T right, T bottom, T top) 
	{
		Matrix<4, 4, T> mat(static_cast<T>(1));

		mat[0][0] = static_cast<T>(2) / (right - left);
		mat[1][1] = static_cast<T>(2) / (top - bottom);
		mat[2][2] = -static_cast<T>(1);
		mat[3][0] = -(right + left) / (right - left);
		mat[3][1] = -(top + bottom) / (top - bottom);

		return mat;
	}

	template <class T>
		Matrix<4, 4, T> Matrix<4, 4, T>::Ortho(T left, T right, T bottom, T top, T near, T far) {
		Matrix<4, 4, T> mat(static_cast<T>(1));

		mat[0][0] = static_cast<T>(2) / (right - left);
		mat[1][1] = static_cast<T>(2) / (top - bottom);
		mat[2][2] = -static_cast<T>(2) / (far - near);
		mat[3][0] = -(right + left) / (right - left);
		mat[3][1] = -(top + bottom) / (top - bottom);
		mat[3][2] = -(far + near) / (far - near);

		return mat;
	}
	template<class _Type>
	Matrix<4, 4, _Type>& Matrix<4, 4, _Type>::ToIdentity(void)
		requires (std::is_arithmetic_v<_Type>)
	{
		for (size_t index = 0; index < 4; ++index)
			for (size_t jindex = 0; jindex < 4; ++jindex)
				(*this)[index][jindex] = std::move((index == jindex) ? _Type(1) : _Type());

		return *this;
	}

	template<class _Type>
	Matrix<4, 4, _Type>& Matrix<4, 4, _Type>::Empty(void)
	{
		for (size_t index = 0; index < 4; ++index)
			for (size_t jindex = 0; jindex < 4; ++jindex)
				(*this)[index][jindex] = std::move(_Type());

		return *this;
	}

	template<class _Type>
	Matrix<4, 4, _Type> Matrix<4, 4, _Type>::GetTranspose(void) const
	{
		Matrix<4, 4, _Type> matrix;

		for (size_t index = 0; index < 4; ++index)
			for (size_t jindex = 0; jindex < 4; ++jindex)
				matrix[jindex][index] = (*this)[index][jindex];

		return matrix;
	}

	template<class _Type>
	Matrix<4, 4, _Type>& Matrix<4, 4, _Type>::ToTranspose(void)
	{
		*this = std::move(this->GetTranspose());
		return *this;
	}

	template<class _Type>
	_Type Matrix<4, 4, _Type>::GetDeterminant(void) const
	{
		_Type determinant = _Type();

		for (size_t index = 0; index < 4; ++index)
		{
			Matrix<3, 3, _Type> matrix = std::move(this->GetMinor(index, 0));
			determinant += ((index) % 2 > 0 ? -1 : 1) * (*this)[index][0] * matrix.GetDeterminant();
		}

		return determinant;
	}

	template<class _Type>
	Matrix<3, 3, _Type> Matrix<4, 4, _Type>::GetMinor(size_t row, size_t column) const
	{
		Matrix<3, 3, _Type> matrix;

		size_t zindex = 0;
		for (size_t index = 0; index < 4; ++index)
		{
			size_t kindex = 0;
			for (size_t jindex = 0; jindex < 4; ++jindex)
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
	Matrix<4, 4, _Type> Matrix<4, 4, _Type>::GetMinorsDeterminant(void) const
	{
		Matrix<4, 4, _Type> matrix;

		for (size_t index = 0; index < 4; ++index)
		{
			for (size_t jindex = 0; jindex < 4; ++jindex)
			{
				matrix[index][jindex] = this->GetMinor(index, jindex).GetDeterminant();
			}
		}

		return matrix;
	}

	template<class _Type>
	Matrix<4, 4, _Type> Matrix<4, 4, _Type>::GetCofactors(void) const
	{
		Matrix<4, 4, _Type> matrix = std::move(this->GetMinorsDeterminant());

		for (size_t index = 0; index < 4; ++index)
		{
			for (size_t jindex = 0; jindex < 4; ++jindex)
			{
				matrix[index][jindex] *= ((index + jindex) % 2 > 0 ? -1 : 1);
			}
		}

		return matrix;
	}

	template<class _Type>
	Matrix<4, 4, _Type> Matrix<4, 4, _Type>::GetInverse(void) const
	{
		Matrix<4, 4, _Type> matrix = this->GetCofactors().ToTranspose();
		matrix *= (1 / this->GetDeterminant());

		return matrix;
	}

	template<class _Type>
	Matrix<4, 4, _Type> Matrix<4, 4, _Type>::operator*(_Type rhs) const
	{
		Matrix<4, 4, _Type> matrix;

		for (size_t index = 0; index < 4; ++index)
		{
			for (size_t jindex = 0; jindex < 4; ++jindex)
			{
				matrix[index][jindex] = (*this)[index][jindex] * rhs;
			}
		}

		return matrix;
	}

	template<class _Type>
	Matrix<4, 4, _Type> Matrix<4, 4, _Type>::operator+(const Matrix<4, 4, _Type>& rhs) const
	{
		Matrix<4, 4, _Type> matrix;

		for (size_t index = 0; index < 4; ++index)
		{
			for (size_t jindex = 0; jindex < 4; ++jindex)
			{
				matrix[index][jindex] = (*this)[index][jindex] + rhs[index][jindex];
			}
		}

		return matrix;
	}

	template<class _Type>
	Matrix<4, 4, _Type>& Matrix<4, 4, _Type>::operator+=(const Matrix<4, 4, _Type>& rhs)
	{
		*this = std::move(this->operator+(rhs));
		return *this;
	}

	template<class _Type>
	Matrix<4, 4, _Type> Matrix<4, 4, _Type>::operator-(const Matrix<4, 4, _Type>& rhs) const
	{
		Matrix<4, 4, _Type> matrix;

		for (size_t index = 0; index < 4; ++index)
		{
			for (size_t jindex = 0; jindex < 4; ++jindex)
			{
				matrix[index][jindex] = (*this)[index][jindex] - rhs[index][jindex];
			}
		}

		return matrix;
	}

	template<class _Type>
	Matrix<4, 4, _Type>& Matrix<4, 4, _Type>::operator-=(const Matrix<4, 4, _Type>& rhs)
	{
		*this = std::move(this->operator-(rhs));
		return *this;
	}

	template<class _Type>
	template<size_t _C>
	Matrix<4, _C, _Type> Matrix<4, 4, _Type>::operator*(const Matrix<4, _C, _Type>& rhs) const
	{
		Matrix<4, _C, _Type> matrix;

		for (size_t index = 0; index < 4; ++index)
		{
			for (size_t jindex = 0; jindex < _C; ++jindex)
			{
				matrix[jindex][index] = std::move(_Type());
				for (size_t kindex = 0; kindex < 4; ++kindex)
					matrix[jindex][index] += (*this)[kindex][index] * rhs[jindex][kindex];
			}
		}
		return matrix;
	}

	template<class _Type>
	Matrix<4, 4, _Type>& Matrix<4, 4, _Type>::operator*=(const Matrix<4, 4, _Type>& rhs)
	{
		*this = std::move(this->operator*(rhs));
		return *this;
	}

	template<class _Type>
	Matrix<4, 4, _Type>& Matrix<4, 4, _Type>::operator*=(_Type rhs)
	{
		*this = std::move(this->operator*(rhs));
		return *this;
	}

	template<class _Type>
	Vector<4, _Type> operator*(const Vector<4, _Type>& vec, const Matrix<4, 4, _Type>& matrix)
	{
		Vector<4, _Type> vector = LibMath::Vector4::Zero();

		for (size_t index = 0; index < 4; ++index)
		{
			vector[index] = static_cast<_Type>(0);
			for (size_t kindex = 0; kindex < 4; ++kindex)
				vector[index] += matrix[kindex][index] * vec[kindex];
		}

		return vector;
	}

	template<class _Type>
	std::ostream& operator<<(std::ostream& os, const Matrix<4, 4, _Type>& matrix)
	{
		for (size_t index = 0; index < 4; ++index)
		{
			for (size_t jindex = 0; jindex < 4; ++jindex)
				os << matrix[index][jindex] << '\t';

			os << '\n';
		}

		return os;
	}
}