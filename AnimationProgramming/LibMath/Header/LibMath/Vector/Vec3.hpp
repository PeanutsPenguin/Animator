#pragma once

#include <LibMath/Trigonometry.h>
#include <LibMath/Vector/Vec3.h>

#include "LibMath/Matrix.h"

#include "LibMath/Arithmetic.h"

#include <float.h>


namespace LibMath
{
	template<typename _Type>
	inline LibMath::Vector<3, _Type>::Vector(void) : LibMath::Vector<3, _Type>(_Type(0)) {}

	template<typename _Type>
	inline LibMath::Vector<3, _Type>::Vector(_Type value) : LibMath::Vector<3, _Type>(value, value, value) {}

	template<typename _Type>
	inline LibMath::Vector<3, _Type>::Vector(_Type x, _Type y, _Type z) : x(x), y(y), z(z) {}

	template<typename _Type>
	inline Vector<3, _Type> LibMath::Vector<3, _Type>::zero(void)
	{
		return Vector<3, _Type>();
	}

	template<typename _Type>
	inline Vector<3, _Type> LibMath::Vector<3, _Type>::one(void)
	{
		return Vector<3, _Type>(_Type(1));
	}

	template<typename _Type>
	inline Vector<3, _Type> LibMath::Vector<3, _Type>::up(void)
	{
		return Vector<3, _Type>(_Type(0), _Type(1), _Type(0));
	}

	template<typename _Type>
	inline Vector<3, _Type> LibMath::Vector<3, _Type>::down(void)
	{
		return Vector<3, _Type>(_Type(0), _Type(-1), _Type(0));
	}

	template<typename _Type>
	inline Vector<3, _Type> LibMath::Vector<3, _Type>::left(void)
	{
		return Vector<3, _Type>(_Type(-1), _Type(0), _Type(0));
	}

	template<typename _Type>
	inline Vector<3, _Type> LibMath::Vector<3, _Type>::right(void)
	{
		return Vector<3, _Type>(_Type(1), _Type(0), _Type(0));
	}

	template<typename _Type>
	inline Vector<3, _Type> LibMath::Vector<3, _Type>::front(void)
	{
		return Vector<3, _Type>(_Type(0), _Type(0), _Type(1));
	}

	template<typename _Type>
	inline Vector<3, _Type> LibMath::Vector<3, _Type>::back(void)
	{
		return Vector<3, _Type>(_Type(0), _Type(0), _Type(-1));
	}

	template<typename _Type>
	inline LibMath::Radian LibMath::Vector<3, _Type>::Angle(const Vector<3, _Type>& a, const Vector<3, _Type>& b)
	{
		LibMath::Vector3 normA = LibMath::Vector3::normalize(a);
		LibMath::Vector3 normB = LibMath::Vector3::normalize(b);

		float value = LibMath::Vector3::dot(normA, normB);

		if (std::isnan(value))
			std::cout << "VALUE IN ACOS WRONG\n";

		return LibMath::acos(value);
	}

	template<typename _Type>
	inline LibMath::Radian LibMath::Vector<3, _Type>::Angle(const Vector<3, _Type>& a, const Vector<3, _Type>& b, const Vector<3, _Type>& c)
	{
		LibMath::Vector3 vec1(a.x - b.x, a.y - b.y, a.z - b.z);
		LibMath::Vector3 vec2(c.x - b.x, c.y - b.y, c.z - b.z);

		return LibMath::Vector3::Angle(vec1, vec2);
	}

	template<typename _Type>
	inline Radian Vector<3, _Type>::angleFrom(const Vector<3, _Type>& other, bool range) const
	{
		float dot			 = LibMath::Vector3::dot(*this, other);
		float magnitudeDenom = (this->Magnitude() * other.Magnitude());
		float limitedAngle	 = std::acosf(dot / magnitudeDenom);

		if (!range)
		{
			return Radian(limitedAngle);
		}

		float cross = LibMath::Vector3::cross(*this, other).Magnitude();

		float radian;
		if (std::asinf(cross / magnitudeDenom) < 0)
		{
			radian = g_2pi - limitedAngle;
			return Radian(radian);
		}

		return Radian(limitedAngle);
	}

	template<typename _Type>
	inline _Type LibMath::Vector<3, _Type>::distance(const Vector<3, _Type>& a, const Vector<3, _Type>& b)
	{
		return b.operator-(a).Magnitude();
	}

	template<typename _Type>
	inline _Type LibMath::Vector<3, _Type>::distance2(const Vector<3, _Type>& a, const Vector<3, _Type>& b)
	{
		return LibMath::Vector<2, _Type>(b).operator-(LibMath::Vector<2, _Type>(a)).Magnitude();
	}

