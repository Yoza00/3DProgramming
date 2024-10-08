#include "CameraBase.h"

void CameraBase::PreDraw()
{
	// 初期化されていない場合はリターン
	if (!m_spCamera)return;

	// ルールとして呼び出さないといけない
	m_spCamera->SetToShader();		// shaderプログラムに渡すプログラム
}

void CameraBase::Update()
{
	// 初期化されていない場合はリターン
	if (!m_spCamera)return;

	m_spCamera->SetCameraMatrix(m_mWorld);
}

void CameraBase::Init()
{
	// m_spCameraのnullチェック
	if (!m_spCamera)
	{
		m_spCamera = std::make_shared<KdCamera>();
	}
}

void CameraBase::UpdateRotateByMouse()
{
	POINT _nowPos;
	GetCursorPos(&_nowPos);

	// マウスカーソルの差分を求める
	POINT _mouseMove{};
	_mouseMove.x = _nowPos.x - m_FixMousePos.x;
	_mouseMove.y = _nowPos.y - m_FixMousePos.y;

	// マウスカーソルをサイド画面中央へ固定
	SetCursorPos(m_FixMousePos.x, m_FixMousePos.y);

	// 上の差分をもとにカメラの回転角度を求める
	m_degAng.x += _mouseMove.y * 0.15f;
	m_degAng.y += _mouseMove.x * 0.15f;
	// 0.15fは補正値(マウス感度)
}
