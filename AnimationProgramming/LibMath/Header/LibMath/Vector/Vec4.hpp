#pragma once

#include <LibMath/Trigonometry.h>
#include <LibMath/Vector/Vec4.h>

#include <float.h>


namespace LibMath
{
	template<typename _Type>
	inline LibMath::Vector<4, _Type>::Vector(void) : LibMath::Vector<4, _Type>(_Type(0)) {}

	template<typename _Type>
	inline LibMath::Vector<4, _Type>::Vector(_Type value) : LibMath::Vector<4, _Type>(value, value, value, _Type(1)) {}

	template<typename _Type>
	inline LibMath::Vector<4, _Type>::Vector(_Type x, _Type y, _Type z, _Type w) : x(x), y(y), z(z), w(w) {}

	template<typename _Type>
	inline LibMath::Vector<4, _Type>::Vector(const Vector<1, _Type>& a, const Vector<1, _Type>& b, const Vector<1, _Type>& c, const Vector<1, _Type>& d) : x(a.x), y(b.x), z(c.x), w(d.x) { }
	
	template<typename _Type>
	inline LibMath::Vector<4, _Type>::Vector(const Vector<2, _Type>& ab, const Vector<1, _Type>& c, const Vector<1, _Type>& d) : x(ab.x), y(ab.y), z(c.x), w(d.x) { }
	
	template<typename _Type>
	inline LibMath::Vector<4, _Type>::Vector(const Vector<1, _Type>& a, const Vector<2, _Type>& bc, const Vector<1, _Type>& d) : x(a.x), y(bc.x), z(bc.y), w(d.x) { }

	template<typename _Type>
	inline LibMath::Vector<4, _Type>::Vector(const Vector<1, _Type>& a, const Vector<1, _Type>& b, const Vector<2, _Type>& cd) : x(a.x), y(b.x), z(cd.x), w(cd.y) { }

	template<typename _Type>
	inline LibMath::Vector<4, _Type>::Vector(const Vector<2, _Type>& ab, const Vector<2, _Type>& cd) : x(ab.x), y(ab.y), z(cd.x), w(cd.y) { }

	template<typename _Type>
	inline LibMath::Vector<4, _Type>::Vector(const Vector<3, _Type>& abc, const Vector<1, _Type>& d) : x(abc.x), y(abc.y), z(abc.z), w(d.x) { }

	template<typename _Type>
	inline LibMath::Vector<4, _Type>::Vector(const Vector<1, _Type>& a, const Vector<3, _Type>& bcd) : x(a.x), y(bcd.x), z(bcd.y), w(bcd.z) { }

	template<typename _Type>
	inline Vector<4, _Type> LibMath::Vector<4, _Type>::Zero(void)
	{
		return Vector<4, _Type>();
	}

	template<typename _Type>
	inline Vector<4, _Type> LibMath::Vector<4, _Type>::One(void)
	{
		return Vector<4, _Type>(_Type(1));
	}

	template<typename _Type>
	inline Vector<4, _Type> LibMath::Vector<4, _Type>::Up(void)
	{
		return Vector<4, _Type>(_Type(0), _Type(1), _Type(0), _Type(1));
	}

	template<typename _Type>
	inline Vector<4, _Type> LibMath::Vector<4, _Type>::Down(void)
	{
		return Vector<4, _Type>(_Type(0), _Type(-1), _Type(0), _Type(1));
	}

	template<typename _Type>
	inline Vector<4, _Type> LibMath::Vector<4, _Type>::Left(void)
	{
		return Vector<4, _Type>(_Type(-1), _Type(0), _Type(0), _Type(1));
	}

	template<typename _Type>
	inline Vector<4, _Type> LibMath::Vector<4, _Type>::Right(void)
	{
		return Vector<4, _Type>(_Type(1), _Type(0), _Type(0), _Type(1));
	}