	template<typename _Type>
	inline _Type LibMath::Vector<3, _Type>::distanceSquared(const Vector<3, _Type>& a, const Vector<3, _Type>& b)
	{
		return b.operator-(a).MagnitudeSquared();
	}

	template<typename _Type>
	inline _Type LibMath::Vector<3, _Type>::distance2Squared(const Vector<3, _Type>& a, const Vector<3, _Type>& b)
	{
		return LibMath::Vector<2, _Type>(b).operator-(LibMath::Vector<2, _Type>(a)).MagnitudeSquared();
	}

	template<typename _Type>
	inline int LibMath::Vector<3, _Type>::compare(const Vector<3, _Type>& a, const Vector<3, _Type>& b)
	{
		_Type m_a = a.Magnitude(), m_b = b.Magnitude();
		return m_a < m_b ? 1 : m_a > m_b ? -1 : 0;
	}

	template<typename _Type>
	inline bool LibMath::Vector<3, _Type>::IsUnit(const Vector<3, _Type>& vec)
	{
		return FLOAT_EQ(vec.Magnitude(), _Type(1));
	}

	template<typename _Type>
	inline Vector<3, _Type> LibMath::Vector<3, _Type>::normalize(const Vector<3, _Type>& vec)
	{
		return vec.operator/(vec.Magnitude());
	}

	template<typename _Type>
	inline Vector<3, _Type> LibMath::Vector<3, _Type>::Project(const Vector<3, _Type>& a, const Vector<3, _Type>& b)
	{
		return b * (LibMath::Vector3::dot(a, b) / LibMath::Vector3::dot(b, b));
	}
	
	template<typename _Type>
	inline Vector<3, _Type> LibMath::Vector<3, _Type>::Reflect(const Vector<3, _Type>& a, const Vector<3, _Type>& b)
	{
		LibMath::Vector3 N = LibMath::Vector3::normalize(b);
		return a - N * LibMath::Vector3::dot(N, a) * static_cast<_Type>(2);
	}

	template<typename _Type>
	inline _Type LibMath::Vector<3, _Type>::dot(const Vector<3, _Type>& a, const Vector<3, _Type>& b)
	{
		return a.x * b.x + a.y * b.y + a.z * b.z;
	}

	template<typename _Type>
	inline LibMath::Vector<3, _Type> LibMath::Vector<3, _Type>::cross(const Vector<3, _Type>& a, const Vector<3, _Type>& b)
	{
		return LibMath::Vector3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
	}

	template<typename _Type>
	inline bool LibMath::Vector<3, _Type>::isLongerThan(const Vector<3, _Type>& vec)
	{
		return this->MagnitudeSquared() > vec.MagnitudeSquared();
	}

	template<typename _Type>
	inline bool Vector<3, _Type>::isShorterThan(const Vector<3, _Type>& vec)
	{
		return this->MagnitudeSquared() < vec.MagnitudeSquared();
	}

	template<typename _Type>
	inline bool Vector<3, _Type>::compareSign(const Vector<3, _Type>& vec)
	{
		if (this->x + vec.x >= this->x &&
			this->y + vec.y >= this->y &&
			this->z + vec.z >= this->z)
			return true;

		return false;
	}

	template<typename _Type>
	inline void Vector<3, _Type>::translate(const Vector<3, _Type>& vec)
	{
		*this += vec;
	}

	template<typename _Type>
	inline void Vector<3, _Type>::scale(const Vector<3, _Type>& vec)
	{
		*this *= vec;
	}

	template<typename _Type>
	inline void Vector<3, _Type>::rotate(const LibMath::Radian& xRot, const LibMath::Radian& yRot, const LibMath::Radian& zRot)
	{
		float cosZ = std::cosf(zRot.raw());
		float sinZ = std::sinf(zRot.raw());

		float cosX = std::cosf(xRot.raw());
		float sinX = std::sinf(xRot.raw());

		float cosY = std::cosf(yRot.raw());
		float sinY = std::sinf(yRot.raw());

		float tempX = this->x * (cosZ * cosY + sinZ * sinX * sinY)
			+ this->y * (-cosZ * sinY + sinZ * sinX * cosY)
			+ this->z * (sinZ * cosX);

		float tempY = this->x * (sinY * cosX)
			+ this->y * (cosY * cosX)
			+ this->z * -sinX;

		float tempZ = this->x * (-sinZ * cosY + cosZ * sinX * sinY)
			+ this->y * (sinZ * sinY + cosZ * sinX * cosY)
			+ this->z * (cosZ * cosX);

		this->x = tempX, this->y = tempY, this->z = tempZ;;
	}

