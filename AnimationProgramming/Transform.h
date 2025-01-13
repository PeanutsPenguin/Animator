#pragma once

#include "LibMath/Vector/Vec3.h"
#include "LibMath/quat.h"
#include "LibMath/Matrix/Mat4x4.h"

struct Transform
{
	LibMath::Vector3 mPosition;
	LibMath::Quat mRotation;

	operator LibMath::Mat4() const;
};

Transform operator-(Transform const& pRight);

Transform operator*(Transform pLeft, Transform const& pRight);

Transform& operator*=(Transform& pLeftRef, Transform const& pRight);

Transform interpolate(Transform const& pLeft, Transform const& pRight, float pAlpha);
