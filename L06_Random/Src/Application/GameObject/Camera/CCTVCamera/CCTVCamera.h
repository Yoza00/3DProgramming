#pragma once
#include "../CameraBase.h"

class CCTVCamera : public CameraBase
{
public:
	CCTVCamera()						{}
	~CCTVCamera()			override	{}

	void PostUpdate()		override;
	void Init()				override;

private:

	void UpdateLookAtRotate(const Math::Vector3& _targetPos);
};