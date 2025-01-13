#include "LibMath/Interpolation.h"

namespace LibMath
{
	float Lerp(float& alpha, float& bravo, float ratio)
	{
		if (ratio == 0)
			return alpha;
		else if (ratio == 1.f)
			return bravo;

		return (bravo - alpha) * ratio + alpha;
	}

	Vector2 Lerp(Vector2& charlie, Vector2& delta, float ratio)
	{

		if (ratio == 0)
			return charlie;
		else if (ratio == 1.f)
			return delta;

		return (delta - charlie) * ratio + charlie;
	}

	Vector3 Lerp(Vector3& echo, Vector3& foxtrot, float ratio)
	{
		if (ratio == 0)
			return echo;
		else if (ratio == 1.f)
			return foxtrot;

		return (foxtrot - echo) * ratio + echo;
	}

	Vector4 Lerp(Vector4& kilo, Vector4& lima, float ratio)
	{
		if (ratio == 0)
			return kilo;
		else if (ratio == 1.f)
			return lima;

		return (lima - kilo) * ratio + kilo;
	}

	Radian Lerp(Radian& mike, Radian& november, float ratio)
	{
		if (ratio == 0)
			return mike;
		else if (ratio == 1.f)
			return november;

		return Radian((november.raw() - mike.raw()) * ratio + mike.raw());
	}

	Degree Lerp(Degree& oscar, Degree& papa, float ratio)
	{
		if (ratio == 0)
			return oscar;
		else if (ratio == 1.f)
			return papa;

		return Degree((papa.raw() - oscar.raw()) * ratio + oscar.raw());
	}

	Vector2 Bilerp(Vector2& quebec, Vector2& romeo, Vector2& ratio)
	{
		return Vector2(Lerp(quebec.x, romeo.x, ratio.x), Lerp(quebec.y, romeo.y, ratio.y));
	}
}
