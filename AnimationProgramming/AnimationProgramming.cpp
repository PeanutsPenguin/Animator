// AnimationProgramming.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <random>

#include "Engine.h"
#include "Simulation.h"
#include "AnimationHandler.h"

#define STEP 5
#define CROSSFADELENGTH 1.f

class CSimulation : public ISimulation
{
	virtual void Init() override
	{
		this->initBindPosSkel();
		this->initCurrentAnim("ThirdPersonWalk.anim", this->m_anim1);
		this->initCurrentAnim("ThirdPersonRun.anim", this->m_anim2);

		this->m_crossFadeStop.second = (std::rand() % 500) / 100.f;
		this->m_crossFadeHandler.first = false;
		this->m_crossFadeStop.first = true;
	}

	void initBindPosSkel(void)
	{
		int skelBoneCount = GetSkeletonBoneCount() - 7;
		Animation::Skeleton skel;
		skel.m_bones.reserve(skelBoneCount);
		skel.m_inverseBindPose.reserve(skelBoneCount);

		Animation::Bone boneToAdd;

		for(size_t i = 0; i < skelBoneCount; i++)
		{
			boneToAdd.m_name = GetSkeletonBoneName(i);
			GetSkeletonBoneLocalBindTransform(i,	boneToAdd.m_localTransform.m_position.x,
													boneToAdd.m_localTransform.m_position.y,
													boneToAdd.m_localTransform.m_position.z,
													boneToAdd.m_localTransform.m_rotation.w,
													boneToAdd.m_localTransform.m_rotation.x,
													boneToAdd.m_localTransform.m_rotation.y,
													boneToAdd.m_localTransform.m_rotation.z);

			boneToAdd.m_parentIndex = GetSkeletonBoneParentIndex(i);

			if (boneToAdd.m_parentIndex != -1)
				boneToAdd.m_localTransform *= skel.m_bones[boneToAdd.m_parentIndex].m_localTransform;

			skel.m_bones.push_back(boneToAdd);
			skel.m_inverseBindPose.push_back(LibMath::Mat4(boneToAdd.m_localTransform).GetInverse());
		}

		this->m_bindPosSkeletton = skel;
		this->m_previousBones = skel.m_bones;
	}

	void initAnimSkel(int skelBoneCount, Animation::Anim& toInit)
	{
		Animation::Bone boneToAdd;

		for (size_t i = 0; i < toInit.m_keyFrame; i++)
		{
			Animation::Skeleton skelToAdd;
			skelToAdd.m_bones.reserve(skelBoneCount);

			for (size_t j = 0; j < skelBoneCount; j++)
			{
				boneToAdd.m_name = GetSkeletonBoneName(j);

				GetAnimLocalBoneTransform(toInit.m_name, j, i,
					boneToAdd.m_localTransform.m_position.x,
					boneToAdd.m_localTransform.m_position.y,
					boneToAdd.m_localTransform.m_position.z,
					boneToAdd.m_localTransform.m_rotation.w,
					boneToAdd.m_localTransform.m_rotation.x,
					boneToAdd.m_localTransform.m_rotation.y,
					boneToAdd.m_localTransform.m_rotation.z);

				boneToAdd.m_parentIndex = GetSkeletonBoneParentIndex(j);

				skelToAdd.m_bones.push_back(boneToAdd);
			}

			toInit.m_skelettonAnim.push_back(skelToAdd);
		}
	}

	void initCurrentAnim(const char* name, Animation::Anim& toInit)
	{
		toInit.m_name = name;
		toInit.m_keyFrame = GetAnimKeyCount(name);
		toInit.m_timeSpent = 0;
		toInit.m_currentKeyFrameIndex = 0;

		int skelBoneCount = GetSkeletonBoneCount() - 7;

		this->initAnimSkel(skelBoneCount, toInit);

		toInit.m_skelettonBindPose.m_bones.reserve(skelBoneCount);

		Animation::Bone boneToAdd;

		for (size_t j = 0; j < skelBoneCount; j++)
		{
			boneToAdd.m_name = GetSkeletonBoneName(j);

			GetSkeletonBoneLocalBindTransform(j,
				boneToAdd.m_localTransform.m_position.x,
				boneToAdd.m_localTransform.m_position.y,
				boneToAdd.m_localTransform.m_position.z,
				boneToAdd.m_localTransform.m_rotation.w,
				boneToAdd.m_localTransform.m_rotation.x,
				boneToAdd.m_localTransform.m_rotation.y,
				boneToAdd.m_localTransform.m_rotation.z);

			boneToAdd.m_parentIndex = GetSkeletonBoneParentIndex(j);

			toInit.m_skelettonBindPose.m_bones.push_back(boneToAdd);

			toInit.m_offsetMatrices.push_back(LibMath::Mat4::Identity());
		}
	}

