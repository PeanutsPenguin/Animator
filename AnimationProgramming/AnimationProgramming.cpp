// AnimationProgramming.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "Engine.h"
#include "Simulation.h"

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

	virtual void Update(float frameTime) override
	{
		// X axis
		DrawLine(0, 0, 0, 100, 0, 0, 1, 0, 0);

		// Y axis
		DrawLine(0, 0, 0, 0, 100, 0, 0, 1, 0);

		// Z axis
		DrawLine(0, 0, 0, 0, 0, 100, 0, 0, 1);

		DrawBones();

	}
public: 

	void DrawBones()
	{
		/*for (int i = 0; i < GetSkeletonBoneCount() - 7; i++)
		{
			LinkBoneToParent(i);
		}*/

		LinkBoneToParent(1);
	}

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

	void LinkBoneToParent(int index)
	{
		float x0, y0, z0,
			x1, y1, z1,
			quatx0, quaty0, quatz0, quatw0,
			quatx1, quaty1, quatz1, quatw1;

		int parentIndex = GetSkeletonBoneParentIndex(index);

		if (parentIndex == -1)
			return;

		GetSkeletonBoneLocalBindTransform(index, x0, y0, z0, quatx0, quaty0, quatz0, quatw0);
		GetSkeletonBoneLocalBindTransform(parentIndex, x1, y1, z1, quatx1, quaty1, quatz1, quatw1);

		DrawLine(x0, y0 - 50, z0, x1, y1 - 50, z1, 0, 0, 255);
	}

};

int main()
{
	CSimulation simulation;
	Run(&simulation, 1400, 800);
	
	for(int i = 0; i < GetSkeletonBoneCount(); i++)
	{
		simulation.printSkeletonBoneInfo(i);
		printf("\n");
	}



	return 0;
}

