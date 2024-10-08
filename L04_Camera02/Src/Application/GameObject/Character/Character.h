#pragma once

class CameraBase;

class Character : public KdGameObject
{
public:
	Character() {}
	virtual ~Character()	override {}

	void Init()				override;
	void Update()			override;
	void DrawLit()			override;

	void SetCamera(const std::shared_ptr<CameraBase>& _camera)
	{
		m_wpCamera = _camera;
	}

private:

	void UpdateRotate(const Math::Vector3& _srcMoveVec);

	std::shared_ptr<KdSquarePolygon>	m_spPoly	= nullptr;

	std::weak_ptr<CameraBase>			m_wpCamera;

	// CameraBase						m_camera;
	// 前方宣言は、〇〇というクラスがあることを知らせるだけ
	// 中身は知らない
	// 中身まで完璧に知らないものを宣言することはできない

	// CameraBaae*						m_camera;
	// ポインタで作成する場合は前方宣言だけでも宣言だけは可能

	// KdSquarePolygon					m_Poly;
	// これはインクルードも前方宣言もしていないけれど宣言できるし、ビルドもできる
	// Pch.h(プリコンパイルヘッダ)で事前にインクルードしているために可能である
	// インスタンスを宣言できるのは、各クラスをシングルトンパターンで作成しているため、
	// 他のクラスでもインクルードせずに使用することができる

	Math::Vector3						m_WorldRot;
};