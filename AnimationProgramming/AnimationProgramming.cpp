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
		int spine01 =	GetSkeletonBoneIndex("spine_01");
		int spineParent = GetSkeletonBoneParentIndex(spine01);
		const char* spineParentName = GetSkeletonBoneName(spineParent);

		float posX, posY, posZ, quatW, quatX, quatY, quatZ;
		size_t keyCount = GetAnimKeyCount("ThirdPersonWalk.anim");
		GetAnimLocalBoneTransform("ThirdPersonWalk.anim", spineParent, keyCount / 2, posX, posY, posZ, quatW, quatX, quatY, quatZ);

		printf("Spine parent bone : %s\n", spineParentName);
		printf("Anim key count : %ld\n", keyCount);
		printf("Anim key : pos(%.2f,%.2f,%.2f) rotation quat(%.10f,%.10f,%.10f,%.10f)\n", posX, posY, posZ, quatW, quatX, quatY, quatZ);
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

		this->TimeSpent += frameTime;

		if(TimeSpent > 0.5)
		{
			this->keyFrameIndex += 1;
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

		//printf("%d", this->keyFrameIndex);

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

	virtual void Update(float frameTime) override
	{
		// X axis
		DrawLine(0, 0, 0, 100, 0, 0, 1, 0, 0);

		// Y axis
		DrawLine(0, 0, 0, 0, 100, 0, 0, 1, 0);

		// Z axis
		DrawLine(0, 0, 0, 0, 0, 100, 0, 0, 1);

		//this->step1();
		this->step2(frameTime);
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

	int keyFrameIndex = 0;
	float TimeSpent = 0;
};

int main()
{
	CSimulation simulation;
	Run(&simulation, 1400, 800);
	
	return 0;
}

