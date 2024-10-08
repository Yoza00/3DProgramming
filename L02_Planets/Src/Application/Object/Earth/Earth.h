#pragma once

class Earth :public KdGameObject
{
public:

	Earth() {}
	~Earth()override;

	void DrawLit()override;
	void Update()override;
	void Init()override;

private:

	KdModelData m_earth;
};