#include "Transform.h"
#include "LibMath/Interpolation.h"

Transform::operator LibMath::Mat4() const
{
	LibMath::Mat4 result = LibMath::Mat4::Identity();

	result *= LibMath::Mat4::Translate(this->m_position);
	result *= LibMath::Quat::Rotation(this->m_rotation);

	return result;
}

Transform operator*(Transform pLeft, Transform const& pRight)
{
	pLeft.m_position = LibMath::Quat::Rotate(pRight.m_rotation, { pLeft.m_position.x, pLeft.m_position.y, pLeft.m_position.z , 0 });

	pLeft.m_position += pRight.m_position;
	pLeft.m_rotation = pRight.m_rotation * pLeft.m_rotation;

	return pLeft;
}

Transform& operator*=(Transform& pLeftRef, Transform const& pRight)
{
	pLeftRef.m_position = LibMath::Quat::Rotate(pRight.m_rotation, {  pLeftRef.m_position.x, pLeftRef.m_position.y, pLeftRef.m_position.z , 0});

	pLeftRef.m_position += pRight.m_position;
	pLeftRef.m_rotation = pRight.m_rotation * pLeftRef.m_rotation;

	return pLeftRef;
}

Transform interpolate(Transform const& pLeft, Transform const& pRight, float pAlpha)
{
	LibMath::Vector3 newPos = LibMath::Lerp(pLeft.m_position, pRight.m_position, pAlpha);
	LibMath::Quat	 newQuat = LibMath::Quat::Slerp(pLeft.m_rotation, pRight.m_rotation, pAlpha);

	return Transform(newPos, newQuat);
}

std::ostream& operator<<(std::ostream& os, const Transform& a)
{
	os << "Position : " << a.m_position << "\t" << " Quat :" << a.m_rotation << "\n";
	return os;
}
