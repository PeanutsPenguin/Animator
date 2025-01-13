#include <iostream>

#include "LibMath/Trigonometry.h"
#include "LibMath/Arithmetic.h"

namespace LibMath
{
	float const g_pi = 3.141592653589793f;
	float const g_2pi =	6.283185307179586f;
	float const g_halfpi = 1.570796326794896f;

	float sin(LibMath::Radian angle)
	{
		return -LibMath::cos(Radian(angle.raw() + g_halfpi));
	}

	float cos(LibMath::Radian angle)
	{
		/* Taylor Series */
		float wrappedAngle = angle.radian();
		float sign = 1.f;

		if (wrappedAngle >= g_halfpi)
		{
			wrappedAngle -= 2 * (wrappedAngle - g_halfpi);
			sign = -1.f;
		}
		else if (wrappedAngle <= -g_halfpi)
		{
			wrappedAngle += -2 * (wrappedAngle + g_halfpi);
			sign = -1.f;
		}

		return sign * (1 - (LibMath::power(wrappedAngle, 2) * 0.5f) + 
				   (LibMath::power(wrappedAngle, 4) * 0.04166666666f) - 
				   (LibMath::power(wrappedAngle, 6) * 0.00138888888f) +
				   (LibMath::power(wrappedAngle, 8) * 0.00002480158f) -
				   (LibMath::power(wrappedAngle, 10) / 3628800));
	}

	float tan(LibMath::Radian angle)
	{
		float cosine = LibMath::cos(angle);

		if (cosine != 0.f)
			return LibMath::sin(angle) / cosine;
		else
		{
			std::cout << "Tangent of " << angle.raw() << " is undefined." << std::endl;
			return 0.f;
		}
	}
	Radian asin(float value)
	{
		return atan(value / squareRoot(1 - value * value));
	}

	Radian acos(float value)
	{
		return Radian(g_halfpi - atan(value / squareRoot(1 - value * value)).raw());
	}

	Radian atan(float value)
	{
		/* Horner's method */
		float accumulator, valuePower, valueSquared, offset;

		offset = 0.f;

		if (value < -1.f)
		{
			offset = -g_halfpi;
			value = -1.f / value;
		}
		else if (value > 1.f)
		{
			offset = g_halfpi;
			value = -1.f / value;
		}
		valueSquared = value * value;
		accumulator = 1.0;
		valuePower = valueSquared;
		accumulator += 0.33288950512027f * valuePower;
		valuePower *= valueSquared;
		accumulator += -0.08467922817644f * valuePower;
		valuePower *= valueSquared;
		accumulator += 0.03252232640125f * valuePower;
		valuePower *= valueSquared;
		accumulator += -0.00749305860992f * valuePower;

		return Radian(offset + value / accumulator);
	}

	Radian atan2(float y, float x)
	{
		Radian arctangent = atan(y / x);

		if (x > 0)
			return arctangent;
		else if (x < 0 && y >= 0)
			return Radian(arctangent.raw() + g_pi);
		else if (x < 0 && y < 0)
			return Radian(arctangent.raw() - g_pi);
		else if (x == 0 && y > 0)
			return Radian(g_halfpi);
		else if (x == 0 && y < 0)
			return Radian(-g_halfpi);
		else
		{
			std::cout << "Atan2 with y = " << y << " and x = " << x << " is undefined." << std::endl;
			return Radian(0.f);
		}
	}
}