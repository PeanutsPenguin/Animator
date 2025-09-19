#pragma once

#include <LibMath/vector/vec3.h>
#include <LibMath/vector/vec4.h>

#include <LibMath/matrix/mat4x4.h>

namespace LibMath
{
	/*
		Quaternion.
	*/
	struct Quat
	{
		Quat(void);

		Quat(Quat const& other) = default;

		Quat(Quat&& other) = default;

		~Quat(void) = default;

		Quat(Vector4 const& vec);

		Quat(float a, Vector3 const& im);

		Quat(float a, float b, float c, float d);

		operator Vector4() const;

		static Quat Slerp(Quat const& a, Quat b, float alpha);

		static float Magnitude(Quat const& quat);

		static float MagnitudeSquared(Quat const& quat);

		static int Compare(Quat const& a, Quat const& b);

		static bool IsUnit(Quat const& quat);

		static Quat Normalize(Quat const& quat);

		static Quat Conjugate(Quat const& quat);

		static Quat Inverse(Quat const& quat);

		static Mat4 Matrix(Quat const& quat);

		static Mat4 Rotation(Quat quat);

		static Vector3 Rotate(Quat const& quat, Vector3 const& vec);

		static Vector4 Rotate(Quat const& quat, Vector4 const& vec);

		Quat& operator=(Quat const& rhs) = default;

		Quat& operator=(Quat&& rhs) = default;

		union
		{
			float w, a;
		};
		union
		{
			float x, b;
		};
		union
		{
			float y, c;
		};
		union
		{
			float z, d;
		};
	};

	Quat operator+(Quat const& lhs, Quat const& rhs);

	Quat& operator+=(Quat& lhs, Quat const& rhs);

	Quat operator-(Quat const& lhs, Quat const& rhs);

	Quat& operator-=(Quat& lhs, Quat const& rhs);

	Quat operator*(Quat const& quat, float scalar);

	Quat& operator*=(Quat& quat, float scalar);

	Quat operator*(Quat const& lhs, Quat const& rhs);

	Quat& operator*=(Quat& lhs, Quat const& rhs);

	Quat operator/(Quat const& quat, float scalar);

	Quat& operator/=(Quat& quat, float scalar);

	Quat operator/(Quat const& lhs, Quat const& rhs);

	Quat& operator/=(Quat& lhs, Quat const& rhs);

	Vector3 operator*(Quat const& quat, Vector3 const& vec);

	Vector4 operator*(Quat const& quat, Vector4 const& vec);

	bool operator==(Quat const& rhs, Quat const& lhs);

	std::ostream& operator<<(std::ostream& os, Quat const& quat);
} // namespace LibMath