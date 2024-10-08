#pragma once
#include"../CameraBase.h"

class TrackingCamera :public CameraBase
{
public:

	TrackingCamera()			{}
	~TrackingCamera()	override{}

	void Update()		override;
	void Init()			override;
};