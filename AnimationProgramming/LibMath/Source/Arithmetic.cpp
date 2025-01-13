#include "LibMath/Arithmetic.h"

bool LibMath::almostequal(float alpha, float beta)
{
	return FLOAT_EQ(alpha, beta);
}

int LibMath::ceiling(float value)
{
	return (int)(value + 1);
}

float LibMath::clamp(float value, float min, float max)
{
	if (min > max)
	{
		return clamp(value, max, min);
	}

	if (value >= min && value <= max)
		return value;

	return (value < min ? min : max);
}

int LibMath::floor(float value)
{
	return (int)value;
}

float LibMath::power(float base, int exponent)
{
	if (exponent == 0)
		return 1.f;
	else if (base == 0)
		return 0.f;

	float result = base;
	for (int i = 1; i < exponent; i++)
	{
		result *= base;
	}

	return result;
}

float LibMath::squareRoot(float value)
{
	if (value <= 0)
		return 0;       // if negative number throw an exception?

	int exp = 0;
	float mantissa;
	separatefloat(value, mantissa, exp); // extract binary exponent from x
	if (exp & 1) {      // we want exponent to be even
		exp--;
		mantissa *= 2;
	}
	float y = (1 + mantissa) / 2; // first approximation
	float z = 0;
	while (y != z) {    // yes, we CAN compare doubles here!
		z = y;
		y = (y + mantissa / y) / 2;
	}
	return assemblefloat(y, exp / 2); // multiply answer by 2^(exp/2)}
}

float LibMath::wrap(float value, float rangeMin, float rangeMax)
{
	if (rangeMin > rangeMax)
	{
		return wrap(value, rangeMax, rangeMin);
	}
	else if (rangeMin == rangeMax)
		return rangeMin;

	if (value >= rangeMin && value <= rangeMax)
		return value;
	else
	{
		return (value >= 0 ? rangeMin : rangeMax) + LibMath::fmod(value, rangeMax - rangeMin);
	}
}

float LibMath::fmod(float numerator, float denominator)
{
	return numerator - ((int)(numerator / denominator)) * denominator;
}

void LibMath::swap(int& alpha, int& beta)
{
	alpha ^= beta;
	beta ^= alpha;
	alpha ^= beta;
}

void LibMath::swap(float& alpha, float& beta)
{
	float temp = alpha;
	alpha = beta;
	beta = temp;
}

void LibMath::separatefloat(float value, float& mantissa, int& exponent)
{
	int binValue = *(int*)&value;

	int temp = binValue & 0x7F800000;

	exponent = temp;

	temp = 0;
	while (exponent > 0)
	{
		temp++;
		exponent >>= 1;
	}
	exponent = temp;

	mantissa = value / power(2.f, exponent);
}

float LibMath::assemblefloat(float mantissa, int exponent)
{
	return mantissa * power(2.f, exponent);
}
