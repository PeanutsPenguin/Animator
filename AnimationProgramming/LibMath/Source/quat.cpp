#include <LibMath/quat.h>

#include "LibMath/Arithmetic.h"
#include "LibMath/Interpolation.h"

namespace LibMath
{
	Quat::Quat(void) : Quat(1.f,Vector3::zero()) {}

	Quat::Quat(Vector4 const& vec) : a(vec.w), b(vec.x), c(vec.y), d(vec.z) {}

	Quat::Quat(float a,Vector3 const& im) : a(a), b(im.x), c(im.y), d(im.z) {}

	Quat::Quat(float a, float b, float c, float d) : a(a), b(b), c(c), d(d) {}

	Quat::operator LibMath::Vector<4U, float>() const 
	{
		LibMath::Vector4 result(this->a, this->b, this->c, this->d);

		return result;
	}

	Quat Quat::Slerp(Quat const& a, Quat b, float alpha)
	{
		float RawCosom = LibMath::Vector4::Dot(a, b);

		float const Sign = RawCosom >= 0.f ? 1.f : -1.f;
		RawCosom *= Sign;

		float Scale0 = 1.f - alpha;
		float Scale1 = alpha * Sign;

		if (RawCosom < 1.f)
		{
			float const Omega = std::acos(RawCosom);
			float const InvSin = 1.f / std::sin(Omega);
			Scale0 = std::sin(Scale0 * Omega) * InvSin;
			Scale1 = std::sin(Scale1 * Omega) * InvSin;
		}

		return a * Scale0 + b * Scale1;
	}

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

	LibMath::Mat4 Quat::Rotation(Quat quat)
	{
		if (!Quat::IsUnit(quat))
		{
			quat = Quat::Normalize(quat);
		}

		float const aSquared = quat.a * quat.a;
		float const bSquared = quat.b * quat.b;
		float const cSquared = quat.c * quat.c;
		float const dSquared = quat.d * quat.d;

		float const ab = quat.a * quat.b;
		float const ac = quat.a * quat.c;
		float const ad = quat.a * quat.d;

		float const bc = quat.b * quat.c;
		float const bd = quat.b * quat.d;

		float const cd = quat.c * quat.d;

		return LibMath::Mat4(
			LibMath::Vector4(aSquared + bSquared - cSquared - dSquared, 2.f * (ad + bc), 2.f * (bd - ac), 0.f),
			LibMath::Vector4(2.f * (bc - ad), aSquared - bSquared + cSquared - dSquared, 2.f * (ab + cd), 0.f),
			LibMath::Vector4(2.f * (ac + bd), 2.f * (cd - ab), aSquared - bSquared - cSquared + dSquared, 0.f),
			LibMath::Vector4::Zero());
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

	Quat operator+(Quat const& lhs, Quat const& rhs)
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

	bool operator==(Quat const& lhs, Quat const& rhs)
	{
		return (lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z && lhs.w == rhs.w);
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