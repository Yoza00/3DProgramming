#pragma once
#include"../CameraBase.h"

class FPSCamera :public CameraBase
{
public:

	FPSCamera()						{}
	~FPSCamera()		override	{}

	void Update()		override;
	void Init()			override;
};