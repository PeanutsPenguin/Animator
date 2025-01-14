// AnimationProgramming.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "Engine.h"
#include "Simulation.h"
#include "Transform.h"

#include "vector"

class CSimulation : public ISimulation
{
	virtual void Init() override
	{
		int BoneCount = GetSkeletonBoneCount() - 7;
		std::vector<Transform> bones;
		bones.reserve(BoneCount);

		for (int i = 0; i < BoneCount; i++)
		{
			bones.push_back(Transform());
			GetSkeletonBoneLocalBindTransform(i, bones[i].mPosition.x, bones[i].mPosition.y, bones[i].mPosition.z,
				bones[i].mRotation.w, bones[i].mRotation.x, bones[i].mRotation.y, bones[i].mRotation.z);

			int parent = GetSkeletonBoneParentIndex(i);

			if (parent != -1)
				bones[i] *= bones[parent];

			this->inverseBindMatrices.push_back(LibMath::Mat4(bones[i]).GetInverse());

		}
	}

	void step1(void)
	{
		std::vector<Transform> bones;
		int BoneCount = GetSkeletonBoneCount() - 7;
		bones.reserve(BoneCount);

		for (int i = 0; i < BoneCount; i++)
		{
			bones.push_back(Transform());
			GetSkeletonBoneLocalBindTransform(i, bones[i].mPosition.x, bones[i].mPosition.y, bones[i].mPosition.z,
				bones[i].mRotation.w, bones[i].mRotation.x, bones[i].mRotation.y, bones[i].mRotation.z);

			int parent = GetSkeletonBoneParentIndex(i);

			if (parent != -1)
			{
				bones[i] *= bones[parent];
				DrawLine(bones[i].mPosition.x, bones[i].mPosition.y - 50, bones[i].mPosition.z,
					bones[parent].mPosition.x, bones[parent].mPosition.y - 50, bones[parent].mPosition.z,
					0, 0, 0);
			}
		}
	}

	void step2(float frameTime)
	{
		int nbrKeyFrames = GetAnimKeyCount("ThirdPersonWalk.anim");

		if (TimeSpent < (1.f / nbrKeyFrames))
		{
			this->TimeSpent += frameTime;
		}
		else if (this->keyFrameIndex < nbrKeyFrames - 1)
		{
			this->keyFrameIndex += 1;
			this->TimeSpent = 0;
		}
		else 
		{
			this->keyFrameIndex = 0;
			this->TimeSpent = 0;
		}

		if (this->keyFrameIndex > nbrKeyFrames)
			this->keyFrameIndex = 0;

		this->DrawBonesStep2();
	}

	void DrawBonesStep2()
	{
		std::vector<Transform> bones;
		int BoneCount = GetSkeletonBoneCount() - 7;
		bones.reserve(BoneCount);

		Transform animBone;

		for (int i = 0; i < BoneCount; i++)
		{
			bones.push_back(Transform());
			GetSkeletonBoneLocalBindTransform(i, bones[i].mPosition.x, bones[i].mPosition.y, bones[i].mPosition.z,
				bones[i].mRotation.w, bones[i].mRotation.x, bones[i].mRotation.y, bones[i].mRotation.z);

			GetAnimLocalBoneTransform("ThirdPersonWalk.anim", i, this->keyFrameIndex, animBone.mPosition.x, animBone.mPosition.y, animBone.mPosition.z,
				animBone.mRotation.w, animBone.mRotation.x, animBone.mRotation.y, animBone.mRotation.z);

			int parent = GetSkeletonBoneParentIndex(i);

			if (parent != -1)
			{
				bones[i] = (animBone * bones[i]) * bones[parent];
				DrawLine(bones[i].mPosition.x, bones[i].mPosition.y - 50, bones[i].mPosition.z, bones[parent].mPosition.x, bones[parent].mPosition.y - 50, bones[parent].mPosition.z, 0, 0, 0);
			}
		}
	}
	
	void step3(float frameTime)
	{
		int nbrKeyFrames = GetAnimKeyCount("ThirdPersonWalk.anim");

		if (TimeSpent < (1.f / nbrKeyFrames))
		{
			this->TimeSpent += frameTime;
		}
		else if (this->keyFrameIndex < nbrKeyFrames - 1)
		{
			this->keyFrameIndex += 1;
			this->TimeSpent = 0;
		}
		else
		{
			this->keyFrameIndex = 0;
			this->TimeSpent = 0;
		}

		if (this->keyFrameIndex > nbrKeyFrames)
			this->keyFrameIndex = 0;

		this->drawStep3();
	}

	void drawStep3(void)
	{
		std::vector<Transform> bones;
		std::vector<LibMath::Mat4> bonesMatrices;
		int BoneCount = GetSkeletonBoneCount() - 7;
		bones.reserve(BoneCount);
		bonesMatrices.reserve(BoneCount);

		Transform animBone;

		for (int i = 0; i < BoneCount; i++)
		{
			bones.push_back(Transform());
			GetSkeletonBoneLocalBindTransform(i, bones[i].mPosition.x, bones[i].mPosition.y, bones[i].mPosition.z,
				bones[i].mRotation.w, bones[i].mRotation.x, bones[i].mRotation.y, bones[i].mRotation.z);

			GetAnimLocalBoneTransform("ThirdPersonWalk.anim", i, this->keyFrameIndex, animBone.mPosition.x, animBone.mPosition.y, animBone.mPosition.z,
				animBone.mRotation.w, animBone.mRotation.x, animBone.mRotation.y, animBone.mRotation.z);

			int parent = GetSkeletonBoneParentIndex(i);

			if (parent != -1)
				bones[i] = (animBone * bones[i]) * bones[parent];  /*<---WORLD MATRIX*/

			//if (parent != -1)
			//	bones[i] *= bones[parent];

			LibMath::Mat4 offsetMatrix = LibMath::Mat4(bones[i]) * this->inverseBindMatrices[i];
			bonesMatrices.push_back(offsetMatrix);
		}

		SetSkinningPose((float*)&bonesMatrices[0][0], BoneCount);
	}

	virtual void Update(float frameTime) override
	{
		// X axis
		DrawLine(0, 0, 0, 100, 0, 0, 1, 0, 0);

		// Y axis
		DrawLine(0, 0, 0, 0, 100, 0, 0, 1, 0);

		// Z axis
		DrawLine(0, 0, 0, 0, 0, 100, 0, 0, 1);

		//this->step1();
		//this->step2(frameTime);
		this->step3(frameTime);
	}

public: 

	void printSkeletonBoneInfo(int index)
	{
		float x0, y0, z0, quatx0, quaty0, quatz0, quatw0;
		GetSkeletonBoneLocalBindTransform(index, x0, y0, z0, quatx0, quaty0, quatz0, quatw0);

		printf("Bone Name : "); printf(GetSkeletonBoneName(index));
		printf("\n");
		printf("Position : x : %f, y : %f,  z : %f\n", x0, y0, z0);
		printf("Quaternion :  x : %f, y : %f,  z : %f,  w : %f", quatx0, quaty0, quatz0, quatw0);
		printf("\n");
	}

	std::vector<LibMath::Mat4> inverseBindMatrices;
	int keyFrameIndex = 0;
	float TimeSpent = 0;
};

int main()
{
	CSimulation simulation;
	Run(&simulation, 1400, 800);
	
	return 0;
}

