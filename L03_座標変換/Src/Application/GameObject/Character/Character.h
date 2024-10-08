#pragma once

class Character : public KdGameObject
{
public:
	Character() {}
	virtual ~Character()	override {}

	void Init()				override;
	void Update()			override;
	void DrawLit()			override;
	void DrawSprite()		override;

	// 引数のカメラの情報を作成したカメラ情報に代入する
	void SetCamera(std::shared_ptr<KdCamera> camera)
	{
		m_wpCam = camera;
	}

	void SetTerrain(std::shared_ptr<KdGameObject> terrain)
	{
		m_wpTerrain = terrain;
	}

private:
	std::shared_ptr<KdSquarePolygon>	m_spPoly = nullptr;
	std::weak_ptr<KdCamera>				m_wpCam;			// カメラ情報

	std::shared_ptr<KdTexture>			m_spNamePlate = nullptr;

	std::weak_ptr<KdGameObject>			m_wpTerrain;

	Math::Vector3						m_TargetPos = Math::Vector3::Zero;
};