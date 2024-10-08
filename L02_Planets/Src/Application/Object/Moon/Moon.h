#pragma once

class Moon :public KdGameObject
{
public:

	Moon(){}
	~Moon()override;

	void DrawLit()override;
	void Update()override;
	void Init()override;

private:

	KdModelData m_moon;
};