	template<typename _Type>
	inline void Vector<3, _Type>::rotate(const LibMath::Radian& angle, const LibMath::Vector<3, _Type>& other)
	{
		float cosR = std::cosf(angle.raw());
		float sinR = std::sinf(angle.raw());

		LibMath::Vector3 unitOther;

		if (!LibMath::Vector3::IsUnit(other))
			unitOther = LibMath::Vector3::normalize(other);
		else
			unitOther = other;

		LibMath::Vector3 temp = unitOther * (1 - cosR);

		float tempX = this->x * (cosR + temp.x * unitOther.x)
			+ this->y * (temp.y * unitOther.x - sinR * unitOther.z)
			+ this->z * (temp.z * unitOther.x + sinR * unitOther.y);
		
		float tempY = this->x * (temp.x * unitOther.y + sinR * unitOther.z)
			+ this->y * (cosR + temp.y * unitOther.y)
			+ this->z * (temp.z * unitOther.y - sinR * unitOther.x);

		float tempZ = this->x * (temp.x * unitOther.z - sinR * unitOther.y)
			+ this->y * (temp.y * unitOther.z + sinR * unitOther.x)
			+ this->z * (cosR + temp.z * unitOther.z);

		this->x = tempX, this->y = tempY, this->z = tempZ;
	}

	template<typename _Type>
	inline LibMath::Vector<3, _Type>::operator Vector<4, _Type>() const
	{
		return Vector<4, _Type>(this->x, this->y, this->z, static_cast<_Type>(1));
	}

	template<typename _Type>
	inline LibMath::Vector<3, _Type>::operator Vector<2, _Type>() const
	{
		return Vector<2, _Type>(this->x, this->y);
	}

	template<typename _Type>
	inline LibMath::Vector<3, _Type>::operator Vector<1, _Type>() const
	{
		return Vector<1, _Type>(this->x);
	}

	template<typename _Type>
	inline _Type& LibMath::Vector<3, _Type>::operator[](size_t index)
	{
		switch (index)
		{
		default:
		case 0:
			return this->x;
		case 1:
			return this->y;
		case 2:
			return this->z;
		}
	}

	template<typename _Type>
	inline const _Type& LibMath::Vector<3, _Type>::operator[](size_t index) const
	{
		switch (index)
		{
		default:
		case 0:
			return this->x;
		case 1:
			return this->y;
		case 2:
			return this->z;
		}
	}

	template<typename _Type>
	inline bool LibMath::Vector<3, _Type>::operator==(const Vector<3, _Type>& vec) const
	{
		return this->x == vec.x && this->y == vec.y && this->z == vec.z;
	}

	template<typename _Type>
	inline bool LibMath::Vector<3, _Type>::operator!=(const Vector<3, _Type>& vec) const
	{
		return this->x != vec.x || this->y != vec.y || this->z != vec.z;
	}

	template<typename _Type>
	inline Vector<3, _Type>& LibMath::Vector<3, _Type>::operator++(void)
	{
		++this->x;
		++this->y;
		++this->z;
		return *this;
	}

	template<typename _Type>
	inline Vector<3, _Type> LibMath::Vector<3, _Type>::operator++(int) const
	{
		return Vector<3, _Type>(this->x++, this->y++, this->z++);
	}

	template<typename _Type>
	inline Vector<3, _Type>& LibMath::Vector<3, _Type>::operator--(void)
	{
		--this->x;
		--this->y;
		--this->z;
		return *this;
	}

	template<typename _Type>
	inline Vector<3, _Type> LibMath::Vector<3, _Type>::operator--(int) const
	{
		return Vector<3, _Type>(this->x--, this->y--, this->z--);
	}

	template<typename _Type>
	inline Vector<3, _Type> LibMath::Vector<3, _Type>::operator+(const Vector<3, _Type>& vec) const
	{
		return Vector<3, _Type>(this->x + vec.x, this->y + vec.y, this->z + vec.z);
	}

	template<typename _Type>
	inline Vector<3, _Type>& LibMath::Vector<3, _Type>::operator+=(const Vector<3, _Type>& vec)
	{
		this->x += vec.x;
		this->y += vec.y;
		this->z += vec.z;
		return *this;
	}

	template<typename _Type>
	inline Vector<3, _Type> LibMath::Vector<3, _Type>::operator+(_Type scalar) const
	{
		return Vector<3, _Type>(this->x + scalar, this->y + scalar, this->z + scalar);
	}

