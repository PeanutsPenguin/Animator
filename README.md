# Animator Project 

<details>
  <summary>Table of Content</summary>
  <ol>
    <li>
      <a href="#summary">Summary</a>
    </li>
    <li>
    <a href="#step-1">Step 1</a>
    </li>
      <li>
    <a href="#step-2">Step 2</a>
    </li>
    <li>
    <a href="#step-3">Step 3</a>
    </li>
    <li>
    <a href="#step-4">Step 4</a>
    </li>
    <li>
    <a href="#step-5">Step 5</a>
    </li>
    <li>
    <a href="#contact">Contact</a>
    </li>
  </ol>
</details>

## Summary
School Project to discover how skeletton animation work. A visual studio solution with graphic rendering built-in has been given to us. The main exercise was the good us of the bone's data and the mathematical reflexion behind a good animation
## Step 1
First of all, we have to draw the skelletton in bind pose.

<img width="1297" height="1262" alt="Screenshot 2025-09-19 083846" src="https://github.com/user-attachments/assets/316c76d0-927f-487f-99a0-9ad75c89d0e4" />

*Snippet* :

```cpp
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
```
## Step 2
Once skelletton is on screen, we can animate it.

https://github.com/user-attachments/assets/8b644f5b-b904-46bd-a9d0-3908b0a37eb7

*Snippet* :

```cpp
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
```
## Step 3 
Now that the skelletton moves, it's time for the skinning phase.

https://github.com/user-attachments/assets/17935aaf-e54a-41fc-9121-05c055ae517c

*Snippet* :

```cpp
	void drawStep3(void)
	{
		std::vector<Animation::Bone> bones = this->m_anim1.m_skelettonBindPose.m_bones;

		for (size_t i = 0; i < this->m_bindPosSkeletton.m_bones.size(); i++)
		{
			if (this->m_bindPosSkeletton.m_bones[i].m_parentIndex != -1)
			{
				bones[i].m_localTransform = (this->m_anim1.m_skelettonAnim[this->m_anim1.m_currentKeyFrameIndex].m_bones[i].m_localTransform
											* bones[i].m_localTransform)
											* bones[bones[i].m_parentIndex].m_localTransform; 
			}

			this->m_anim1.m_offsetMatrices[i] = LibMath::Mat4(bones[i].m_localTransform)
										* this->m_bindPosSkeletton.m_inverseBindPose[i];
		}

		SetSkinningPose((float*)&this->m_anim1.m_offsetMatrices[0][0], bones.size());
	}
```
## Step 4 
Everything is rendered on the screen, but we can render it better with interpolation.

https://github.com/user-attachments/assets/9d328e03-19f8-4376-a1f3-dc252e7ac65c

*Snippet* : 

```cpp
	//Lerp two Quaternion
	Quat Quat::Slerp(Quat const& a, Quat b, float alpha)
	{
		float RawCosom = LibMath::Vector4::Dot(a, b);

		float const Sign = RawCosom >= 0.f ? 1.f : -1.f;
		RawCosom *= Sign;

		float Scale0 = 1.f - alpha;
		float Scale1 = alpha * Sign;

		if (RawCosom < 1.f)
		{
			float const Omega = std::acos(RawCosom);
			float const InvSin = 1.f / std::sin(Omega);
			Scale0 = std::sin(Scale0 * Omega) * InvSin;
			Scale1 = std::sin(Scale1 * Omega) * InvSin;
		}

		return a * Scale0 + b * Scale1;
	}
```
## Step 5
With this kinf of interpolation, we can also switch from an animation to another. 

https://github.com/user-attachments/assets/cea6b049-8d78-4e19-bf35-8df81473fdb9

*Snippet* :

```cpp
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
```
## Contact

<u>**Malo Sadoine**</u>

- [![Linkedin][LinkedIn]][LinkedIn-url]
- mal.sadoine@gmail.com

[LinkedIn]: https://img.shields.io/badge/linkedin-34a8eb?style=for-the-badge&logo=linkedin
[LinkedIn-url]: https://www.linkedin.com/in/malo-sadoine-098b7a254/
