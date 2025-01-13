#ifndef __LIBMATH__TRIGONOMETRY_H__
#define __LIBMATH__TRIGONOMETRY_H__

#include "Angle/Radian.h"

namespace LibMath
{
	extern float const g_pi;		// useful constant pi -> 3.141592...
	extern float const g_2pi;		// useful constant pi -> 3.141592...
	extern float const g_halfpi;	// useful constant pi -> 3.141592...


	float	sin(Radian angle);		// float result = sin(Radian angle{0.5});		// 0.479426
	float	cos(Radian angle);		// float result = sin(Degree{45});		// 0.707107			// this make use implicit conversion
	float	tan(Radian angle);		// float result = sin(0.5_rad);			// 0.479426			// this make use user defined litteral
	Radian	asin(float value);		// Radian angle = asin(0.479426);		// Radian{0.500001}
	Radian	acos(float value);		// Degree angle = acos(0.707107);		// Degree{44.99998}	// this make use implicit conversion
	Radian	atan(float value);		// Radian angle = atan(0.546302);		// Radian{0.500000}
	Radian	atan2(float y, float x);// Radian angle = atan(1, -2);			// Radian{2.677945}
}

#endif // !__LIBMATH__TRIGONOMETRY_H__
