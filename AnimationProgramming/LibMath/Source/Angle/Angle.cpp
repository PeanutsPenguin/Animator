#include <iostream>

#include "LibMath/Angle/Degree.h"
#include "LibMath/Angle/Radian.h"
#include "LibMath/Trigonometry.h"
#include "LibMath/Arithmetic.h"

///* Degrees */
LibMath::Degree::Degree(float value)
{
	m_value = value;
}

LibMath::Degree::Degree(Degree const& other)
{
	m_value = other.m_value;
}

LibMath::Degree::operator LibMath::Radian() const
{
	return LibMath::Radian(this->radian());
}

LibMath::Degree& LibMath::Degree::operator=(Degree const& rhs)
{
	if (this != &rhs)
	{
		this->m_value = rhs.m_value;
	}

	return *this;
}

LibMath::Degree& LibMath::Degree::operator+=(Degree rhs)
{
	m_value += rhs.m_value;

	return *this;
}

LibMath::Degree& LibMath::Degree::operator-=(Degree rhs)
{
	m_value -= rhs.m_value;

	return *this;
}

LibMath::Degree& LibMath::Degree::operator*=(float factor)
{
	m_value *= factor;

	return *this;
}

LibMath::Degree& LibMath::Degree::operator/=(float factor)
{
	m_value /= factor;

	return *this;
}

void LibMath::Degree::wrap(bool range)
{
	m_value = degree(range);
}

float LibMath::Degree::degree(bool range) const
{
	int int_degree = (int)m_value;
	float decimal_part = m_value - int_degree;
	float result = 0;

	if (int_degree >= 0)
	{
		result = (int_degree % 360) + decimal_part;
	}
	else
	{
		result = 360 + (int_degree % 360) + decimal_part;
	}

	if (range && result >= 180)
	{
		result -= 360;
	}
	
	return result;
}

float LibMath::Degree::radian(bool range) const
{
	float result = degree(range);

	result *= g_pi / 180;
	return result;
}

float LibMath::Degree::raw() const
{
	return m_value;
}

bool LibMath::operator==(Degree lhs, Degree rhs)
{
	if (lhs.degree() == rhs.degree())
	{
		return true;
	}
	return false;
}

bool LibMath::operator==(Degree lhs, Radian const& rhs)
{
	if (lhs.degree() == rhs.degree())
		return true;

	return false;
}

LibMath::Degree LibMath::operator-(Degree rhs)
{
	return Degree(-rhs.raw());
}

LibMath::Degree LibMath::operator+(Degree lhs, Degree rhs)
{
	return Degree(lhs.raw() + rhs.raw());
}

LibMath::Degree LibMath::operator-(Degree lhs, Degree rhs)
{
	return Degree(lhs.raw() - rhs.raw());
}

LibMath::Degree LibMath::operator*(Degree lhs, float rhs)
{
	return Degree(lhs.raw() * rhs);
}

LibMath::Degree LibMath::operator/(Degree lhs, float rhs)
{
	return Degree(lhs.raw() / rhs);
}

LibMath::Degree LibMath::Literal::operator""_deg(long double value)
{
	return LibMath::Degree((float)value);
}

LibMath::Degree LibMath::Literal::operator""_deg(unsigned long long int value)
{
	return LibMath::Degree((float)value);
}

///* Radians */

LibMath::Radian::Radian(float value)
{
	m_value = value;
}

LibMath::Radian::Radian(Radian const& other)
{
	m_value = other.m_value;
}

LibMath::Radian::operator LibMath::Degree() const
{
	return LibMath::Degree(this->degree());
}

LibMath::Radian& LibMath::Radian::operator=(Radian const& rhs)
{
	if (this != &rhs)
	{
		this->m_value = rhs.m_value;
	}

	return *this;
}

LibMath::Radian& LibMath::Radian::operator+=(Radian rhs)
{
	m_value += rhs.m_value;

	return *this;
}

LibMath::Radian& LibMath::Radian::operator-=(Radian rhs)
{
	m_value -= rhs.m_value;

	return *this;
}

LibMath::Radian& LibMath::Radian::operator*=(float factor)
{
	m_value *= factor;

	return *this;
}

LibMath::Radian& LibMath::Radian::operator/=(float factor)
{
	m_value /= factor;

	return *this;
}

void LibMath::Radian::wrap(bool range)
{
	m_value = radian(range);
}

float LibMath::Radian::radian(bool range) const
{
	float result = 0;

	/* Checking if a m_value is already in the wanted range */
	if ((range && m_value >= -1 * g_pi && m_value < g_pi)
	|| (!range && m_value >= 0 && m_value < 2 * g_pi))
		return m_value;
	/* Checking if m_value is strictly inferior to 2Pi so that 
	in the case where m_value = 2Pi, 0 will be returned */
	/* Same for [-Pi, Pi] */

	if (m_value >= 0)
	{
		result = LibMath::fmod(m_value, 2.0f * g_pi);
	}
	else
	{
		result = 2.0f * g_pi + LibMath::fmod(m_value, 2.0f * g_pi);
	}

	if (range && result >= g_pi)
	{
		result -= 2.0f * g_pi;
	}

	return result;
}

float LibMath::Radian::degree(bool range) const
{
	float result = radian(range);

	result *= 180 / g_pi;
	return result;
}

float LibMath::Radian::raw() const
{
	return m_value;
}

bool LibMath::operator==(Radian lhs, Radian rhs)
{
	float angle1 = lhs.radian(false);
	float angle2 = rhs.radian(false);

	return FLOAT_EQ(angle1, angle2);
}

bool LibMath::operator==(Radian lhs, Degree const& rhs)
{
	if (lhs.radian() == rhs.radian())
		return true;

	return false;
}

LibMath::Radian LibMath::operator-(Radian rhs)
{
	return Radian(-rhs.raw());
}

LibMath::Radian LibMath::operator+(Radian lhs, Radian rhs)
{
	return Radian(lhs.raw() + rhs.raw());
}

LibMath::Radian LibMath::operator-(Radian lhs, Radian rhs)
{
	return Radian(lhs.raw() - rhs.raw());
}

LibMath::Radian LibMath::operator*(Radian lhs, float rhs)
{
	return Radian(lhs.raw() * rhs);
}

LibMath::Radian LibMath::operator/(Radian lhs, float rhs)
{
	return Radian(lhs.raw() / rhs);
}

LibMath::Radian LibMath::Literal::operator""_rad(long double value)
{
	return LibMath::Radian((float)value);
}

LibMath::Radian LibMath::Literal::operator""_rad(unsigned long long int value)
{
	return LibMath::Radian((float)value);
}
