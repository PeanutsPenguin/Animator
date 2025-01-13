#include <LibMath/quat.h>

#include "LibMath/Arithmetic.h"

namespace LibMath
{
	Quat::Quat(void) : Quat(1.f,Vector3::zero()) {}

	Quat::Quat(Vector4 const& vec) : a(vec.w), b(vec.x), c(vec.y), d(vec.z) {}

	Quat::Quat(float a,Vector3 const& im) : a(a), b(im.x), c(im.y), d(im.z) {}

	Quat::Quat(float a, float b, float c, float d) : a(a), b(b), c(c), d(d) {}

	float Quat::Magnitude(Quat const& quat)
	{
		float const mSquared = Quat::MagnitudeSquared(quat);
		return LibMath::almostequal(mSquared, 1.f) ? 1.f : std::sqrtf(mSquared);
	}

	float Quat::MagnitudeSquared(Quat const& quat)
	{
		return quat.a * quat.a + quat.b * quat.b + quat.c * quat.c + quat.d * quat.d;
	}

	int Quat::Compare(Quat const& a, Quat const& b)
	{
		float aMagnitudeSqrt = Quat::MagnitudeSquared(a);
		float bMagnitudeSqrt = Quat::MagnitudeSquared(b);
		return aMagnitudeSqrt < bMagnitudeSqrt ? 1 : aMagnitudeSqrt > bMagnitudeSqrt ? -1 : 0;
	}

	bool Quat::IsUnit(Quat const& quat)
	{
		return LibMath::almostequal(Quat::MagnitudeSquared(quat), 1.f);
	}

	Quat Quat::Normalize(Quat const& quat)
	{
		float const magnitude = Quat::Magnitude(quat);
		return LibMath::almostequal(magnitude, 1.f) ? quat : quat / magnitude;
	}

	Quat Quat::Conjugate(Quat const& quat)
	{
		return Quat(quat.a, -Vector3(quat.b, quat.c, quat.d));
	}

	Quat Quat::Inverse(Quat const& quat)
	{
		float const magnitude = Quat::Magnitude(quat);
		float const mult = LibMath::almostequal(magnitude, 1.f) ? 1.f : 1.f / magnitude;

		return Quat::Conjugate(quat) * mult;
	}

	Mat4 Quat::Matrix(Quat const& quat)
	{
		return Mat4(
			Vector4(quat.a, -quat.b, -quat.c, -quat.d), Vector4(quat.b, quat.a, -quat.d, quat.c),
			Vector4(quat.c, quat.d, quat.a, -quat.b), Vector4(quat.d, -quat.c, quat.b, quat.a));
	}

	Mat4 Quat::Rotation(Quat quat)
	{
		if (!Quat::IsUnit(quat))
		{
			quat = Quat::Normalize(quat);
		}

		return Mat4(
			Vector4(quat.a * quat.a + quat.b * quat.b - quat.c * quat.c - quat.d * quat.d,
							 2.f * quat.b * quat.c - 2.f * quat.a * quat.d, 2.f * quat.a * quat.c + 2.f * quat.b * quat.d, 0.f),
			Vector4(2.f * quat.a * quat.d + 2.f * quat.b * quat.c,
							 quat.a * quat.a - quat.b * quat.b + quat.c * quat.c - quat.d * quat.d,
							 2.f * quat.c * quat.d - 2.f * quat.a * quat.b, 0.f),
			Vector4(2.f * quat.b * quat.d - 2.f * quat.a * quat.c, 2.f * quat.a * quat.b + 2.f * quat.c * quat.b,
							 quat.a * quat.a - quat.b * quat.b - quat.c * quat.c + quat.d * quat.d, 0.f),
			Vector4::Zero());
	}

	Vector3 Quat::Rotate(Quat const& quat,Vector3 const& vec)
	{
		Quat result = quat * Quat(0.f, vec.x, vec.y, vec.z) * Quat::Inverse(quat);
		return Vector3(result.b, result.c, result.d);
	}

