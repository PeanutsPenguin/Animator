#pragma once

#include "Transform.h"
#include <vector>

namespace Animation
{
	struct Bone
	{
		const char* m_name;
		Transform m_localTransform;
		int m_parentIndex;
	};

	struct Skeleton
	{
		std::vector<Bone> m_bones;
		std::vector<LibMath::Mat4> m_inverseBindPose;
	};

	struct Anim
	{
		std::vector<LibMath::Mat4> m_offsetMatrices;
		std::vector<Skeleton> m_skelettonAnim;
		Skeleton m_skelettonBindPose;
		float m_timeSpent;
		int m_keyFrame;
		int m_currentKeyFrameIndex;
		const char* m_name;
	};
}

void drawLine(LibMath::Vector3 const& pStart, LibMath::Vector3 const& pEnd,
	LibMath::Vector3 const& pColor, LibMath::Vector3 const& pOffset);

