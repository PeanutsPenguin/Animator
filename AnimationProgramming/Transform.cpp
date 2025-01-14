#include "Transform.h"

Transform::operator LibMath::Mat4() const
{
	LibMath::Mat4 result = LibMath::Mat4::Identity();

	result *= LibMath::Mat4::Translate(this->mPosition);
	result *= LibMath::Quat::Rotation(this->mRotation);

	return result;
}



Transform operator*(Transform pLeft, Transform const& pRight)
{
	pLeft.mPosition = LibMath::Quat::Rotate(pRight.mRotation, { pLeft.mPosition.x, pLeft.mPosition.y, pLeft.mPosition.z , 0 });

	pLeft.mPosition += pRight.mPosition;
	pLeft.mRotation = pRight.mRotation * pLeft.mRotation;

	return pLeft;
}

Transform& operator*=(Transform& pLeftRef, Transform const& pRight)
{
	pLeftRef.mPosition = LibMath::Quat::Rotate(pRight.mRotation, {  pLeftRef.mPosition.x, pLeftRef.mPosition.y, pLeftRef.mPosition.z , 0});

	pLeftRef.mPosition += pRight.mPosition;
	pLeftRef.mRotation = pRight.mRotation * pLeftRef.mRotation;

	return pLeftRef;
}

Transform interpolate(Transform const& pLeft, Transform const& pRight, float pAlpha)
{
	return Transform();
}