	Vector4 Quat::Rotate(Quat const& quat, Vector4 const& vec)
	{
		Quat result = quat * Quat(vec) * Quat::Inverse(quat);
		return Vector4(result.b, result.c, result.d, result.a);
	}

	Quat operator+(Quat& lhs, Quat const& rhs)
	{
		Vector4 const lhsIm  = Vector4(lhs.b, lhs.c, lhs.d, lhs.a);
		Vector4 const rhsIm  = Vector4(rhs.b, rhs.c, rhs.d, rhs.a);
		Vector4 const result = lhsIm + rhsIm;

		return Quat(result.w, LibMath::Vector3(result));
	}

	Quat& operator+=(Quat& lhs, Quat const& rhs)
	{
		lhs.a += rhs.a;
		lhs.b += rhs.b;
		lhs.c += rhs.c;
		lhs.d += rhs.d;
		return lhs;
	}

	Quat operator-(Quat& lhs, Quat const& rhs)
	{
		Vector4 const lhsIm  = Vector4(lhs.b, lhs.c, lhs.d, lhs.a);
		Vector4 const rhsIm  = Vector4(rhs.b, rhs.c, rhs.d, rhs.a);
		Vector4 const result = lhsIm - rhsIm;

		return Quat(result.w, LibMath::Vector3(result));
	}

	Quat& operator-=(Quat& lhs, Quat const& rhs)
	{
		lhs.a -= rhs.a;
		lhs.b -= rhs.b;
		lhs.c -= rhs.c;
		lhs.d -= rhs.d;
		return lhs;
	}

	Quat operator*(Quat const& lhs, Quat const& rhs)
	{
		Vector3 const lhsIm =Vector3(lhs.b, lhs.c, lhs.d);
		Vector3 const rhsIm =Vector3(rhs.b, rhs.c, rhs.d);

		return Quat(lhs.a * rhs.a -Vector3::dot(lhsIm, rhsIm),
					rhsIm * lhs.a + lhsIm * rhs.a +Vector3::cross(lhsIm, rhsIm));
	}

	Quat operator*(Quat const& quat, float scalar)
	{
		return Quat(quat.a * scalar, quat.b * scalar, quat.c * scalar, quat.d * scalar);
	}

	Quat& operator*=(Quat& quat, float scalar)
	{
		quat.a *= scalar;
		quat.b *= scalar;
		quat.c *= scalar;
		quat.d *= scalar;
		return quat;
	}

	Quat& operator*=(Quat& lhs, Quat const& rhs)
	{
		Quat result = lhs * rhs;
		memcpy(&lhs, &result, sizeof(result));
		return lhs;
	}

	Quat operator/(Quat const& quat, float scalar)
	{
		float const mult = 1.f / scalar;
		return Quat(quat.a, quat.b, quat.c, quat.d) * mult;
	}

	Quat& operator/=(Quat& quat, float scalar)
	{
		float const mult = 1.f / scalar;
		return quat *= mult;
	}

	Quat operator/(Quat const& lhs, Quat const& rhs)
	{
		return lhs * Quat::Inverse(rhs);
	}

	Quat& operator/=(Quat& lhs, Quat const& rhs)
	{
		return lhs *= Quat::Inverse(rhs);
	}

	Vector3 operator*(Quat const& quat,Vector3 const& vec)
	{
		return Quat::Rotate(quat, vec);
	}

	Vector4 operator*(Quat const& quat, Vector4 const& vec)
	{
		return Quat::Rotate(quat, vec);
	}

	std::ostream& operator<<(std::ostream& os, Quat const& quat)
	{
		os << "quat\t"
		   << "w(" << quat.w << ")\t"
		   << "x(" << quat.x << ")\t"
		   << "y(" << quat.y << ")\t"
		   << "z(" << quat.z << ")\t";
		return os;
	}
} // namespace lm