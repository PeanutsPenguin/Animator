#pragma once

#include "LibMath/Vector/Vec3.h"
#include "LibMath/quat.h"
#include "LibMath/Matrix/Mat4x4.h"

struct Transform
{
	LibMath::Vector3 m_position;
	LibMath::Quat m_rotation;

	operator LibMath::Mat4() const;
};

Transform operator*(Transform pLeft, Transform const& pRight);

Transform& operator*=(Transform& pLeftRef, Transform const& pRight);

Transform interpolate(Transform const& pLeft, Transform const& pRight, float pAlpha);

std::ostream& operator<<(std::ostream&, const Transform&);		//Operator << to debug a vector in the console


