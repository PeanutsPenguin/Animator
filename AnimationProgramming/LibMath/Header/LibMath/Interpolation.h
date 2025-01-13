#ifndef __LIBMATH__INTERPOLATION_H__
#define __LIBMATH__INTERPOLATION_H__

#include "LibMath/Angle.h"
#include "LibMath/Vector.h"

namespace LibMath
{
	float	Lerp(float& alpha, float& bravo, float ratio);					//Lerp between two float with a given ratio
			
	Vector2	Lerp(Vector2& charlie, Vector2& delta, float ratio);			//Lerp between two Vector2 with a given ratio

	Vector3	Lerp(Vector3& echo, Vector3& foxtrot, float ratio);				//Lerp between two Vector3 with a given ratio

	Vector4	Lerp(Vector4& kilo, Vector4& lima, float ratio);				//Lerp between two Vector4 with a given ratio

	Radian	Lerp(Radian& mike, Radian& november, float ratio);				//Lerp between two radiant with a given ratio

	Degree	Lerp(Degree& oscar, Degree& papa, float ratio);					//Lerp between two degrees with a given ratio

	Vector2	Bilerp(Vector2& quebec, Vector2& romeo, Vector2& ratio);		//Bilerp between two Vector2 with a given ratio
}

#endif // !__LIBMATH__INTERPOLATION_H__
