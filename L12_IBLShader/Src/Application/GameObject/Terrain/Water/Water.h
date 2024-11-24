#pragma once

class Water : public KdGameObject
{
public:
	Water() {}
	virtual ~Water()		override {}

	void Init()				override;
	void Update()			override;
	void DrawLesson()		override;

private:
	std::shared_ptr<KdModelWork> m_spModel = nullptr;

	Math::Vector2 m_UVOffset = Math::Vector2::Zero;
};