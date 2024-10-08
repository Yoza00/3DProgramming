#pragma once

class Sun :public KdGameObject
{
public:

	Sun() {}
	~Sun()override;

	void DrawLit()override;
	void Update()override;
	void Init()override;

private:

	KdModelData m_sun;
};