	template<typename _Type>
	inline Vector<4, _Type> LibMath::Vector<4, _Type>::Front(void)
	{
		return Vector<4, _Type>(_Type(0), _Type(0), _Type(1), _Type(1));
	}

	template<typename _Type>
	inline Vector<4, _Type> LibMath::Vector<4, _Type>::Back(void)
	{
		return Vector<4, _Type>(_Type(0), _Type(0), _Type(-1), _Type(1));
	}

	template<typename _Type>
	inline LibMath::Radian LibMath::Vector<4, _Type>::Angle(const Vector<4, _Type>&, const Vector<4, _Type>&)
	{
		return LibMath::acos(LibMath::Vector4::Dot(LibMath::Vector4::Normalize(a), LibMath::Vector4::Normalize(b)));
	}

	template<typename _Type>
	inline _Type LibMath::Vector<4, _Type>::Distance(const Vector<4, _Type>& a, const Vector<4, _Type>& b)
	{
		return b.operator-(a).Magnitude();
	}

	template<typename _Type>
	inline _Type LibMath::Vector<4, _Type>::Distance2(const Vector<4, _Type>& a, const Vector<4, _Type>& b)
	{
		return LibMath::Vector<2, _Type>(b).operator-(LibMath::Vector<2, _Type>(a)).Magnitude();
	}

	template<typename _Type>
	inline _Type LibMath::Vector<4, _Type>::DistanceSquared(const Vector<4, _Type>& a, const Vector<4, _Type>& b)
	{
		return b.operator-(a).MagnitudeSquared();
	}

	template<typename _Type>
	inline _Type LibMath::Vector<4, _Type>::Distance2Squared(const Vector<4, _Type>& a, const Vector<4, _Type>& b)
	{
		return LibMath::Vector<2, _Type>(b).operator-(LibMath::Vector<2, _Type>(a)).MagnitudeSquared();
	}

	template<typename _Type>
	inline int LibMath::Vector<4, _Type>::Compare(const Vector<4, _Type>& a, const Vector<4, _Type>& b)
	{
		_Type m_a = a.Magnitude(), m_b = b.Magnitude();
		return m_a < m_b ? 1 : m_a > m_b ? -1 : 0;
	}

	template<typename _Type>
	inline bool LibMath::Vector<4, _Type>::IsUnit(const Vector<4, _Type>& vec)
	{
		return FLOAT_EQ(vec.Magnitude(), _Type(1));
	}

	template<typename _Type>
	inline Vector<4, _Type> LibMath::Vector<4, _Type>::Normalize(const Vector<4, _Type>& vec)
	{
		return vec.operator/(vec.Magnitude());
	}

	template<typename _Type>
	inline Vector<4, _Type> LibMath::Vector<4, _Type>::Project(const Vector<4, _Type>& a, const Vector<4, _Type>& b)
	{
		return b * (LibMath::Vector4::Dot(a, b) / LibMath::Vector4::Dot(b, b));
	}

	template<typename _Type>
	inline Vector<4, _Type> LibMath::Vector<4, _Type>::Reflect(const Vector<4, _Type>& a, const Vector<4, _Type>& b)
	{
		LibMath::Vector4 N = LibMath::Vector4::Normalize(b);
		return a - N * LibMath::Vector4::Dot(N, a) * static_cast<_Type>(2);
	}

	template<typename _Type>
	inline _Type LibMath::Vector<4, _Type>::Dot(const Vector<4, _Type>& a, const Vector<4, _Type>& b)
	{
		return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
	}

	template<typename _Type>
	inline LibMath::Vector<4, _Type>::operator Vector<3, _Type>() const
	{
		return Vector<3, _Type>(this->x, this->y, this->z);
	}

	template<typename _Type>
	inline LibMath::Vector<4, _Type>::operator Vector<2, _Type>() const
	{
		return Vector<2, _Type>(this->x, this->y);
	}

