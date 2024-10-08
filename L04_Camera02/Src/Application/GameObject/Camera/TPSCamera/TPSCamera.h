#pragma once
#include"../CameraBase.h"

class TPSCamera :public CameraBase
{
public:

	TPSCamera()						{}
	~TPSCamera()			override	{}

	void Update()		override;
	void Init()			override;
};