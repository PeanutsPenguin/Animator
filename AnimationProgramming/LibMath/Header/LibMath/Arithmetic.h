#ifndef __LIBMATH__ARITHMETIC_H__
#define __LIBMATH__ARITHMETIC_H__

#define EPSILON 0.000001f
#define FLOAT_EQ(x,v) (((v - EPSILON) < x) && (x <( v + EPSILON)))

namespace LibMath
{
	bool	almostequal(float alpha, float beta);				// Return true when values are equal to 10^-6
	int		ceiling(float value);								// Return lowest integer value higher or equal to parameter (Round-up)
	float	clamp(float value, float min, float max);			// Return parameter limited by the given range
	int		floor(float value);									// Return highest integer value lower or equal to parameter (Round-down)
	float	power(float base, int exponent);					// Return base^exponent
	float	squareRoot(float value);							// Return square root of parameter
	float	wrap(float value, float rangeMin, float rangeMax);	// Return parameter as value inside the given range
	float	fmod(float numerator, float denominator);			// Return modulo of a floating point divison
	void	swap(int& alpha, int& beta);						// Swaps 2 integers
	void	swap(float& alpha, float& beta);					// Swaps 2 floats
	void	separatefloat(float value, float& mantissa, int& exponent);
	float	assemblefloat(float mantissa, int exponent);
}

#endif // !__LIBMATH__ARITHMETIC_H__