	template<typename _Type>
	inline Vector<3, _Type>& LibMath::Vector<3, _Type>::operator+=(_Type scalar)
	{
		this->x += scalar;
		this->y += scalar;
		this->z += scalar;
		return *this;
	}

	template<typename _Type>
	inline Vector<3, _Type> LibMath::Vector<3, _Type>::operator-(const Vector<3, _Type>& vec) const
	{
		return Vector<3, _Type>(this->x - vec.x, this->y - vec.y, this->z - vec.z);
	}

	template<typename _Type>
	inline Vector<3, _Type>& LibMath::Vector<3, _Type>::operator-=(const Vector<3, _Type>& vec)
	{
		this->x -= vec.x;
		this->y -= vec.y;
		this->z -= vec.z;
		return *this;
	}

	template<typename _Type>
	inline Vector<3, _Type> LibMath::Vector<3, _Type>::operator-(void) const
	{
		return Vector<3, _Type>(-this->x, -this->y, -this->z);
	}

	template<typename _Type>
	inline Vector<3, _Type> LibMath::Vector<3, _Type>::operator-(_Type scalar) const
	{
		return Vector<3, _Type>(this->x - scalar, this->y - scalar, this->z - scalar);
	}

	template<typename _Type>
	inline Vector<3, _Type>& LibMath::Vector<3, _Type>::operator-=(_Type scalar)
	{
		this->x -= scalar;
		this->y -= scalar;
		this->z -= scalar;
		return *this;
	}

	template<typename _Type>
	inline Vector<3, _Type> LibMath::Vector<3, _Type>::operator*(const Vector<3, _Type>& vec) const
	{
		return Vector<3, _Type>(this->x * vec.x, this->y * vec.y, this->z * vec.z);
	}

	template<typename _Type>
	inline Vector<3, _Type>& LibMath::Vector<3, _Type>::operator*=(const Vector<3, _Type>& vec)
	{
		this->x *= vec.x;
		this->y *= vec.y;
		this->z *= vec.z;
		return *this;
	}

	template<typename _Type>
	inline Vector<3, _Type> LibMath::Vector<3, _Type>::operator*(_Type scalar) const
	{
		return Vector<3, _Type>(this->x * scalar, this->y * scalar, this->z * scalar);
	}

	template<typename _Type>
	inline Vector<3, _Type>& LibMath::Vector<3, _Type>::operator*=(_Type scalar)
	{
		this->x *= scalar;
		this->y *= scalar;
		this->z *= scalar;
		return *this;
	}

	template<typename _Type>
	inline Vector<3, _Type> LibMath::Vector<3, _Type>::operator/(const Vector<3, _Type>& vec) const
	{
		return Vector<3, _Type>(this->x / vec.x, this->y / vec.y, this->z / vec.z);
	}

	template<typename _Type>
	inline Vector<3, _Type>& LibMath::Vector<3, _Type>::operator/=(const Vector<3, _Type>& vec)
	{
		this->x /= vec.x;
		this->y /= vec.y;
		this->z /= vec.z;
		return *this;
	}

	template<typename _Type>
	inline Vector<3, _Type> LibMath::Vector<3, _Type>::operator/(_Type scalar) const
	{
		return Vector<3, _Type>(this->x / scalar, this->y / scalar, this->z/ scalar);
	}

	template<typename _Type>
	inline Vector<3, _Type>& LibMath::Vector<3, _Type>::operator/=(_Type scalar)
	{
		this->x /= scalar;
		this->y /= scalar;
		this->z /= scalar;
		return *this;
	}

	template<typename _Type>
	inline _Type LibMath::Vector<3, _Type>::Magnitude(void) const
	{
		return std::sqrtf(std::powf(static_cast<float>(this->x), 2.f) + std::powf(static_cast<float>(this->y), 2.f) + std::powf(static_cast<float>(this->z), 2.f));
	}

	template<typename _Type>
	inline _Type LibMath::Vector<3, _Type>::MagnitudeSquared(void) const
	{
		return std::powf(static_cast<float>(this->x), 2.f) + std::powf(static_cast<float>(this->y), 2.f) + std::powf(static_cast<float>(this->z), 2.f);
	}

	template<typename _Type>
	std::ostream& operator<<(std::ostream& os, const Vector<3, _Type>& vec)
	{
		os << "{" << vec[0] << "," << vec[1] << "," << vec[2] << "}";
		return os;
	}

	template<typename _Type>
	std::istream& operator>>(std::istream& is, Vector<3, _Type>& vec)
	{
		for (size_t index = 0; index < 3; ++index)
		{
			if (!(is >> vec[index])) 
				vec[index] = _Type(0);
		}
		return is;
	}
}