	template<typename _Type>
	inline LibMath::Vector<4, _Type>::operator Vector<1, _Type>() const
	{
		return Vector<1, _Type>(this->x);
	}

	template<typename _Type>
	inline _Type& LibMath::Vector<4, _Type>::operator[](size_t index)
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
		case 3:
			return this->w;
		}
	}

	template<typename _Type>
	inline const _Type& LibMath::Vector<4, _Type>::operator[](size_t index) const
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
		case 3:
			return this->w;
		}
	}

	template<typename _Type>
	inline bool LibMath::Vector<4, _Type>::operator==(const Vector<4, _Type>& vec) const
	{
		return this->x == vec.x && this->y == vec.y && this->z == vec.z && this->w == vec.w;
	}

	template<typename _Type>
	inline bool LibMath::Vector<4, _Type>::operator!=(const Vector<4, _Type>& vec) const
	{
		return this->x != vec.x || this->y != vec.y || this->z != vec.z || this->w != vec.w;
	}

	template<typename _Type>
	inline Vector<4, _Type>& LibMath::Vector<4, _Type>::operator++(void)
	{
		++this->x;
		++this->y;
		++this->z;
		++this->w;
		return *this;
	}

	template<typename _Type>
	inline Vector<4, _Type> LibMath::Vector<4, _Type>::operator++(int) const
	{
		return Vector<4, _Type>(this->x++, this->y++, this->z++, this->w++);
	}

	template<typename _Type>
	inline Vector<4, _Type>& LibMath::Vector<4, _Type>::operator--(void)
	{
		--this->x;
		--this->y;
		--this->z;
		--this->w;
		return *this;
	}

	template<typename _Type>
	inline Vector<4, _Type> LibMath::Vector<4, _Type>::operator--(int) const
	{
		return Vector<4, _Type>(this->x--, this->y--, this->z--, this->w--);
	}

	template<typename _Type>
	inline Vector<4, _Type> LibMath::Vector<4, _Type>::operator+(const Vector<4, _Type>& vec) const
	{
		return Vector<4, _Type>(this->x + vec.x, this->y + vec.y, this->z + vec.z, this->w + vec.w);
	}

	template<typename _Type>
	inline Vector<4, _Type>& LibMath::Vector<4, _Type>::operator+=(const Vector<4, _Type>& vec)
	{
		this->x += vec.x;
		this->y += vec.y;
		this->z += vec.z;
		this->w += vec.w;
		return *this;
	}

	template<typename _Type>
	inline Vector<4, _Type> LibMath::Vector<4, _Type>::operator+(_Type scalar) const
	{
		return Vector<4, _Type>(this->x + scalar, this->y + scalar, this->z + scalar, this->w + scalar);
	}

	template<typename _Type>
	inline Vector<4, _Type>& LibMath::Vector<4, _Type>::operator+=(_Type scalar)
	{
		this->x += scalar;
		this->y += scalar;
		this->z += scalar;
		this->w += scalar;
		return *this;
	}

	template<typename _Type>
	inline Vector<4, _Type> LibMath::Vector<4, _Type>::operator-(const Vector<4, _Type>& vec) const
	{
		return Vector<4, _Type>(this->x - vec.x, this->y - vec.y, this->z - vec.z, this->w - vec.w);
	}

	template<typename _Type>
	inline Vector<4, _Type>& LibMath::Vector<4, _Type>::operator-=(const Vector<4, _Type>& vec)
	{
		this->x -= vec.x;
		this->y -= vec.y;
		this->z -= vec.y;
		this->w -= vec.w;
		return *this;
	}

	template<typename _Type>
	inline Vector<4, _Type> LibMath::Vector<4, _Type>::operator-(void) const
	{
		return Vector<4, _Type>(-this->x, -this->y, -this->z, -this->w);
	}

	template<typename _Type>
	inline Vector<4, _Type> LibMath::Vector<4, _Type>::operator-(_Type scalar) const
	{
		return Vector<4, _Type>(this->x - scalar, this->y - scalar, this->z - scalar, this->w - scalar);
	}

	template<typename _Type>
	inline Vector<4, _Type>& LibMath::Vector<4, _Type>::operator-=(_Type scalar)
	{
		this->x -= scalar;
		this->y -= scalar;
		this->z -= scalar;
		this->w -= scalar;
		return *this;
	}

	template<typename _Type>
	inline Vector<4, _Type> LibMath::Vector<4, _Type>::operator*(const Vector<4, _Type>& vec) const
	{
		return Vector<4, _Type>(this->x * vec.x, this->y * vec.y, this->z * vec.z, this->w * vec.w);
	}

	template<typename _Type>
	inline Vector<4, _Type>& LibMath::Vector<4, _Type>::operator*=(const Vector<4, _Type>& vec)
	{
		this->x *= vec.x;
		this->y *= vec.y;
		this->z *= vec.z;
		this->w *= vec.w;
		return *this;
	}

	template<typename _Type>
	inline Vector<4, _Type> LibMath::Vector<4, _Type>::operator*(_Type scalar) const
	{
		return Vector<4, _Type>(this->x * scalar, this->y * scalar, this->z * scalar, this->w * scalar);
	}

	template<typename _Type>
	inline Vector<4, _Type>& LibMath::Vector<4, _Type>::operator*=(_Type scalar)
	{
		this->x *= scalar;
		this->y *= scalar;
		this->z *= scalar;
		this->w *= scalar;
		return *this;
	}

	template<typename _Type>
	inline Vector<4, _Type> LibMath::Vector<4, _Type>::operator/(const Vector<4, _Type>& vec) const
	{
		return Vector<4, _Type>(this->x / vec.x, this->y / vec.y, this->z / vec.z, this->w / vec.w);
	}

	template<typename _Type>
	inline Vector<4, _Type>& LibMath::Vector<4, _Type>::operator/=(const Vector<4, _Type>& vec)
	{
		this->x /= vec.x;
		this->y /= vec.y;
		this->z /= vec.z;
		this->w /= vec.w;
		return *this;
	}

	template<typename _Type>
	inline Vector<4, _Type> LibMath::Vector<4, _Type>::operator/(_Type scalar) const
	{
		return Vector<4, _Type>(this->x / scalar, this->y / scalar, this->z / scalar, this->w / scalar);
	}

	template<typename _Type>
	inline Vector<4, _Type>& LibMath::Vector<4, _Type>::operator/=(_Type scalar)
	{
		this->x /= scalar;
		this->y /= scalar;
		this->z /= scalar;
		this->w /= scalar;
		return *this;
	}

	template<typename _Type>
	inline _Type LibMath::Vector<4, _Type>::Magnitude(void) const
	{
		return std::sqrtf(std::powf(static_cast<float>(this->x), 2.f) + std::powf(static_cast<float>(this->y), 2.f) + std::powf(static_cast<float>(this->z), 2.f) + std::powf(static_cast<float>(this->w), 2.f));
	}

	template<typename _Type>
	inline _Type LibMath::Vector<4, _Type>::MagnitudeSquared(void) const
	{
		return std::powf(static_cast<float>(this->x), 2.f) + std::powf(static_cast<float>(this->y), 2.f) + std::powf(static_cast<float>(this->z), 2.f) + std::powf(static_cast<float>(this->w), 2.f);
	}

	template<typename _Type>
	std::ostream& operator<<(std::ostream& os, const Vector<4, _Type>& vec)
	{
		os << "v\t";
		for (size_t index = 0; index < 4; ++index)
		{
			os << vec[index] << '\t';
		}
		return os;
	}

	template<typename _Type>
	std::istream& operator>>(std::istream& is, Vector<4, _Type>& vec)
	{
		for (size_t index = 0; index < 4; ++index)
		{
			if (!(is >> vec[index]))
				vec[index] = _Type(0);
		}
		return is;
	}
}