	void switchKeyFrame(float frameTime, Animation::Anim& currentAnim)
	{
		if (currentAnim.m_timeSpent < (1.f / currentAnim.m_keyFrame))
		{
			currentAnim.m_timeSpent += frameTime;
		}
		else if (currentAnim.m_currentKeyFrameIndex < currentAnim.m_keyFrame - 1)
		{
			currentAnim.m_currentKeyFrameIndex += 1;
			currentAnim.m_timeSpent = 0;
		}
		else
		{
			currentAnim.m_currentKeyFrameIndex = 0;
			currentAnim.m_timeSpent = 0;
			std::cout << this->m_fps << std::endl;
			this->m_fps = 0;
		}
		this->m_fps++;

		if (currentAnim.m_currentKeyFrameIndex > currentAnim.m_keyFrame)
			currentAnim.m_currentKeyFrameIndex = 0;
	}
	
	void step1(void)
	{
		for (size_t i = 0; i < this->m_bindPosSkeletton.m_bones.size(); i++)
		{
			if (this->m_bindPosSkeletton.m_bones[i].m_parentIndex != -1)
			{
				drawLine(this->m_bindPosSkeletton.m_bones[i].m_localTransform.m_position,
					     this->m_bindPosSkeletton.m_bones[this->m_bindPosSkeletton.m_bones[i].m_parentIndex].m_localTransform.m_position,
						{0, 0, 0}, {0, -50, 0});
			}
		}
	}

	void step2(float frameTime) 
	{
		this->switchKeyFrame(frameTime, this->m_anim1);

		this->drawStep2();
	}

	void drawStep2(void)
	{
		std::vector<Animation::Bone> bones = this->m_anim1.m_skelettonBindPose.m_bones;

		for (size_t i = 0; i < this->m_bindPosSkeletton.m_bones.size(); i++)
		{
			if (this->m_bindPosSkeletton.m_bones[i].m_parentIndex != -1)
			{
				bones[i].m_localTransform = (this->m_anim1.m_skelettonAnim[this->m_anim1.m_currentKeyFrameIndex].m_bones[i].m_localTransform
											* bones[i].m_localTransform)
											* bones[bones[i].m_parentIndex].m_localTransform;
				
				
				drawLine(bones[i].m_localTransform.m_position,
						 bones[bones[i].m_parentIndex].m_localTransform.m_position, 
						{0, 0, 0}, {0, -50, 0});
			}
		}
	}
	
	void step3(float frameTime)
	{
		this->switchKeyFrame(frameTime, this->m_anim1);
		this->drawStep3();
	}

	void drawStep3(void)
	{
		std::vector<Animation::Bone> bones = this->m_anim1.m_skelettonBindPose.m_bones;

		for (size_t i = 0; i < this->m_bindPosSkeletton.m_bones.size(); i++)
		{
			if (this->m_bindPosSkeletton.m_bones[i].m_parentIndex != -1)
			{
				bones[i].m_localTransform = (this->m_anim1.m_skelettonAnim[this->m_anim1.m_currentKeyFrameIndex].m_bones[i].m_localTransform
											* bones[i].m_localTransform)
											* bones[bones[i].m_parentIndex].m_localTransform;  /*<---WORLD MATRIX*/
			}

			this->m_anim1.m_offsetMatrices[i] = LibMath::Mat4(bones[i].m_localTransform)
										* this->m_bindPosSkeletton.m_inverseBindPose[i];
		}

		SetSkinningPose((float*)&this->m_anim1.m_offsetMatrices[0][0], bones.size());
	}

	void step4(float frameTime)
	{
		this->switchKeyFrame(frameTime, this->m_anim1);

		this->drawStep4(this->m_anim1);
	}

	void drawStep4(Animation::Anim& toAnim)
	{
		std::vector<Animation::Bone> bones = toAnim.m_skelettonBindPose.m_bones;

		for (size_t i = 0; i < this->m_bindPosSkeletton.m_bones.size(); i++)
		{
			if (this->m_bindPosSkeletton.m_bones[i].m_parentIndex != -1)
			{
				bones[i].m_localTransform = (toAnim.m_skelettonAnim[toAnim.m_currentKeyFrameIndex].m_bones[i].m_localTransform
					* bones[i].m_localTransform)
					* bones[bones[i].m_parentIndex].m_localTransform;  /*<---WORLD MATRIX*/
			}

			this->m_previousBones[i].m_localTransform = interpolate(this->m_previousBones[i].m_localTransform, bones[i].m_localTransform, toAnim.m_timeSpent);

			toAnim.m_offsetMatrices[i] = LibMath::Mat4(this->m_previousBones[i].m_localTransform) 
													* this->m_bindPosSkeletton.m_inverseBindPose[i];
		}

		SetSkinningPose((float*)&toAnim.m_offsetMatrices[0][0], bones.size());
	}
	
