#pragma once

class CameraBase : public KdGameObject
{
public:

	CameraBase()				{}
	~CameraBase()	override	{}

	void PreDraw()	override;

	void Update()	override;

	void Init()		override;

	// カメラのターゲットとしたいオブジェクト情報の設定
	void SetTarget(std::shared_ptr<KdGameObject> _target)
	{
		m_wpTarget = _target;
	}

	// 作成してある当たり判定に使用するリストに格納するための関数
	void ResistHitObject(const std::shared_ptr<KdGameObject>& _object)
	{
		m_wpHitObjectList.push_back(_object);
	}

	const Math::Matrix GetRotationMatrix() const
	{
		return Math::Matrix::CreateFromYawPitchRoll
		(
			DirectX::XMConvertToRadians(m_degAng.y),			// Yaw
			DirectX::XMConvertToRadians(m_degAng.x),			// Pitch
			DirectX::XMConvertToRadians(m_degAng.z)				// Roll
		);
	}

	const Math::Matrix GetRotationYMatrix() const
	{
		return Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_degAng.y));
	}

protected:		// 継承先クラスで共通して使用できるアクセサ

	void UpdateRotateByMouse();

	std::shared_ptr<KdCamera>					m_spCamera = nullptr;

	std::weak_ptr<KdGameObject>					m_wpTarget;

	std::vector<std::weak_ptr<KdGameObject>>	m_wpHitObjectList{};			// 当たり判定をするオブジェクトを格納するリスト

	Math::Matrix				m_mLocalPos;
	Math::Matrix				m_mRatation;
	// 変数の"m_"の後の'm'は"Matrix"のmを示している

	POINT						m_FixMousePos;

	// カメラの回転用角度
	Math::Vector3				m_degAng;
};