	void step5(float frameTime)
	{
		this->m_crossFadeHandler.second += frameTime;

		if (this->m_crossFadeHandler.second < this->m_crossFadeStop.second)
		{
			if (!this->m_crossFadeHandler.first)
			{
				if(this->m_crossFadeStop.first)
				{
					this->switchKeyFrame(frameTime, this->m_anim1);
					this->drawStep4(this->m_anim1);
				}
				else if (!this->m_crossFadeStop.first)
				{
					this->switchKeyFrame(frameTime, this->m_anim2);
					this->drawStep4(this->m_anim2);
				}
			}
			else 
			{
				if (this->m_crossFadeStop.first)
					crossFade(this->m_anim2, this->m_anim1);
				else if (!this->m_crossFadeStop.first)
					crossFade(this->m_anim1, this->m_anim2);
			}
		}
		else 
			this->resetValue();
	}

	void resetValue(void)
	{
		this->m_crossFadeHandler.first = !this->m_crossFadeHandler.first;
		this->m_crossFadeHandler.second = 0;

		this->m_crossFadeStop.first = this->m_crossFadeHandler.first ? !this->m_crossFadeStop.first : this->m_crossFadeStop.first;
		this->m_crossFadeStop.second = this->m_crossFadeHandler.first ? CROSSFADELENGTH : (std::rand() % 500) / 100.f;

		if (this->m_crossFadeStop.second == 0)
			this->m_crossFadeStop.second = CROSSFADELENGTH;

		std::cout << "Duration :" << this->m_crossFadeStop.second << std::endl;
	}

	void crossFade(Animation::Anim& toAnim, Animation::Anim& toCross)
	{
		std::vector<Animation::Bone> bonesAnim1 = toAnim.m_skelettonBindPose.m_bones, bonesAnim2 = toAnim.m_skelettonBindPose.m_bones;
		Animation::Bone Anim1, Anim2;

		toCross.m_currentKeyFrameIndex = toAnim.m_currentKeyFrameIndex * toCross.m_keyFrame / toAnim.m_keyFrame;

		for (size_t i = 0; i < this->m_bindPosSkeletton.m_bones.size(); i++)
		{
			if (this->m_bindPosSkeletton.m_bones[i].m_parentIndex != -1)
			{
				bonesAnim1[i].m_localTransform = (toAnim.m_skelettonAnim[toAnim.m_currentKeyFrameIndex].m_bones[i].m_localTransform
					* bonesAnim1[i].m_localTransform)
					* bonesAnim1[bonesAnim1[i].m_parentIndex].m_localTransform;  /*<---WORLD MATRIX*/

				bonesAnim2[i].m_localTransform = (toCross.m_skelettonAnim[toCross.m_currentKeyFrameIndex].m_bones[i].m_localTransform
					* bonesAnim2[i].m_localTransform)
					* bonesAnim2[bonesAnim2[i].m_parentIndex].m_localTransform;  /*<---WORLD MATRIX*/
			}

			Anim1.m_localTransform = interpolate(this->m_previousBones[i].m_localTransform, 
												bonesAnim1[i].m_localTransform, 
												this->m_crossFadeHandler.second / CROSSFADELENGTH);
			Anim2.m_localTransform = interpolate(this->m_previousBones[i].m_localTransform, 
												bonesAnim2[i].m_localTransform, 
												this->m_crossFadeHandler.second / CROSSFADELENGTH);
			this->m_previousBones[i].m_localTransform = interpolate(Anim1.m_localTransform, 
														Anim2.m_localTransform, 
														this->m_crossFadeHandler.second / CROSSFADELENGTH);

			toAnim.m_offsetMatrices[i] = LibMath::Mat4(this->m_previousBones[i].m_localTransform)
				* this->m_bindPosSkeletton.m_inverseBindPose[i];
		}
		SetSkinningPose((float*)&toAnim.m_offsetMatrices[0][0], bonesAnim1.size());
	}

	virtual void Update(float frameTime) override
	{
		// X axis
		DrawLine(0, 0, 0, 100, 0, 0, 1, 0, 0);

		// Y axis
		DrawLine(0, 0, 0, 0, 100, 0, 0, 1, 0);

		// Z axis
		DrawLine(0, 0, 0, 0, 0, 100, 0, 0, 1);


		switch (STEP)
		{
		case 1:
			this->step1();
			break;
		case 2:
			this->step2(frameTime);
			break;
		case 3:
			this->step3(frameTime);
			break;
		case 4:
			this->step4(frameTime);
			break;
		case 5:
			this->step5(frameTime);
			break;
		default:
			this->step1();
			break;
		}
	}

	Animation::Skeleton m_bindPosSkeletton;
	Animation::Anim m_anim1;
	Animation::Anim m_anim2;
	std::vector<Animation::Bone> m_previousBones;
	int m_fps;
	std::pair<bool, float> m_crossFadeHandler; //First, bool to see if i'm currently crossFading or not. Second, Time spent since the beginning of the action
	std::pair<bool, float> m_crossFadeStop;	//First, bool to see if im on anim1 or anim2. Second, Time where i need to switch action

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
};

int main()
{
	CSimulation simulation;
	Run(&simulation, 1400, 800);
	
	return 0;
}

